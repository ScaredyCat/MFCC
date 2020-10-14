/*
    I've Got A Big Clock - inspired by Brett Oliver's creations.

    Corona virus lockdown project

    Andy Powell, in the year of the virus, 2020.

    PIN Allocation
    ========================================================
    2   AON/CLOCKD/HUMAN  - Either AON (MSF Autogain on) or CLOCKD. CLOCKC and CLOCKD or human detection
                          - WARNING DS3231 library uses pins 2/3 - either don't use this lib or don't
                          - use AON/CLOCKD/HUMAN
    3   CLOCKC            - add the pontential to have another clock mechanism
    4   PON               - Power up for MSF board
    5   JQ6500            - (1/4, 1/2, 3/4  hour and top of the hour chimes)
    6   MAX7219_CS        - Drive 7 segment led arrays via SPI
    7   INTERRUPT 4       - Interrupt for MSF receiver
    8   JQ6500            - Software serial port for JQ6500 #2 to trigger chimes
    9   CLOCKA            - Drive pin for quartz clock requires 2 pins
    10  CLOCKB            - sending alternating pulses, 30ms pulse for 120ms
    11  LED_PIN           - For control of LED strip for notification LEDs.
    12  AUTOTOCK          - Hardware loop to JQ6500 #1 for repeated Tick-Tock.
    A0  TICKTOCKSWITCH    - Enable or disable tick-tock sound from JQ6500 #1
    A1  CHIMESWITCH       - Enable or disable 1/4 hour and hourly chimes from JQ6500 #2
    A2  BACKLIGHT_PIN     - Allows us to turn the LCD backlight on or off. Any value < 128 = Off
    A3  ADVANCE_PIN       - momentary switch turns advance on.
    A4  RETARD_PIN        - Momentary switch to retard pulses.
    A5  BACKLIGHT_TRIGGER - Force backlight on or off


    I2C:  LCD Display, Non volatile memory, DS3231
    SPI:  7 Segment displays

*/
#include <TimeLib.h>
#include <Adafruit_NeoPixel.h>
#include <MSFDecoder.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <JQ6500_Serial.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <DS3231.h>
#include <Timezone.h>

TimeChangeRule rBST = {"BST", Last, Sun, Mar, 1, 60};        //British Summer Time
TimeChangeRule rGMT = {"GMT", Last, Sun, Oct, 2, 0};         //Standard Time
Timezone UK(rBST, rGMT);
/*
    Clock pins for clock 1
    Multiple clocks can be used and hands removed that are
    not required, ie you can have a mechanism with just a
    second hand. Nothing really needs to change because
    they all take a pule to move a second's worth.
*/

const int CLOCKA = 9;         // Main analog clock pins
const int CLOCKB = 10;        // for alternate pulses.

/*
    Switches to disable or enable sounds and the backlight

*/
const int TICKTOCKSWITCH = A0;
const int CHIMESWITCH = A1;
const int BACKLIGHT_PIN = A2;
const int ADVANCE_PIN = A3;
const int RETARD_PIN = A4;
const int BACKLIGHT_TRIGGER = A5;
const int PON = 4;


/*
   Using a CANADUINO Atomic Clock AM Receiver that works with MSF
   in the UK. The other option in DCF77 where the signal originates
   from Germany. Canaduino has pathetic wires that will break. I'd advise hot gluing
   the board and antenna to a lump of wood the size of Canada so that it doesn't
   move aboot.

   MSF library needs an interrupt. This depends on the device being used and how many
   interrupts you have

   PON is a pin to allow powering the board on and off but in this instance power is
   'plentiful' so not required and we need the pins anyway.


*/


/*
    Arduino Interrupt Number:   0   1   2   3   4   5   6   7   8   9   10    11  12  13  14  15  16
    UNO I/O Pins                2   3           7
    LEONARDO                    3   2   0   1   -1  -1  7
    Mega2560 I/O Pins           2 3 21  20  19  18
    ESP8266 GPIO Pins           0 1 2 3 4 5             12  13  14  15  16

      Leonardo interrupt pins

      PIN D0 (rx) D1 (tx) D2  D3  D7
      INT   2       3     1    0  6

      PCINT (Pin Change)

      PIN     8   9   10    11
      PCINT   4   5   6      7
*/

uint8_t parity = 0;

/*

   MAX7219 driven 7 segment LED controller

*/

#define Number_MAX7219 2            // 2 chips = 16 digits
#define MAX7219_CS  6               // pin the MAX7219's CS pin is connected to
#define Default_Brightness 0        // brightness level 0-15

#include <MAX7219_8_Digit_Driver.h>

/*
    DS3231 for managing the time and keeping it stored in event of
    a power failure.
*/
#define disk1 0x57 // The 32k storage on the DS3231 board.
#define DS3231_I2C_ADDRESS 0x68
#include <DS3231.h>
DS3231 Clock(SDA, SCL);

//extern unsigned long timer0_overflow_count;
/*
    CLOCK_MINUTE values correspond with their id on
    the JQ6500 which is used to trigger audio playback

*/

const int CLOCK_15_MINUTE = 13;
const int CLOCK_30_MINUTE = 14;
const int CLOCK_45_MINUTE = 15;
const int CLOCK_00_MINUTE = 16;

const int twoSecondPulse = 12;

/*
    States of the sounds and backlight
*/
bool soundTickTock = true;
bool soundChime = true;
bool backlightState = true;
bool goDark = false;
bool isDark = false;
bool savedBacklightState = false;
bool refreshTime = true;

/*
      Trial and error values for each quartz clock
      mechanism

     int cwPulse   = 220;               // CW pulse width
     int cwPeriod  = 20;               // CW pulse interval
     int ccwPulse   = 120;               // CW pulse width
     int ccwPeriod  = 20;               // CW pulse interval
*/

const int clockwise = 30;
const int anticlockwise = 20;
const int minimumInterval = 40; // minimum between pulses to prevent stalling.
boolean flag = false;            // drive polarity flag - toggle for each pulse


#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

/*
    Hard to test if you haven't got a clock
    unixtime for testing
*/

const unsigned long DEFAULT_TIME = 1599231660;

/*
    Keep track of the time values, we only
    need to do things when there's a change
*/
int oldH, oldM, oldS, oldD, oldMo, oldY, oldW;

/*
   Avoid doing things the first time round
   everything gets setup nicely.
*/
bool firstRun = true;

/*
   If we need to change the time we can do it by
   either retarding (holding back on pulses) or
   by advancing (adding more frequent pulses)
   to adjust the time.

*/
bool retard = false;
int retardCount = 0;

bool advance = false;
int advanceCount = 0;

bool bstChangeForwardNow = false;
bool bstChangeBackwardNow = false;
const int bstTicks = 3600 + 720;  // 1 hour plus the time taken to advance an hour
const int bstRetards = 3600;
bool bstChanged = false;
bool bst = false;
bool bstsoon = false;
bool syncd = false;

/*
    Display setup for LCD. We don't have a
    last time we had a signal from MSF until
    we've run setup. Parity doesn't matter
    until we try to get a signal.
*/
char LastMSFLCD[21] = "00:00:00 00-00-00";
char parityReason[21] = "";
/*
   Rather than use multiple LEDs on pins or a matrix
   I went for an RGB strip. They cost almost nothing
   and you can cut off as many as you need and use them
   Arduino has happily run with 8 LEDS with no issues at all
   but I run then at less than a 10th of maximum brightness.

   However I will be using an external power source for these
   on the complete project because I plan on using them to indicate
   days of the week, months, week number etc

   They're indicator leds not a light show.

   Define what pin they're connected to and how many of them there
   are.
*/
#define   LED_PIN   11
#define   LED_COUNT 35
/*
   Parity Error LEDs
*/
#define   LED_PARITYERROR_YEAR 31
#define   LED_PARITYERROR_MONTH 32
#define   LED_PARITYERROR_WEEKDAY 33
#define   LED_PARITYERROR_TIME 34



/*
   Months of the year LEDs
*/

#define   LED_MONTH_JANUARY 19
#define   LED_MONTH_FEBRUARY 20
#define   LED_MONTH_MARCH 21
#define   LED_MONTH_APRIL 22
#define   LED_MONTH_MAY 23
#define   LED_MONTH_JUNE 24
#define   LED_MONTH_JULY 25
#define   LED_MONTH_AUGUST 26
#define   LED_MONTH_SEPTEMBER 27
#define   LED_MONTH_OCTOBER 28
#define   LED_MONTH_NOVEMBER 29
#define   LED_MONTH_DECEMBER 30

/*
   Days of the week LEDs.
   The numbers represent their location on the
   LED strip. Sunday is day 0. So we just need to
   add 10 to the day of the week value to get its
   location for lighting the LED
*/

#define   LED_DOW_SUNDAY 12
#define   LED_DOW_MONDAY 13
#define   LED_DOW_TUESDAY 14
#define   LED_DOW_WEDNESDAY 15
#define   LED_DOW_THURSDAY 16
#define   LED_DOW_FRIDAY 17
#define   LED_DOW_SATURDAY 18

#define   LED_MIRROR 11
#define   LED_SYNC_TODAY 10

#define   TICKTOCK 9
#define   CHIMING 8

#define   LED_BSTSOON 7
#define   LED_SUMMERTIME 6
#define   LED_MSFCARRIER 5
#define   VALID_MSFTIME 4
#define   SECOND_TICK 3
#define   LED_RETARD 2
#define   LED_ADVANCE 1
#define   LED_TICK 0

#define MAX_BRIGHTNESS 10

const uint8_t lcdbell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
const uint8_t lcdnote[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
const uint8_t lcdclock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
const uint8_t lcdheart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
const uint8_t lcdblank[8]  = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const uint8_t lcdcheck[8] = {0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0};
const uint8_t lcdcross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
const uint8_t lcdretarrow[8] = {  0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};


MSFDecoder MSF;

const byte aInputPin = 7;
const byte aInterrupt = 4;

byte MSFIcon[] = { B00000,  B00000,  B00000,  B01010,  B10101,  B00000,  B00000,  B00000};

static const uint32_t YELLOW = 0xFFCC00;
static const uint32_t RED    = 0xff0d00;
static const uint32_t GREEN  = 0x73ff00;
static const uint32_t WHITE  = 0xffffff;
static const uint32_t ORANGE = 0xff9900;
static const uint32_t PURPLE = 0x80098E;
static const uint32_t BLACK  = 0x000000;
static const uint32_t OFF    = 0x000000;
static const uint32_t BLUE   = 0x0B5394;
static const uint32_t MAGENTA = 0xFF00FF;


unsigned long pulses = 0;

bool g_bPrevCarrierState;
byte g_iPrevBitCount;

bool tick = false;
bool stopClock = false;
bool century = false;
bool ghourFormat12 = false;
bool writtenToday = false;
bool writtenThisHour = false;

byte iBitCount = 0;
bool bCarrierState = false;

Time tinfo;


const char* weekDay[8] = {  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
const char* months[13] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const char* parityErrors[5] = { "No Errors", "Year Error", "Month Error", "Weekday Error", "Time Error"};

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

// make an instance of MAX7219_Digit called My_Display and set CS pin

MAX7219_8_Digit_Driver My_Display(MAX7219_CS, Number_MAX7219);

JQ6500_Serial mp3(8, 5);


void setup() {

  byte savedHour, savedMinute, savedSecond, savedDay, savedMonth, savedYear;

  pinMode(PON, OUTPUT);
  digitalWrite(PON, LOW);

  pinMode(TICKTOCKSWITCH, INPUT_PULLUP);
  pinMode(CHIMESWITCH, INPUT_PULLUP);
  pinMode(ADVANCE_PIN, INPUT_PULLUP);
  pinMode(RETARD_PIN, INPUT_PULLUP);
  pinMode(BACKLIGHT_TRIGGER, INPUT_PULLUP);
  pinMode(twoSecondPulse, OUTPUT);

  Wire.begin();

  g_bPrevCarrierState = false;
  g_iPrevBitCount = 255;

  digitalWrite(13, LOW);
  //sprintf(wipe, "%16s"," ");
  My_Display.String_To_Buffer(" ", 0);

  //if (SERIALOUT) {
  //  Serial.begin(115200);
  //   while (!Serial);
  //}

  MSF.init(aInputPin, aInterrupt);

  Clock.begin();

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(MAX_BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)

  pinMode(CLOCKA, OUTPUT);
  pinMode(CLOCKB, OUTPUT);
  digitalWrite(CLOCKA, LOW);
  digitalWrite(CLOCKB, LOW);

  tinfo = Clock.getTime();
  setTime(tinfo.hour, tinfo.min, tinfo.sec, tinfo.date, tinfo.mon, tinfo.year);

  mp3.begin(9600);
  mp3.reset();
  mp3.setVolume(27);
  mp3.setLoopMode(MP3_LOOP_NONE);

  readSavedDate(savedHour, savedMinute, savedSecond, savedDay, savedMonth, savedYear);
  sprintf(LastMSFLCD, "%02d:%02d:%02d %02d-%02d-%02d", savedHour, savedMinute, savedSecond, savedDay, savedMonth, savedYear);

  /*if (savedMonth > month() && savedDay > day() && savedYear > year() && savedHour > hour() and savedMinute > minute()) {
    Clock.setTime(savedHour,savedMinute,savedDay);
    Clock.setDate(savedDay,savedMonth,savedYear);
    }
  */
  /*
    // set a default time until we get a DS3231 battery backed up clock attached.
    setTime(DEFAULT_TIME);

    Clock.setTime(hour(),minute(),second());
    Clock.setDOW(weekday());
    Clock.setDate(day(),month(),year());


  */

  g_bPrevCarrierState = false;
  g_iPrevBitCount = 255;

  lcd.init();                      // initialize the lcd
  lcd.setBacklight(HIGH);
  //lcd.createChar(6, lcdcross);
  lcd.createChar(0, lcdbell);
  lcd.createChar(1, lcdnote);
  lcd.createChar(2, lcdclock);
  lcd.createChar(3, lcdheart);
  lcd.createChar(4, lcdblank);
  lcd.createChar(5, lcdcheck);
  lcd.createChar(6, MSFIcon);
  lcd.createChar(7, lcdretarrow);
  lcd.home();
  lcd.setCursor(15, 0);
  lcd.printByte(3);

  if (soundTickTock) {
    lcd.setCursor(16, 0);
    lcd.printByte(0);
  } else {
    lcd.setCursor(16, 0);
    lcd.printByte(4);
  }
  if (soundChime) {
    lcd.setCursor(17, 0);
    lcd.printByte(1);
  } else {
    lcd.setCursor(17, 0);
    lcd.printByte(4);
  }
  if (advance) {
    lcd.setCursor(18, 0);
    lcd.printByte(2);
  } else {
    lcd.setCursor(18, 0);
    lcd.printByte(4);
  }
  if (retard) {
    lcd.setCursor(19, 0);
    lcd.printByte(7);
  } else {
    lcd.setCursor(19, 0);
    lcd.printByte(4);
  }

  lcd.setCursor(0, 1); lcd.printByte(2);
  lcd.setCursor(0, 2); lcd.printByte(6);

  /* backlight off for startup */
  pinMode(BACKLIGHT_PIN, OUTPUT);
  analogWrite(BACKLIGHT_PIN, 0);

 // setSyncInterval(260);
 // setSyncProvider(refreshClockTime);

}

unsigned long refreshClockTime() {

  return Clock.getUnixTime(Clock.getTime());
}


// Main loop
void loop() {


  if (firstRun) {
    oldM = minute();
    oldH = hour();
    oldY = year();
    dayOfWeekLED(weekday());
    monthOfYearLED(month());
    firstRun = false;
  }

  bCarrierState = MSF.getHasCarrier();
  iBitCount = MSF.getBitCount();



  if (MSF.TimeAvailable) {

    parity = MSF.ParityResult;

    if ( parity == 0) {

      // write it to DS3231
      if (MSF.m_iYear < 2000)
        Clock.setDate(MSF.m_iDay, MSF.m_iMonth, 2000 + MSF.m_iYear);
      else
        Clock.setDate(MSF.m_iDay, MSF.m_iMonth, MSF.m_iYear);

      Clock.setTime(MSF.m_iHour, MSF.m_iMinute, 0);
      Clock.setDOW(MSF.m_iDOW);

      if (MSF.m_iYear < 2000)
        setTime(MSF.m_iHour, MSF.m_iMinute, 0, MSF.m_iDay, MSF.m_iMonth, MSF.m_iYear);
      else
        setTime(MSF.m_iHour, MSF.m_iMinute, 0, MSF.m_iDay, MSF.m_iMonth, 2000 + MSF.m_iYear);

      Clock.setDate(day(), month(), year());


      /*
          This will serve as "The last date signal received history.
          We'll load this into LastMSFLCD when the arduino restarts.

         This is EEPROM so if our signal is "too good" we want to prevent writing to this constantly

      */
      if (!writtenThisHour)
        writeSavedDate(MSF.m_iHour, MSF.m_iMinute, 0, MSF.m_iDay, MSF.m_iMonth, MSF.m_iYear);

      writtenToday = true;
      writtenThisHour = true;


      bst = MSF.m_BST;
      bstsoon = MSF.m_BSTSOON;

      indicatorLED(LED_SUMMERTIME, YELLOW, OFF, bst);
      indicatorLED(LED_BSTSOON, YELLOW, OFF, bstsoon);

      sprintf(LastMSFLCD, "%02d:%02d:%02d %02d-%02d-%02d", hour(), minute(), 0, day(), month(), year() - 2000);
      syncd = true;

      indicatorLED(LED_SYNC_TODAY, BLUE, OFF, syncd);

      indicatorLED(LED_PARITYERROR_YEAR, YELLOW, OFF, false);
      indicatorLED(LED_PARITYERROR_MONTH, YELLOW, OFF, false);
      indicatorLED(LED_PARITYERROR_WEEKDAY, YELLOW, OFF, false);
      indicatorLED(LED_PARITYERROR_TIME, YELLOW, OFF, false);

      // Show it on LCD

      /*
         Automatically retard time if we're changing to winter
         time.
      */

      if (MSF.m_BST && MSF.m_BSTSOON && !bstChanged) {
        retardCount = bstRetards;
        retard = true;
        stopClock = true;
        bstChanged = true;
      }

      /*
         Automatically advance time if we're changing to summer
         time.
      */

      if (!MSF.m_BST && MSF.m_BSTSOON && !bstChanged) {
        advanceCount = bstTicks;
        advance = true;
        bstChanged = true;
      }

      dayOfWeekLED(weekday());
      monthOfYearLED(month());

    } else {

      if (parity > 0) {
        indicatorLED(30 + parity, RED, OFF, true);
      }
    }

    MSF.TimeAvailable = 0;
  } else {

    // doing this makes me vomit a little each time I see it.
    // but it does 'fix' the issue.
    
    tinfo = Clock.getTime();
    setTime(tinfo.hour, tinfo.min, tinfo.sec, tinfo.date, tinfo.mon, tinfo.year);
  }
  
   indicatorLED(LED_MIRROR, MAGENTA, OFF, !MSF.LED);
    
   tasksOnceASecond();

  if (retard || bstChangeBackwardNow) {
    if (retardCount > 0) {
      if (oldS != second() ) {
        oldS = second();
        retardCount--;
      }

    } else {
      retard = false;
      bstChangeBackwardNow = false;
      stopClock = false;
      retardCount = 0;
      lcdindicatorLED(LED_RETARD, retard);
      indicatorLED(LED_RETARD, PURPLE, OFF, retard);

    }
    displayTime(goDark);
  }

  if (advance || bstChangeForwardNow) {
    if (advanceCount > 0) {
      delay(minimumInterval);
      motorPulse(clockwise);
      advanceCount--;
      //sprintf(parityReason,"% 10d",bstTicks-advanceCount);
    } else {
      advance = false;
      bstChangeForwardNow = false;
      advanceCount = 0;
      lcdindicatorLED(LED_ADVANCE, advance);
      indicatorLED(LED_ADVANCE, GREEN, OFF, advance);

    }
    displayTime(goDark);

  }

} // loop

void indicatorLED(int c, uint32_t onColour, uint32_t offColour, bool state) {

  if (!goDark) {

    if (isDark) {
      strip.setBrightness(MAX_BRIGHTNESS);
      isDark = false;
    }

    if (state)
      strip.setPixelColor(c, onColour); // Set pixel 'c' to value 'color'
    else
      strip.setPixelColor(c, offColour); // Set pixel 'c' to value 'color'


  } else {
    //strip.setPixelColor(c, OFF);
    strip.setBrightness(0);
    isDark = true;
  }


  strip.show();

}


void displayTime(bool lightsOut) {

  char timeDisplay[22];
  char timeDisplayLCD[22];


  if (second() % 3 == 0) {
    //indicatorLED(LED_ADVANCE, GREEN, OFF, true);
    sprintf(timeDisplay, "%02d-%02d-%02d%02d-%02d-%02d", hour(), minute(), second(), day(), month(), year() - 2000);
    sprintf(timeDisplayLCD, "%02d:%02d:%02d %02d-%02d-%02d", hour(), minute(), second(), day(), month(), year() - 2000);
  } else {
    //indicatorLED(LED_ADVANCE, GREEN, OFF, false);
    sprintf(timeDisplay, "%02d %02d %02d%02d-%02d-%02d", hour(), minute(), second(), day(), month(), year() - 2000);
    sprintf(timeDisplayLCD, "%02d %02d %02d %02d-%02d-%02d", hour(), minute(), second(), day(), month(), year() - 2000);
  }

  char dy[3] = "";
  
  sprintf(dy, "%2d", day());

  //if (SERIALOUT) Serial.println(timeDisplay);

  if (lightsOut || backlightState) {
    if (lightsOut)
      sprintf(timeDisplay, "%8 ");
    lcd.noDisplay();
  } else {
    lcd.display();
  }

  My_Display.String_To_Buffer(timeDisplay, 0);


  /* if (!syncd)
     sprintf(parityReason,"(no sync)");
    else
     sprintf(parityReason,"%s",parityErrors[parity]);
  */

  sprintf(parityReason, "  %02d of 60 Pulses", iBitCount);

  say(4, 1, parityReason, false);
  say(2, 3, timeDisplayLCD, false);
  say (3, 3, LastMSFLCD, false);
  say(1, 1, weekDay[weekday() - 1], false);
  say(1, 5, dy, false);
  say(1, 8, months[month()], false);



}

void checkSwitches() {

  soundTickTock = !digitalRead(TICKTOCKSWITCH);
  soundChime = !digitalRead(CHIMESWITCH);
  backlightState = digitalRead(BACKLIGHT_TRIGGER);
  advance = !digitalRead(ADVANCE_PIN);
  retard = !digitalRead(RETARD_PIN);

  if (advance) {
    //advance = digitalRead(ADVANCE_PIN);
    lcdindicatorLED(LED_ADVANCE, advance);
    indicatorLED(LED_ADVANCE, GREEN, OFF, advance);
    advanceCount = 5;
  }

  if (retard) {
    lcdindicatorLED(LED_RETARD, retard);
    indicatorLED(LED_RETARD, PURPLE, OFF, true);
    retardCount = 5;
    stopClock = true;
  }

  lcdindicatorLED(TICKTOCK, soundTickTock);
  lcdindicatorLED(CHIMING, soundChime);

  indicatorLED(TICKTOCK, WHITE, OFF, soundTickTock);
  indicatorLED(CHIMING, WHITE, OFF, soundChime);

  if (backlightState || goDark)
    analogWrite(BACKLIGHT_PIN, 0);
  else
    analogWrite(BACKLIGHT_PIN, 128);

}

void chime(int chimeId) {

  if (!goDark)
    mp3.playFileByIndexNumber(chimeId);

}


void monthOfYearLED(int m) {

  for (int i = LED_MONTH_JANUARY - 18; i <= LED_MONTH_DECEMBER - 18; i++) {
    if (m == i)
      strip.setPixelColor(i + 18, GREEN);
    else
      strip.setPixelColor(i + 18, OFF);
  }

  strip.show();

}

void dayOfWeekLED(int DOW) {

  for (int i = LED_DOW_SUNDAY - 12; i <= LED_DOW_SATURDAY - 12; i++) {
    if (DOW == i)
      strip.setPixelColor(i + 12, GREEN);
    else
      strip.setPixelColor(i + 12, OFF);
  }

  strip.show();

}

void lcdindicatorLED(int item, bool state) {

  switch (item) {
    case SECOND_TICK:
      lcd.setCursor(15, 0);
      if (state) {
        lcd.printByte(3);
      } else {
        lcd.printByte(4);
      }
      break;
    case TICKTOCK:
      lcd.setCursor(16, 0);
      if (state) {
        lcd.printByte(0);
      } else {
        lcd.printByte(4);
      }
      break;
    case CHIMING:
      lcd.setCursor(17, 0);
      if (state) {
        lcd.printByte(1);
      } else {
        lcd.printByte(4);
      }
      break;
    case LED_ADVANCE:
      lcd.setCursor(18, 0);
      if (state) {
        lcd.printByte(2);
      } else {
        lcd.printByte(4);
      }
      break;
    case LED_RETARD:
      lcd.setCursor(19, 0);
      if (state) {
        lcd.printByte(7);
      } else {
        lcd.printByte(4);
      }
      break;
  }
}


void tasksOnceASecond() {

  if (oldS != second() && (!retard && !advance)) {
      oldS = second();
      
   
    tasksOnceAMinute();
    tasksOnceAnHour();
    tasksOnceADay();
    tasksOnceAYear();

    if (stopClock == false) {
        motorPulse(clockwise);
        pulses++;
    }
    
    indicatorLED(LED_MSFCARRIER, GREEN, WHITE, bCarrierState);
    indicatorLED(VALID_MSFTIME, GREEN, ORANGE, MSF.TimeAvailable);
        
    tick = !tick;
    
    indicatorLED(SECOND_TICK, GREEN, RED, tick);
    lcdindicatorLED(SECOND_TICK, tick);


    if (oldH >= 1 && oldH <= 6)
      goDark = true;
    else
      goDark = false;

    displayTime(goDark);

    if (second() % 5 == 0)
      checkSwitches();


    if ( (second() % 2) == 0 && !goDark && soundTickTock) {
      digitalWrite(twoSecondPulse, HIGH);
    } else {
      digitalWrite(twoSecondPulse, LOW);
    }   
  }
}


void tasksOnceAMinute() {

  if (minute() != oldM) {
    oldM = minute();
    // do things each minute

    if (soundChime && !goDark) {

      
      if (oldM == 10 && oldS == 0)  {
        chime(CLOCK_15_MINUTE);
      }

      if (oldM == 15 && oldS == 0)  {
        chime(CLOCK_15_MINUTE);
      }
      if (oldM == 30 && oldS == 0)  {
        chime(CLOCK_30_MINUTE);
      }
      if (oldM == 45 && oldS == 0)  {
        chime(CLOCK_45_MINUTE);
      }
      if (oldM == 59 && oldS == 55) {
        chime(CLOCK_15_MINUTE);
      }

    }
    
    // It's not a thermometer, just extra info, once a minute is enough 
    char tmp[4];
    char tempBu[6] = "";
    
    dtostrf(Clock.getTemp(), 2, 0, tmp);
    sprintf(tempBu, "%s%c", tmp, 0xDF); //degrees
    say(1, 12, tempBu, false);
    
  }


}
void tasksOnceAnHour() {

  if (hour() != oldH) {
    oldH = hour();

    if (!goDark) {
      if (oldH > 12) {
        chime(oldH - 12);
      } else {
        if (oldH == 0)
          chime(12);
        else
          chime(oldH);
      }
    }
    writtenThisHour = false;
  }

}



void tasksOnceADay() {

  byte savedHour, savedMinute, savedSecond, savedDay, savedMonth, savedYear;

  // if a new day then...
  if (day() != oldD) {
    oldD = day();
    dayOfWeekLED(weekday());
    writtenToday = false;  //allow write to EEPROM (once) for this new day.
    syncd = false;
    indicatorLED(LED_SYNC_TODAY, YELLOW, OFF, syncd);
    readSavedDate(savedHour, savedMinute, savedSecond, savedDay, savedMonth, savedYear);
    sprintf(LastMSFLCD, "%02d:%02d:%02d %02d-%02d-%02d", savedHour, savedMinute, savedSecond, savedDay, savedMonth, savedYear);
  }

  if (month() != oldMo) {
    oldMo = month();
    monthOfYearLED(oldMo);
  }
}

void tasksOnceAYear() {

  if (year() != oldY) {
    oldY = year();
  }

}


void say(int x, int y, String what, bool clean) {

  if (clean)
    lcd.clear();

  lcd.setCursor(y - 1, x - 1);
  lcd.print(what);

}


void writeSavedDate(byte savedHour, byte savedMinute, byte savedSecond, byte savedDay, byte savedMonth, byte savedYear) {

  unsigned int address = 0;

  writeEEPROM(disk1, address++, savedHour);
  writeEEPROM(disk1, address++, savedMinute);
  writeEEPROM(disk1, address++, savedSecond);

  writeEEPROM(disk1, address++, savedDay);
  writeEEPROM(disk1, address++, savedMonth);
  writeEEPROM(disk1, address++, savedYear);

}


void readSavedDate(byte& savedHour, byte& savedMinute, byte& savedSecond, byte& savedDay, byte& savedMonth, byte& savedYear) {

  unsigned int address = 0;

  savedHour   = readEEPROM(disk1, address++);
  savedMinute = readEEPROM(disk1, address++);
  savedSecond = readEEPROM(disk1, address++);

  savedDay   = readEEPROM(disk1, address++);
  savedMonth = readEEPROM(disk1, address++);
  savedYear  = readEEPROM(disk1, address++);

}


void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data )
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();

  delay(5);
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;

  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(deviceaddress, 1);

  if (Wire.available()) rdata = Wire.read();

  return rdata;
}


void motorPulse(int movementDirection) {

  indicatorLED(LED_TICK, ORANGE, OFF, true);

  flag = ! flag;                   // reverse polarity from last drive
  if (flag != true) {
    posiDrive(movementDirection);
  }  else {
    negaDrive(movementDirection);
  }

  indicatorLED(LED_TICK, GREEN, OFF, false);

}



void posiDrive(int t) {            // output positive pulse at designated width
  digitalWrite(CLOCKB, HIGH);
  digitalWrite(CLOCKA, LOW);           // coil drive positive
  delay(t);               // wait spcified time
  digitalWrite(CLOCKA, HIGH);            // coil drive end
}

void negaDrive(int t) {                 // output negative pulse at designated width
  digitalWrite(CLOCKA, HIGH);
  digitalWrite(CLOCKB, LOW);          // coil drive negative
  delay(t);                             // wait specified time
  digitalWrite(CLOCKB, HIGH);           // coil drive end
}

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val) {
  return ( (val / 10 * 16) + (val % 10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}
