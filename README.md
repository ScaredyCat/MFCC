# MFCC
My first Clock Controller - My Corona Virus lockdown project (2020 - just in case there's another outbreak)

I was furloughed during 2020 and legally wasn't allowed to work for my employer so I took the time to try and learn somthing new. That turned out to be this project, learning how to use Kicad and how to build a radio-time enabled clock. Most of the things I've built in the past don't survive for too long, the Arduino is invariably repurposed for the next project and so on. This time is was different.

# Before we start

Most of this is really new to me. I've never designed a circuit board of any real complexity before this and I wouldn't particularly trust that my electronics knowledge is any use at all.


I've made some modifications to both the MSFDecoder library and the JQ6500 library so they are included here for completeness.

# Board

I used a DIYMORE Arduino Leonardo Clone for this project they are half the price of a Genuine Arduino Leonardo and have pints broken out to header pins in addition to the standard headers. The also have GND and 5v broken out for each pin and additional header pins for serial and i2c. This is really the sort of connectivity that I think should be on the genuine boards, but I guess they have reasons for not doing it.

The "motherboard" is really a deliberately oversized Arduino shield but it removes a lot of the wires and provides a stable platform fo rall the components. I appreciate my soldering leaves a lot to be desired. I used pin headers quite a bit for my connections just for convenience - they turned out to be inconvenient when wires kept popping out of them. Many of the connections do not get populated as they are for other options.



![Image of boards](https://github.com/ScaredyCat/MFCC/blob/main/images/boards.png)

# Modules

The design is fairly modular and uses off the shelf modules to provide additional features. Prices at time of purchase (May-Oct 2020)

 - I2C:  LCD Display, Non volatile memory (EEPROM), DS3231
 - SPI:  7 Segment displays

 Major parts:

- 2 x JQ6500 for audio - if you don't want audio or only want chimes or only want tick-tock then it's up to you. Approx cost from aliexpress is £1/unit

- 2 x 7 segment display boards 0.56" 8 displays on a board Approx cost from aliexpress is £1.40/unit dependant on colour selected.

- 1 x LCD display with backpack Approx cost from aliexpress is £5/unit

- 1 x DS3231 module Approx cost from aliexpress is £0.90/unit

- 1 x buck converter for power Approx cost from aliexpress is £1/unit

- 1 x MSF receiver (CANADUINO) £11.18 + shipping (£5.40) - cost more than the price of getting the "motherboard" made, takes a long time to arrive. No other suppliers found as alternative. This cqan be swapped out for the DCF77 board if you want to use the DCF77 time signal (code changes required, same price
though)

- LED strip of WS2812B I picked up a 1 metre strip with 60 leds on it for £4.25 from aliexpress.

- Various header pins and headers these work out at about £0.15 each from aliexpress but I just got a box of them from an Amazon seller.

- An old (or new) quartz clock mechanism.

- PCB cost￡9.85 + ￡5.22 shipping that's for the minimum oquantity of 5 boards.


You can get these parts at places like amazon for slightly inflated prices but without the 2 week wait - sometimes prices are the same so shop around.


Without access to something like [JLCPCB](https://jlcpcb.com/) [No, they didn't sponsor me] none of this would have really happened - it would have been another rats nest of wires project that survived for a limited time before repurposing the Arudino. Access to services like this make a huge difference to people starting out and the existance of software like [kICad](https://kicad-pcb.org/) makes the process of design to physical board simple. How many newbies would fork out £100's for pcb design software if they were just trying something out? KiCad is free and it's awesome and major component suppliers support the library format too.



# Issues

The biggest issue you are going to face is getting a good signal from Anthorn (Cumbria) - (or your location for WWVB, JJY). My workspace/office has lots of electrical equipment in it which interferes with the signal. Nothing during the day (the sun buggers up the signal) but better at night in with the receiver near a window. The antenna should be at 90 degrees to the expected signal path for best reception. Rotating it 90 degrees can change the signal level by 20-30dB. Initially my results were great but they have got steadily worse with a sync taking place maybe twice a fortnight if I'm lucky.

**The current big issue is the arduino internal clock is losing about 3 minutes / hour if I don't resync with the DS3231, resyncing causes a pause and jump in the 7 segment/lcd display which is obviously not acceptable. I'm investigating this.**
