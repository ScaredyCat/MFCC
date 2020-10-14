// MSFDecoder.

// Originally written as MSFTime by Jarkman, 01/2011 (see http://www.jarkman.co.uk/catalog/robots/msftime.htm).

// Decodes MSF time signals from a receiver like this:
//  http://www.pvelectronics.co.uk/index.php?main_page=product_info&cPath=9&products_id=2

// I have butchered the library to make it a bit more "passive", and to remove dependency on the Time library.
// I just needed a library that would listen on a particular input pin (courtesy of CHANGE interrupts), and store a decoded time.
// This is then grabbed by the host code and used to adjust an RTC module on a regular basis.

// The main decoder logic is fundamentally unchanged - all Kudos to Jarkman, please!

// 9th March 2013
//
//
// June 2020  - Added BST and BST Changing indicators and decoding.
//            - Added Pin and interrupt id parameters. Should probably be
//              a lookup table for each arduino model but I don't have the time
//              or inclination to build it, just pass the right values.
//            - Increased minmum pulse width length to prevent interrupt being
//              called repeatedly in noisy environments.
//            - Decreased PULSE_OFF_OFFSET

#include "Arduino.h"
#include <wiring_private.h>
#include "MSFDecoder.h"

#define PULSE_MARGIN 30     // The leeway we allow our pulse lengths

#define PULSE_OFF_OFFSET 10 // arbitrary offset to compensate for assymetric behaviour of my receiver,
                            // which tends to deliver an 'off' period that is too short

#define PULSE_IGNORE_WIDTH 80 // just ignore very short pulses

MSFDecoder *sMSF = NULL; // pointer to singleton

MSFDecoder::MSFDecoder()
{
  m_bHasValidTime = false;
  TimeAvailable = false;
  m_bIsReading = false;
}

void sStateChange() // static function for the interrupt handler
{
  if (sMSF) sMSF->stateChange();
}

void MSFDecoder::init(byte inputPin, byte interruptId)
{
  m_bHasValidTime = false;
  TimeAvailable = false;

  mOffStartMillis = 0;
  mOnStartMillis = 0;
  mPrevOffStartMillis = 0;
  mPrevOnStartMillis = 0;
  mOnWidth = 0;
  mFixMillis = 0;
  m_bIsReading = false;
  m_iBitIndex = 0;
  m_iGoodPulses = 0;

  for (int i = 0; i < 7; i++)
  {
    mABits[i] = 0;
    mBBits[i] = 0;
  }

  sMSF = this; // singleton pointer

  m_iInputPin = inputPin;
  pinMode(m_iInputPin, INPUT);
  attachInterrupt(interruptId, sStateChange, CHANGE);
}

//byte oldVal = 3;

void MSFDecoder::stateChange()  // interrupt routine called on every state change
{
  byte val = digitalRead(m_iInputPin);
  //if (val == oldVal) return;
  //oldVal = val;
  LED = val;
  long millisNow = millis();

  // see here:
  // http://www.pvelectronics.co.uk/rftime/msf/MSF_Time_Date_Code.pdf
  // for an explanation of the format

  // Carrier goes off for 100, 200, 300, or 500 mS during every second

  // Our input is inverted by our receiver, so val != 0 when carrier is off

  if (val != 0) // carrier is off, start timing
  {
  	if (millisNow - mOnStartMillis < PULSE_IGNORE_WIDTH)
    {
      // ignore this transition plus the previous one
      mOnStartMillis = mPrevOnStartMillis;
      return;
    }

    mPrevOffStartMillis = mOffStartMillis;
    mOffStartMillis = millisNow;

    mOnWidth = mOffStartMillis - mOnStartMillis;
    return;
  }

  if (millisNow - mOffStartMillis < PULSE_IGNORE_WIDTH)
  {
    // ignore this transition plus the previous one
    mOffStartMillis = mPrevOffStartMillis;
    return;
  }

  mPrevOnStartMillis = mOnStartMillis;
  mOnStartMillis = millisNow;

  long offWidth = millisNow - mOffStartMillis - PULSE_OFF_OFFSET;

  /* check the width of the off-pulse; according to the specifications, a
   * pulse must be 0.1 or 0.2 or 0.3 or 0.5 seconds
   */

  bool is500 = abs(offWidth-500) < PULSE_MARGIN;
  bool is300 = abs(offWidth-300) < PULSE_MARGIN;
  bool is200 = abs(offWidth-200) < PULSE_MARGIN;
  bool is100 = abs(offWidth-100) < PULSE_MARGIN;

  long onWidth = mOnWidth;

  bool onWas100 =  (onWidth > 5) && (onWidth < 200);

  bool onWasNormal = (onWidth > 400) && (onWidth < (900 + PULSE_MARGIN));

  if ((onWasNormal || onWas100) && (is100 || is200 || is300 || is500))
  {
    m_iGoodPulses++;
  }
  else
  {
    m_iGoodPulses = 0;
  }

  /*
    Cases:
    a 500mS carrier-off marks the start of a minute
    a 300mS carrier-off means bits 1 1
    a 200mS carrier-off means bits 1 0
    a 100mS carrier-off followed by a 900mS carrier-on means bits 0 0
    a 100mS carrier-off followed by a 100mS carrier-on followed by a 100mS carrier-off means bits 0 1
  */

  if (is500) // minute marker
  {
    if (m_bIsReading) doDecode();

    m_bIsReading = true; // and get ready to read the next minute's worth
    m_iBitIndex = 1;  // the NPL docs number bits from 1, so we will too
  }
  else
  if (m_bIsReading)
  {
    if (m_iBitIndex < 60 && onWasNormal && (is100 || is200 || is300)) // we got a sensible pair of bits, 00 or 01 or 11
    {
      if (is100)
      {
        setBit(mABits, m_iBitIndex, false);
        setBit(mBBits, m_iBitIndex++, false);
      }
      if (is200)
      {
        setBit(mABits, m_iBitIndex, true);
        setBit(mBBits, m_iBitIndex++, false);
      }
      if (is300)
      {
        setBit(mABits, m_iBitIndex, true);
        setBit(mBBits, m_iBitIndex++, true);
      }
    }
    else
    if (m_iBitIndex < 60 && onWas100 && is100 && m_iBitIndex > 0) // tricky - we got a second bit for the preceding pair
    {
      setBit(mBBits, m_iBitIndex - 1, true);
    }
    else // bad pulse, give up
    {
      m_bIsReading = false;
      m_iBitIndex = 0;
    }
  }
}

byte MSFDecoder::getProgress()
{
  if( m_bIsReading )
    return m_iBitIndex;
  else
    return m_iGoodPulses;
}


void MSFDecoder::doDecode()
{
	m_bHasValidTime = false;
  TimeAvailable = false;

    if (m_iBitIndex != 60) return; // there are always 59 bits, barring leap-seconds

    if (!checkValid()) return;

    mFixMillis = millis() - 500L;

    m_iYear    = decodeBCD(mABits, 24, 17);    // 0-99
    m_iMonth   = decodeBCD(mABits, 29, 25);    // 1-12
    m_iDay     = decodeBCD(mABits, 35, 30);    // 1-31
    m_iDOW     = decodeBCD(mABits, 38, 36);
    m_iHour    = decodeBCD(mABits, 44, 39);    // 0-23
    m_iMinute  = decodeBCD(mABits, 51, 45);    // 0-59
    m_BST      = getBit(mBBits, 58);
    m_BSTSOON  = getBit(mBBits, 53);
    TimeTime   = makeTime();
    ParityResult = getParity();

    rtcBuffer[MSF_SECOND] = 0;
    rtcBuffer[MSF_MINUTE] = m_iMinute; 	// minute
    rtcBuffer[MSF_HOUR]   = m_iHour;		// hour
    rtcBuffer[MSF_DAY]    = m_iDOW;	// weekday
    rtcBuffer[MSF_DATE]   = m_iDay;		// date
    rtcBuffer[MSF_MONTH]  = m_iMonth; 		// month
    rtcBuffer[MSF_YEAR]   = 2000+m_iYear;

    TimeAvailable  = true;

    if (!checkValid()) return;

    m_bHasValidTime = true;
}

bool MSFDecoder::checkValid()
{
  if ( getBit(mABits, 52)) return(false);
  if (!getBit(mABits, 53)) return(false);
  if (!getBit(mABits, 54)) return(false);
  if (!getBit(mABits, 55)) return(false);
  if (!getBit(mABits, 56)) return(false);
  if (!getBit(mABits, 57)) return(false);
  if (!getBit(mABits, 58)) return(false);
  if ( getBit(mABits, 59)) return(false);
  if (!checkParity(mABits, 17, 24, getBit(mBBits, 54))) return(false);
  if (!checkParity(mABits, 25, 35, getBit(mBBits, 55))) return(false);
  if (!checkParity(mABits, 36, 38, getBit(mBBits, 56))) return(false);
  if (!checkParity(mABits, 39, 51, getBit(mBBits, 57))) return(false);

  return(true);
}


uint8_t MSFDecoder::getParity()
{
	// calculate the parity bits and return true if all's well
	// all data and parity bits are relative to the last second count copntained in "bitPointer"
	// this allows for leap seconds which are added or removed at second 16 i.e. before
	// the actual date & time data. There can be 59 or 61 seconds in a leep minute
	// Year data parity check
  if (!checkParity(mABits, 17, 24, getBit(mBBits, 54))) return 1;
  if (!checkParity(mABits, 25, 35, getBit(mBBits, 55))) return 2;
  if (!checkParity(mABits, 36, 38, getBit(mBBits, 56))) return 3;
  if (!checkParity(mABits, 39, 51, getBit(mBBits, 57))) return 4;

	return 0;
}


bool MSFDecoder::checkParity(byte *bits, int from, int to, bool p)
{
  int set = 0;
  int b;
  for (b = from; b <= to; b++)
  {
    if (getBit(bits, b)) set++;
  }

  if (p) set++;

  if (set & 0x01) return(true);// must be an odd number of set bits

  return(false);
}

bool MSFDecoder::getHasCarrier()
{
  if ((millis() - mOffStartMillis) >= 5000L) return(false);
  return(true);
}

void MSFDecoder::setBit(byte* bits, int bitIndex, bool bSet) // sets bit if bSet is true, or clears it otherwise
{
  byte mask = 1 << (bitIndex & 0x7);

  if (bSet) bits[bitIndex>>3] = bits[bitIndex>>3] | mask;
  else      bits[bitIndex>>3] = bits[bitIndex>>3] & ( ~ mask );
}

bool MSFDecoder::getBit(byte* bits, int bitIndex)
{
  byte mask = 1 << (bitIndex & 0x7);

  return (bits[bitIndex>>3] & mask) != 0;
}

byte MSFDecoder::encodeBCD(byte val) {
  return( (val/10*16) + (val%10) );
}

byte BCD[] = {1, 2, 4, 8, 10, 20, 40, 80};

byte MSFDecoder::decodeBCD( byte *bits, byte lsb, byte msb )
{
  byte result = 0;

  byte b = lsb;
  byte d = 0;

  for( ; b >= msb; b --, d ++ )
  {
    if( getBit( bits, b ))
      result += BCD[ d ];
  }

  return result;
}


byte MSFDecoder::getStatus()
{
  byte result = 0;

  if( (millis() - mOffStartMillis) < 5000L)
    result = result |  MSF_STATUS_CARRIER; // got radio activity of some sort

   if( m_iBitIndex > 1 )
     result = result | MSF_STATUS_READING;
   else
     if( result & MSF_STATUS_CARRIER )
       result = result | MSF_STATUS_WAITING;

   if( (millis() - mFixMillis) < 60L * 60000L )
     result = result | MSF_STATUS_FIX;      // got a fix that's less than an hour old

    if( (millis() - mFixMillis) < 62000L )
      result = result | MSF_STATUS_FRESH_FIX;    // got a fix on our last cycle

    return result;
}

#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)

static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0


time_t MSFDecoder::makeTime()
{
// this function was borrowed and modified from the Time library by Michael Margolis
// note year argument is offset from 1970 (see macros in Time.h to convert to other formats)
// previous version used full four digit year (or digits since 2000),i.e. 2009 was 2009 or 9

	int16_t i;
	uint32_t seconds;
	uint8_t Year = m_iYear;	//decYear;
	uint8_t Month = m_iMonth;
	uint8_t Date = m_iDay;
  uint8_t Hour = m_iHour;
	uint8_t Minute = m_iMinute;

	if(Year > 99) Year = Year - 1970;
	else Year += 30;

	// seconds from 1970 till 1 jan 00:00:00 of the given year
	seconds= Year*(SECS_PER_DAY * 365);
	for (i = 0; i < Year; i++)
	{
		if (LEAP_YEAR(i)) seconds +=  SECS_PER_DAY;   // add extra days for leap years
	}

	// add days for this year, months start from 1
	for (i = 1; i < Month; i++)
	{
		if ( (i == 2) && LEAP_YEAR(Year)) seconds += SECS_PER_DAY * 29;
		else seconds += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
	}
	seconds+= (Date-1) * SECS_PER_DAY;
	seconds+= Hour * SECS_PER_HOUR;
	seconds+= Minute * SECS_PER_MIN;
  return seconds;
}
