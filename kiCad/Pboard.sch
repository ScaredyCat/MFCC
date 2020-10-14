EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 8250 7750 0    50   Input ~ 0
GND
Text GLabel 10150 7450 2    50   Input ~ 0
LEDDATA
$Comp
L Connector_Generic:Conn_01x02 CLOCK1
U 1 1 5F4FCC9E
P 10350 9150
F 0 "CLOCK1" H 10430 9142 50  0000 L CNN
F 1 "Conn_01x02" H 10430 9051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10350 9150 50  0001 C CNN
F 3 "~" H 10350 9150 50  0001 C CNN
	1    10350 9150
	1    0    0    -1  
$EndComp
Text GLabel 10150 9150 0    50   Input ~ 0
CLOCKA
Text GLabel 10150 9250 0    50   Input ~ 0
CLOCKB
Text GLabel 10150 7950 2    50   Input ~ 0
MSF
$Comp
L Connector_Generic:Conn_01x05 SPI1
U 1 1 5F526A8C
P 10700 5200
F 0 "SPI1" H 10780 5242 50  0000 L CNN
F 1 "Conn_01x05" H 10780 5151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 10700 5200 50  0001 C CNN
F 3 "~" H 10700 5200 50  0001 C CNN
	1    10700 5200
	1    0    0    -1  
$EndComp
Text GLabel 9100 6350 0    50   Input ~ 0
MISO-NR
Text GLabel 9100 6450 0    50   Input ~ 0
SCK-NR
Text GLabel 10150 6350 2    50   Input ~ 0
VCC-NR
Text GLabel 10150 6450 2    50   Input ~ 0
MOSI-NR
Text GLabel 10150 6550 2    50   Input ~ 0
GND-NR
Text GLabel 10500 5300 0    50   Input ~ 0
GND
Text GLabel 10500 5100 0    50   Input ~ 0
VCC
Text GLabel 10500 5200 0    50   Input ~ 0
MOSI-NR
Text GLabel 10500 5400 0    50   Input ~ 0
SCK-NR
Text GLabel 10500 5000 0    50   Input ~ 0
MISO-NR
$Comp
L Connector_Generic:Conn_01x04 I2C1
U 1 1 5F529CDC
P 11800 6600
F 0 "I2C1" H 11880 6592 50  0000 L CNN
F 1 "Conn_01x04" H 11880 6501 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 11800 6600 50  0001 C CNN
F 3 "~" H 11800 6600 50  0001 C CNN
	1    11800 6600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 I2C3
U 1 1 5F52BCF3
P 11800 7050
F 0 "I2C3" H 11880 7042 50  0000 L CNN
F 1 "Conn_01x04" H 11880 6951 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 11800 7050 50  0001 C CNN
F 3 "~" H 11800 7050 50  0001 C CNN
	1    11800 7050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 I2C5
U 1 1 5F52C063
P 11800 7550
F 0 "I2C5" H 11880 7542 50  0000 L CNN
F 1 "Conn_01x04" H 11880 7451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 11800 7550 50  0001 C CNN
F 3 "~" H 11800 7550 50  0001 C CNN
	1    11800 7550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 I2C2
U 1 1 5F52D50F
P 12900 6650
F 0 "I2C2" H 12980 6642 50  0000 L CNN
F 1 "Conn_01x04" H 12980 6551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 12900 6650 50  0001 C CNN
F 3 "~" H 12900 6650 50  0001 C CNN
	1    12900 6650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 I2C4
U 1 1 5F52D93B
P 12900 7150
F 0 "I2C4" H 12980 7142 50  0000 L CNN
F 1 "Conn_01x04" H 12980 7051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 12900 7150 50  0001 C CNN
F 3 "~" H 12900 7150 50  0001 C CNN
	1    12900 7150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 I2C6
U 1 1 5F52DE54
P 12900 7650
F 0 "I2C6" H 12980 7642 50  0000 L CNN
F 1 "Conn_01x04" H 12980 7551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 12900 7650 50  0001 C CNN
F 3 "~" H 12900 7650 50  0001 C CNN
	1    12900 7650
	1    0    0    -1  
$EndComp
Text GLabel 11600 7750 0    50   Input ~ 0
GND
Text GLabel 12700 7850 0    50   Input ~ 0
GND
Text GLabel 12700 7350 0    50   Input ~ 0
GND
Text GLabel 11600 7250 0    50   Input ~ 0
GND
Text GLabel 12700 6850 0    50   Input ~ 0
GND
Text GLabel 11600 6800 0    50   Input ~ 0
GND
Text GLabel 11600 7650 0    50   Input ~ 0
VCC
Text GLabel 12700 7750 0    50   Input ~ 0
VCC
Text GLabel 12700 7250 0    50   Input ~ 0
VCC
Text GLabel 12700 6750 0    50   Input ~ 0
VCC
Text GLabel 11600 7150 0    50   Input ~ 0
VCC
Text GLabel 11600 6700 0    50   Input ~ 0
VCC
Text GLabel 11600 6600 0    50   Input ~ 0
SDA
Text GLabel 12700 6650 0    50   Input ~ 0
SDA
Text GLabel 12700 7150 0    50   Input ~ 0
SDA
Text GLabel 11600 7050 0    50   Input ~ 0
SDA
Text GLabel 12700 7650 0    50   Input ~ 0
SDA
Text GLabel 11600 7550 0    50   Input ~ 0
SDA
Text GLabel 11600 6500 0    50   Input ~ 0
SCL
Text GLabel 12700 6550 0    50   Input ~ 0
SCL
Text GLabel 11600 6950 0    50   Input ~ 0
SCL
Text GLabel 12700 7050 0    50   Input ~ 0
SCL
Text GLabel 11600 7450 0    50   Input ~ 0
SCL
Text GLabel 12700 7550 0    50   Input ~ 0
SCL
Text GLabel 8250 8350 0    50   Input ~ 0
LCDBACKLIGHT
Text GLabel 8250 8150 0    50   Input ~ 0
TICKTOCK
Text GLabel 8250 8250 0    50   Input ~ 0
CHIMES
Text GLabel 8250 8450 0    50   Input ~ 0
ADVANCE
Text GLabel 8250 8550 0    50   Input ~ 0
RETARD
Text GLabel 10150 7750 2    50   Input ~ 0
JQTX
Text GLabel 10150 8150 2    50   Input ~ 0
JQRX
Text GLabel 10150 7650 2    50   Input ~ 0
CLOCKA
Text GLabel 10150 7550 2    50   Input ~ 0
CLOCKB
Text GLabel 10150 7350 2    50   Input ~ 0
JQTICKTOCK
$Comp
L Connector_Generic:Conn_01x01 RGBGND1
U 1 1 5F497676
P 13750 9000
F 0 "RGBGND1" H 13830 9042 50  0000 L CNN
F 1 "Conn_01x01" H 13830 8951 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 13750 9000 50  0001 C CNN
F 3 "~" H 13750 9000 50  0001 C CNN
	1    13750 9000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 RGBDIN1
U 1 1 5F4978E6
P 13750 9350
F 0 "RGBDIN1" H 13830 9392 50  0000 L CNN
F 1 "Conn_01x01" H 13830 9301 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 13750 9350 50  0001 C CNN
F 3 "~" H 13750 9350 50  0001 C CNN
	1    13750 9350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 RGBVCC1
U 1 1 5F497B14
P 13750 8700
F 0 "RGBVCC1" H 13830 8742 50  0000 L CNN
F 1 "Conn_01x01" H 13830 8651 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 13750 8700 50  0001 C CNN
F 3 "~" H 13750 8700 50  0001 C CNN
	1    13750 8700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F4A29B0
P 13150 9350
F 0 "R1" V 12943 9350 50  0000 C CNN
F 1 "330" V 13034 9350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13080 9350 50  0001 C CNN
F 3 "~" H 13150 9350 50  0001 C CNN
	1    13150 9350
	0    1    1    0   
$EndComp
Wire Wire Line
	13550 9350 13300 9350
Wire Wire Line
	12800 9350 13000 9350
$Comp
L Device:CP C1
U 1 1 5F4ACFB8
P 13150 8850
F 0 "C1" H 13268 8896 50  0000 L CNN
F 1 "1000uF" H 13268 8805 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D7.5mm_P2.50mm" H 13188 8700 50  0001 C CNN
F 3 "~" H 13150 8850 50  0001 C CNN
	1    13150 8850
	1    0    0    -1  
$EndComp
Wire Wire Line
	13550 9000 13150 9000
Wire Wire Line
	12800 9000 13150 9000
Connection ~ 13150 9000
Wire Wire Line
	13550 8700 13150 8700
Wire Wire Line
	12800 8700 13150 8700
Connection ~ 13150 8700
Text GLabel 12800 8700 0    50   Input ~ 0
VCC
Text GLabel 12800 9000 0    50   Input ~ 0
GND
Text GLabel 12800 9350 0    50   Input ~ 0
LEDDATA
Text GLabel 10150 8250 2    50   Input ~ 0
PON
Text GLabel 8250 7650 0    50   Input ~ 0
VCC
Text GLabel 3100 3450 2    50   Input ~ 0
SPK+
Text GLabel 2600 3100 1    50   Input ~ 0
VCC
Text GLabel 2650 4500 3    50   Input ~ 0
GND
Text GLabel 2550 4500 3    50   Input ~ 0
GND
Text GLabel 3100 4050 2    50   Input ~ 0
TX
Text GLabel 3100 4150 2    50   Input ~ 0
RX
Text GLabel 2100 3950 0    50   Input ~ 0
ADKEY
Text GLabel 2100 3450 0    50   Input ~ 0
K1
Text GLabel 2100 3550 0    50   Input ~ 0
K2
Text GLabel 2100 3650 0    50   Input ~ 0
K3
Text GLabel 2100 3750 0    50   Input ~ 0
K4
Text GLabel 2100 3850 0    50   Input ~ 0
K5
Text GLabel 3100 3850 2    50   Input ~ 0
DACR
$Comp
L Connector_Generic:Conn_01x02 SP1
U 1 1 5F5494BA
P 4850 4850
F 0 "SP1" H 4930 4842 50  0000 L CNN
F 1 "Speaker" H 4930 4751 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4850 4850 50  0001 C CNN
F 3 "~" H 4850 4850 50  0001 C CNN
	1    4850 4850
	1    0    0    -1  
$EndComp
Text GLabel 4650 4850 0    50   Input ~ 0
SPK+
Text GLabel 4650 4950 0    50   Input ~ 0
SPK-
$Comp
L Device:R R6
U 1 1 5F54A66E
P 4650 5550
F 0 "R6" V 4750 5550 50  0000 C CNN
F 1 "R1K" V 4800 5550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 4580 5550 50  0001 C CNN
F 3 "~" H 4650 5550 50  0001 C CNN
	1    4650 5550
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F54BA8F
P 3100 6550
F 0 "R2" V 2893 6550 50  0000 C CNN
F 1 "100K" V 2984 6550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3030 6550 50  0001 C CNN
F 3 "~" H 3100 6550 50  0001 C CNN
	1    3100 6550
	0    1    1    0   
$EndComp
Text GLabel 4500 5550 0    50   Input ~ 0
RX
Text GLabel 4700 5350 0    50   Input ~ 0
TX
Wire Wire Line
	4800 5550 5000 5550
$Comp
L Device:D D1
U 1 1 5F55683D
P 2800 6550
F 0 "D1" H 2800 6767 50  0000 C CNN
F 1 "D" H 2800 6676 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" H 2800 6550 50  0001 C CNN
F 3 "~" H 2800 6550 50  0001 C CNN
	1    2800 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F55A3FA
P 3050 6900
F 0 "R4" V 2843 6900 50  0000 C CNN
F 1 "6.2k" V 2934 6900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2980 6900 50  0001 C CNN
F 3 "~" H 3050 6900 50  0001 C CNN
	1    3050 6900
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 5F55B85B
P 3100 7200
F 0 "R5" V 2893 7200 50  0000 C CNN
F 1 "3.3K" V 2984 7200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3030 7200 50  0001 C CNN
F 3 "~" H 3100 7200 50  0001 C CNN
	1    3100 7200
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 6900 2650 6900
Wire Wire Line
	2650 6900 2650 6800
Wire Wire Line
	2650 6800 2400 6800
Wire Wire Line
	2950 7200 2400 7200
Wire Wire Line
	2400 7200 2400 6900
Text GLabel 3750 6850 2    50   Input ~ 0
ADKEY
Wire Wire Line
	3250 7200 3500 7200
Wire Wire Line
	3500 6850 3750 6850
Wire Wire Line
	3250 6550 3500 6550
Wire Wire Line
	3500 6550 3500 6850
Connection ~ 3500 6850
Wire Wire Line
	3500 6850 3500 7200
Wire Wire Line
	3500 6850 3250 6850
Wire Wire Line
	3250 6850 3250 6900
Wire Wire Line
	3250 6900 3200 6900
$Comp
L Connector_Generic:Conn_01x03 AM1
U 1 1 5F56FEB1
P 4200 6000
F 0 "AM1" H 4280 6042 50  0000 L CNN
F 1 "Amp" H 4280 5951 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4200 6000 50  0001 C CNN
F 3 "~" H 4200 6000 50  0001 C CNN
	1    4200 6000
	1    0    0    -1  
$EndComp
Text GLabel 4000 5900 0    50   Input ~ 0
DACL
Text GLabel 4000 6000 0    50   Input ~ 0
DACR
Text GLabel 4000 6100 0    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_01x05 KG1
U 1 1 5F572AD8
P 6250 4550
F 0 "KG1" H 6330 4592 50  0000 L CNN
F 1 "Keys" H 6330 4501 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 6250 4550 50  0001 C CNN
F 3 "~" H 6250 4550 50  0001 C CNN
	1    6250 4550
	1    0    0    -1  
$EndComp
Text GLabel 6050 4350 0    50   Input ~ 0
K1
Text GLabel 6050 4450 0    50   Input ~ 0
K2
Text GLabel 6050 4550 0    50   Input ~ 0
K3
Text GLabel 6050 4650 0    50   Input ~ 0
K4
Text GLabel 6050 4750 0    50   Input ~ 0
K5
$Comp
L Mechanical:MountingHole H1
U 1 1 5F576D54
P 2400 2300
F 0 "H1" H 2500 2346 50  0000 L CNN
F 1 "MountingHole" H 2500 2255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2400 2300 50  0001 C CNN
F 3 "~" H 2400 2300 50  0001 C CNN
	1    2400 2300
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5F5780B1
P 2650 2300
F 0 "H2" H 2750 2346 50  0000 L CNN
F 1 "MountingHole" H 2750 2255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2650 2300 50  0001 C CNN
F 3 "~" H 2650 2300 50  0001 C CNN
	1    2650 2300
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5F578588
P 2900 2300
F 0 "H3" H 3000 2346 50  0000 L CNN
F 1 "MountingHole" H 3000 2255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2900 2300 50  0001 C CNN
F 3 "~" H 2900 2300 50  0001 C CNN
	1    2900 2300
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5F578BC9
P 3200 2300
F 0 "H4" H 3300 2346 50  0000 L CNN
F 1 "MountingHole" H 3300 2255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 3200 2300 50  0001 C CNN
F 3 "~" H 3200 2300 50  0001 C CNN
	1    3200 2300
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole H5
U 1 1 5F578FF6
P 3500 2300
F 0 "H5" H 3600 2346 50  0000 L CNN
F 1 "MountingHole" H 3600 2255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 3500 2300 50  0001 C CNN
F 3 "~" H 3500 2300 50  0001 C CNN
	1    3500 2300
	0    -1   -1   0   
$EndComp
Text GLabel 3100 3550 2    50   Input ~ 0
SPK-
Text GLabel 3100 3750 2    50   Input ~ 0
DACL
$Comp
L Connector_Generic:Conn_01x06 TRIG1
U 1 1 5F5FF607
P 7500 9400
F 0 "TRIG1" H 7580 9442 50  0000 L CNN
F 1 "Conn_01x06" H 7580 9351 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7500 9400 50  0001 C CNN
F 3 "~" H 7500 9400 50  0001 C CNN
	1    7500 9400
	1    0    0    -1  
$EndComp
Text GLabel 7300 9200 0    50   Input ~ 0
TICKTOCK
Text GLabel 7300 9300 0    50   Input ~ 0
CHIMES
Text GLabel 7300 9400 0    50   Input ~ 0
LCDBACKLIGHT
Text GLabel 7300 9500 0    50   Input ~ 0
ADVANCE
Text GLabel 7300 9600 0    50   Input ~ 0
RETARD
$Comp
L Connector_Generic:Conn_01x06 TRIG1G1
U 1 1 5F602255
P 6050 9800
F 0 "TRIG1G1" H 5968 10217 50  0000 C CNN
F 1 "Conn_01x06" H 5968 10126 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 6050 9800 50  0001 C CNN
F 3 "~" H 6050 9800 50  0001 C CNN
	1    6050 9800
	-1   0    0    -1  
$EndComp
Text GLabel 6250 9600 2    50   Input ~ 0
GND
Text GLabel 6250 9700 2    50   Input ~ 0
GND
Text GLabel 6250 9800 2    50   Input ~ 0
GND
Text GLabel 6250 9900 2    50   Input ~ 0
GND
Text GLabel 6250 10000 2    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_01x02 AKO1G1
U 1 1 5F60C1C5
P 1550 6750
F 0 "AKO1G1" H 1630 6742 50  0000 L CNN
F 1 "Conn_01x02" H 1630 6651 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1550 6750 50  0001 C CNN
F 3 "~" H 1550 6750 50  0001 C CNN
	1    1550 6750
	1    0    0    -1  
$EndComp
Text GLabel 1350 6750 0    50   Input ~ 0
GND
Text GLabel 1350 6850 0    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_01x02 AKO1Vol1
U 1 1 5F60DE15
P 2200 6800
F 0 "AKO1Vol1" H 2118 7017 50  0000 C CNN
F 1 "Conn_01x02" H 2118 6926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2200 6800 50  0001 C CNN
F 3 "~" H 2200 6800 50  0001 C CNN
	1    2200 6800
	-1   0    0    -1  
$EndComp
Text GLabel 2650 6550 1    50   Input ~ 0
JQTICKTOCK
$Comp
L Connector_Generic:Conn_01x05 MSFCTL1
U 1 1 5F610F91
P 6650 7600
F 0 "MSFCTL1" H 6600 8000 50  0000 L CNN
F 1 "Conn_01x05" H 6450 7300 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 6650 7600 50  0001 C CNN
F 3 "~" H 6650 7600 50  0001 C CNN
	1    6650 7600
	-1   0    0    -1  
$EndComp
Text GLabel 6850 7400 2    50   Input ~ 0
VCC
Text GLabel 6850 7600 2    50   Input ~ 0
PON
Text GLabel 6850 7700 2    50   Input ~ 0
MSF
Text GLabel 6850 7800 2    50   Input ~ 0
GND
Text GLabel 11150 8450 2    50   Input ~ 0
AON
Text GLabel 5000 5350 2    50   Input ~ 0
JQTX
Text GLabel 5000 5550 2    50   Input ~ 0
JQRX
Text GLabel 10150 6850 2    50   Input ~ 0
SCL
Text GLabel 10150 6950 2    50   Input ~ 0
SDA
Text GLabel 6850 7500 2    50   Input ~ 0
AON
$Comp
L Mechanical:MountingHole H6
U 1 1 5F64BB4A
P 3800 2300
F 0 "H6" H 3900 2346 50  0000 L CNN
F 1 "MountingHole" H 3900 2255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 3800 2300 50  0001 C CNN
F 3 "~" H 3800 2300 50  0001 C CNN
	1    3800 2300
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole H7
U 1 1 5F64C134
P 4050 2350
F 0 "H7" H 4150 2396 50  0000 L CNN
F 1 "MountingHole" H 4150 2305 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 4050 2350 50  0001 C CNN
F 3 "~" H 4050 2350 50  0001 C CNN
	1    4050 2350
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole H8
U 1 1 5F64C61F
P 4400 2600
F 0 "H8" H 4500 2646 50  0000 L CNN
F 1 "MountingHole" H 4500 2555 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 4400 2600 50  0001 C CNN
F 3 "~" H 4400 2600 50  0001 C CNN
	1    4400 2600
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole H9
U 1 1 5F64CAD7
P 4750 2400
F 0 "H9" H 4850 2446 50  0000 L CNN
F 1 "MountingHole" H 4850 2355 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 4750 2400 50  0001 C CNN
F 3 "~" H 4750 2400 50  0001 C CNN
	1    4750 2400
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 VCC1
U 1 1 5F67DF14
P 2050 10600
F 0 "VCC1" H 2150 10600 50  0000 L CNN
F 1 "Conn_01x01" H 2130 10551 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2050 10600 50  0001 C CNN
F 3 "~" H 2050 10600 50  0001 C CNN
	1    2050 10600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 GND1
U 1 1 5F67EBD3
P 2050 10700
F 0 "GND1" H 2150 10700 50  0000 L CNN
F 1 "Conn_01x01" H 2130 10651 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2050 10700 50  0001 C CNN
F 3 "~" H 2050 10700 50  0001 C CNN
	1    2050 10700
	1    0    0    -1  
$EndComp
Text GLabel 1850 10600 0    50   Input ~ 0
VCC
Text GLabel 1850 10700 0    50   Input ~ 0
GND
Text GLabel 8250 8650 0    50   Input ~ 0
BCKLITETRIG
Text GLabel 6250 10100 2    50   Input ~ 0
GND
Text GLabel 7300 9700 0    50   Input ~ 0
BCKLITETRIG
Text GLabel 10150 8050 2    50   Input ~ 0
SEGMENT
Text GLabel 8300 1800 2    50   Input ~ 0
SPK+-2
Text GLabel 7800 1450 1    50   Input ~ 0
VCC
Text GLabel 7850 2850 3    50   Input ~ 0
GND
Text GLabel 7750 2850 3    50   Input ~ 0
GND
Text GLabel 8300 2400 2    50   Input ~ 0
TX-2
Text GLabel 8300 2500 2    50   Input ~ 0
RX-2
Text GLabel 7300 1800 0    50   Input ~ 0
K1-2
Text GLabel 7300 1900 0    50   Input ~ 0
K2-2
Text GLabel 7300 2000 0    50   Input ~ 0
K3-2
Text GLabel 7300 2100 0    50   Input ~ 0
K4-2
Text GLabel 7300 2200 0    50   Input ~ 0
K5-2
Text GLabel 8300 2200 2    50   Input ~ 0
DACR-2
$Comp
L Connector_Generic:Conn_01x02 SP2
U 1 1 5F6B90B5
P 11800 1650
F 0 "SP2" H 11880 1642 50  0000 L CNN
F 1 "Speaker" H 11880 1551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 11800 1650 50  0001 C CNN
F 3 "~" H 11800 1650 50  0001 C CNN
	1    11800 1650
	1    0    0    -1  
$EndComp
Text GLabel 11600 1650 0    50   Input ~ 0
SPK+-2
Text GLabel 11600 1750 0    50   Input ~ 0
SPK--2
$Comp
L Device:R R-2
U 1 1 5F6B90BD
P 11600 2350
F 0 "R-2" V 11800 2350 50  0000 C CNN
F 1 "R1K" V 11700 2350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 11530 2350 50  0001 C CNN
F 3 "~" H 11600 2350 50  0001 C CNN
	1    11600 2350
	0    1    1    0   
$EndComp
Text GLabel 11450 2350 0    50   Input ~ 0
RX-2
Text GLabel 11550 2250 0    50   Input ~ 0
TX-2
Wire Wire Line
	11750 2350 11950 2350
$Comp
L Connector_Generic:Conn_01x03 AM2
U 1 1 5F6B90ED
P 11150 2800
F 0 "AM2" H 11230 2842 50  0000 L CNN
F 1 "Amp" H 11230 2751 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 11150 2800 50  0001 C CNN
F 3 "~" H 11150 2800 50  0001 C CNN
	1    11150 2800
	1    0    0    -1  
$EndComp
Text GLabel 10950 2700 0    50   Input ~ 0
DACL-2
Text GLabel 10950 2800 0    50   Input ~ 0
DACR-2
Text GLabel 10950 2900 0    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_01x05 KG2
U 1 1 5F6B90F6
P 13200 1350
F 0 "KG2" H 13280 1392 50  0000 L CNN
F 1 "Keys" H 13280 1301 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 13200 1350 50  0001 C CNN
F 3 "~" H 13200 1350 50  0001 C CNN
	1    13200 1350
	1    0    0    -1  
$EndComp
Text GLabel 13000 1150 0    50   Input ~ 0
K1-2
Text GLabel 13000 1250 0    50   Input ~ 0
K2-2
Text GLabel 13000 1350 0    50   Input ~ 0
K3-2
Text GLabel 13000 1450 0    50   Input ~ 0
K4-2
Text GLabel 13000 1550 0    50   Input ~ 0
K5-2
Text GLabel 8300 1900 2    50   Input ~ 0
SPK--2
Text GLabel 8300 2100 2    50   Input ~ 0
DACL-2
Text GLabel 11850 2250 2    50   Input ~ 0
JQTX
Text GLabel 11950 2350 2    50   Input ~ 0
JQRX
$Comp
L Jumper:SolderJumper_2_Open TXJ2
U 1 1 5F6BA953
P 11700 2250
F 0 "TXJ2" H 11700 2455 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 11700 2364 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 11700 2250 50  0001 C CNN
F 3 "~" H 11700 2250 50  0001 C CNN
	1    11700 2250
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open TXJP1
U 1 1 5F6BE6E6
P 4850 5350
F 0 "TXJP1" H 4850 5555 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 4850 5464 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 4850 5350 50  0001 C CNN
F 3 "~" H 4850 5350 50  0001 C CNN
	1    4850 5350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 SECMENTCTL1
U 1 1 5F7F8F03
P 12450 4200
F 0 "SECMENTCTL1" H 12530 4242 50  0000 L CNN
F 1 "Conn_01x01" H 12530 4151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 12450 4200 50  0001 C CNN
F 3 "~" H 12450 4200 50  0001 C CNN
	1    12450 4200
	1    0    0    -1  
$EndComp
Text GLabel 12250 4200 0    50   Input ~ 0
SEGMENT
$Comp
L Jumper:SolderJumper_2_Open AONORCLOCK2
U 1 1 5F7FB531
P 11000 8450
F 0 "AONORCLOCK2" H 11000 8655 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 11000 8564 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 11000 8450 50  0001 C CNN
F 3 "~" H 11000 8450 50  0001 C CNN
	1    11000 8450
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 CLOCK2
U 1 1 5F7FC6C1
P 10400 9650
F 0 "CLOCK2" H 10480 9642 50  0000 L CNN
F 1 "Conn_01x02" H 10480 9551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10400 9650 50  0001 C CNN
F 3 "~" H 10400 9650 50  0001 C CNN
	1    10400 9650
	1    0    0    -1  
$EndComp
Text GLabel 10200 9650 0    50   Input ~ 0
CLOCKC
Text GLabel 10200 9750 0    50   Input ~ 0
CLOCKD
Text GLabel 10150 8350 2    50   Input ~ 0
CLOCKC
Text GLabel 11150 8850 2    50   Input ~ 0
CLOCKD
$Comp
L Jumper:SolderJumper_2_Open CLOCK2ORAON2
U 1 1 5F80147F
P 11000 8850
F 0 "CLOCK2ORAON2" H 11000 9055 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 11000 8964 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 11000 8850 50  0001 C CNN
F 3 "~" H 11000 8850 50  0001 C CNN
	1    11000 8850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10850 8850 10850 8450
Connection ~ 10850 8450
Wire Wire Line
	10850 8450 10750 8450
$Comp
L freetronics_schematic:ARDUINO_SHIELD SHIELD1
U 1 1 5F4E964F
P 9200 7850
F 0 "SHIELD1" H 9200 9703 60  0000 C CNN
F 1 "ARDUINO_SHIELD" H 9200 9597 60  0000 C CNN
F 2 "freetronics_footprints:ARDUINO_SHIELD" H 9200 7650 50  0001 C CNN
F 3 "http://www.thingiverse.com/thing:9630" H 9200 9491 60  0001 C CNN
	1    9200 7850
	1    0    0    -1  
$EndComp
NoConn ~ 8250 7250
Wire Wire Line
	10150 8450 10850 8450
NoConn ~ 8250 7350
NoConn ~ 8250 7450
NoConn ~ 8250 7550
NoConn ~ 8250 7950
NoConn ~ 10150 7050
NoConn ~ 10150 7250
NoConn ~ 9100 6550
NoConn ~ 10150 8550
NoConn ~ 10150 8650
NoConn ~ 9050 2300
NoConn ~ 9050 2200
$Comp
L Mechanical:MountingHole H10
U 1 1 5F817CDC
P 5150 2400
F 0 "H10" H 5250 2446 50  0000 L CNN
F 1 "MountingHole" H 5250 2355 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5150 2400 50  0001 C CNN
F 3 "~" H 5150 2400 50  0001 C CNN
	1    5150 2400
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 PWRBUCK1
U 1 1 5F82FEB1
P 3550 9250
F 0 "PWRBUCK1" H 3630 9242 50  0000 L CNN
F 1 "Conn_01x02" H 3630 9151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3550 9250 50  0001 C CNN
F 3 "~" H 3550 9250 50  0001 C CNN
	1    3550 9250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 PWRINB1
U 1 1 5F830FE6
P 1950 8400
F 0 "PWRINB1" V 2150 8350 50  0000 C CNN
F 1 "Screw_Terminal_01x02" V 2350 8400 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 1950 8400 50  0001 C CNN
F 3 "~" H 1950 8400 50  0001 C CNN
	1    1950 8400
	-1   0    0    1   
$EndComp
$Comp
L Device:D D2
U 1 1 5F842498
P 2600 8300
F 0 "D2" H 2600 8083 50  0000 C CNN
F 1 "D" H 2600 8174 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P10.16mm_Horizontal" H 2600 8300 50  0001 C CNN
F 3 "~" H 2600 8300 50  0001 C CNN
	1    2600 8300
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C2
U 1 1 5F843842
P 3000 8650
F 0 "C2" H 3118 8696 50  0000 L CNN
F 1 "4.7" H 3118 8605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3038 8500 50  0001 C CNN
F 3 "~" H 3000 8650 50  0001 C CNN
	1    3000 8650
	1    0    0    -1  
$EndComp
Text GLabel 3800 8300 2    50   Input ~ 0
PBVCC
Text GLabel 3000 8800 3    50   Input ~ 0
INGND
$Comp
L Connector_Generic:Conn_01x02 WOOKIE1
U 1 1 5F59525E
P 8950 9600
F 0 "WOOKIE1" H 9030 9592 50  0000 L CNN
F 1 "Conn_01x02" H 9030 9501 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8950 9600 50  0001 C CNN
F 3 "~" H 8950 9600 50  0001 C CNN
	1    8950 9600
	1    0    0    -1  
$EndComp
Text GLabel 8750 9600 0    50   Input ~ 0
VCC
Text GLabel 8750 9700 0    50   Input ~ 0
GND
$Comp
L Device:Fuse F1
U 1 1 5F5B688E
P 2300 8300
F 0 "F1" V 2103 8300 50  0000 C CNN
F 1 "3A" V 2194 8300 50  0000 C CNN
F 2 "Fuse:Fuseholder_Cylinder-5x20mm_Stelvio-Kontek_PTF78_Horizontal_Open" V 2230 8300 50  0001 C CNN
F 3 "~" H 2300 8300 50  0001 C CNN
	1    2300 8300
	0    1    1    0   
$EndComp
Text GLabel 3350 9250 0    50   Input ~ 0
PBVCC
Wire Wire Line
	3000 8500 3000 8300
Wire Wire Line
	2750 8300 3000 8300
Text GLabel 2150 8400 3    50   Input ~ 0
INGND
Text GLabel 3350 9350 3    50   Input ~ 0
INGND
NoConn ~ 10150 7150
NoConn ~ 8250 7850
$Comp
L gtrzps:JQ6500-16P_Module U1
U 1 1 5F6B399C
P 7800 2150
F 0 "U1" H 7800 3350 50  0000 C CNN
F 1 "JQ6500-16P_Module" H 7800 3250 50  0000 C CNN
F 2 "gtrzps:JQ6500_2x8_P2.54mm" H 7600 2800 50  0001 C CNN
F 3 "https://sparks.gogo.co.nz/jq6500/index.html" H 7600 2800 50  0001 C CNN
	1    7800 2150
	1    0    0    -1  
$EndComp
$Comp
L gtrzps:JQ6500-16P_Module U2
U 1 1 5F6B6166
P 2600 3800
F 0 "U2" H 2950 4650 50  0000 C CNN
F 1 "JQ6500-16P_Module" H 3100 4550 50  0000 C CNN
F 2 "gtrzps:JQ6500_2x8_P2.54mm" H 2400 4450 50  0001 C CNN
F 3 "https://sparks.gogo.co.nz/jq6500/index.html" H 2400 4450 50  0001 C CNN
	1    2600 3800
	1    0    0    -1  
$EndComp
NoConn ~ 2100 4150
NoConn ~ 10150 6550
NoConn ~ 10150 6350
NoConn ~ 7300 2300
NoConn ~ 7300 2500
Connection ~ 3000 8300
Wire Wire Line
	3000 8300 3800 8300
$EndSCHEMATC
