// MSFDecoder.

// Originally written as MSFTime by Jarkman, 01/2011 (see http://www.jarkman.co.uk/catalog/robots/msftime.htm).

// Decodes MSF time signals from a receiver like this:
//  http://www.pvelectronics.co.uk/index.php?main_page=product_info&cPath=9&products_id=2

// I have butchered the library to make it a bit more "passive", and to remove dependency on the Time library.
// I just needed a library that would listen on a particular input pin (courtesy of CHANGE interrupts), and store a decoded time.
// This is then grabbed by the host code and used to adjust an RTC module on a regular basis.

// The main decoder logic is fundamentally unchanged - all Kudos to Jarkman, please!

// 9th March 2013

#ifndef __MSFDECODER_H__
#define __MSFDECODER_H__

#include <inttypes.h>
typedef uint8_t byte;


#if !defined(__time_t_defined)
typedef unsigned long time_t;
#endif

#define MSF_SECOND	0
#define MSF_MINUTE	1
#define MSF_HOUR	2
#define MSF_DAY		3
#define MSF_DATE	4
#define MSF_MONTH	5
#define MSF_YEAR	6

#define MSF_STATUS_CARRIER 1 // got radio activity of some sort
#define MSF_STATUS_WAITING 2 // waiting for a sync marker
#define MSF_STATUS_READING 4 // currently reading in a fix
#define MSF_STATUS_FIX 8      // got a fix that's less than an hour old
#define MSF_STATUS_FRESH_FIX 16 // got a fix on our last cycle

class MSFDecoder
{
private:

  bool m_bIsReading; // false if no signal or waiting for minute start, true if reading data

  byte m_iInputPin; // pin number where MSF receiver is connected

  volatile long mOffStartMillis;
  volatile long mOnStartMillis;
  volatile long mPrevOffStartMillis;
  volatile long mPrevOnStartMillis;
  long mOnWidth;

  // the fix we're reading in
  byte mABits[8];
  byte mBBits[8];
  volatile byte m_iBitIndex;
  volatile byte m_iGoodPulses;

  volatile long mFixMillis; // value of millis() at last fix

  void doDecode();
  bool checkValid();
  bool checkParity(byte *bits, int from, int to, bool p);
  void setBit(byte* bits, int bitIndex, bool bSet);
  bool getBit(byte*bits, int bitIndex);
  byte decodeBCD(byte *bits, byte lsb, byte msb);
  byte encodeBCD(byte val);

  time_t makeTime();
  uint8_t getParity();

public:

  volatile bool TimeAvailable;
  volatile bool m_bHasValidTime; // true if the members below are worth reading ...
  volatile byte m_iYear;         // 0-99
  volatile byte m_iMonth;        // 1-12
  volatile byte m_iDay;          // 1-31
  volatile byte m_iDOW;          // 0-6
  volatile byte m_iHour;         // 0-23
  volatile byte m_iMinute;       // 0-59
  volatile byte m_iSecond = 0;   // 0-59
  volatile bool m_BST;
  volatile bool m_BSTSOON;
  volatile time_t TimeTime;
  volatile uint8_t ParityResult;
  volatile uint8_t rtcBuffer[7];
  volatile byte LED;

       MSFDecoder();
  void stateChange();
  void init(byte inputPin, byte interruptId);
  bool getHasCarrier();
  byte getBitCount()    {return(m_iBitIndex);}
  byte getProgress();
  byte getStatus();

};

#endif // __MSFDECODER_H__
