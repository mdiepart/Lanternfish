EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Lanternfish"
Date "2020-06-20"
Rev ""
Comp ""
Comment1 "Fish tank programmable light dimmer"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Display_Character:WC1602A DS1
U 1 1 5EEE3A5B
P 9600 3200
F 0 "DS1" H 9850 2450 50  0000 C CNN
F 1 "LCM1602" H 9350 3950 50  0000 C CNN
F 2 "lanternfish:lcm1602" H 9600 2300 50  0001 C CIN
F 3 "http://www.wincomlcd.com/pdf/WC1602A-SFYLYHTC06.pdf" H 10300 3200 50  0001 C CNN
	1    9600 3200
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7805 U2
U 1 1 5EEE4FF2
P 2900 1100
F 0 "U2" H 2900 1342 50  0000 C CNN
F 1 "L7805" H 2900 1251 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 2925 950 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 2900 1050 50  0001 C CNN
	1    2900 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_GDS Q1
U 1 1 5EEE57CC
P 1600 1200
F 0 "Q1" V 1500 1000 50  0000 L CNN
F 1 "FQD17P06TM" V 1850 950 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 1800 1300 50  0001 C CNN
F 3 "~" H 1600 1200 50  0001 C CNN
	1    1600 1200
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5EEE8284
P 1150 1100
F 0 "J1" H 1230 1092 50  0000 L CNN
F 1 "Input" H 1230 1001 50  0000 L CNN
F 2 "lanternfish:MC000048" H 1150 1100 50  0001 C CNN
F 3 "~" H 1150 1100 50  0001 C CNN
	1    1150 1100
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR018
U 1 1 5EEEDD0E
P 3400 1100
F 0 "#PWR018" H 3400 950 50  0001 C CNN
F 1 "+5V" H 3415 1273 50  0000 C CNN
F 2 "" H 3400 1100 50  0001 C CNN
F 3 "" H 3400 1100 50  0001 C CNN
	1    3400 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5EEEED37
P 950 3250
F 0 "BT1" H 1068 3346 50  0000 L CNN
F 1 "Battery_Cell" H 1068 3255 50  0000 L CNN
F 2 "lanternfish:Renata_cr2032_CMS" V 950 3310 50  0001 C CNN
F 3 "~" V 950 3310 50  0001 C CNN
	1    950  3250
	1    0    0    -1  
$EndComp
$Comp
L Timer:MCP7940N-xMS U1
U 1 1 5EEF09D7
P 2150 3150
F 0 "U1" H 2450 2750 50  0000 C CNN
F 1 "MCP7940N-xMS" H 1800 2800 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2150 3150 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20005010F.pdf" H 2150 3150 50  0001 C CNN
	1    2150 3150
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATmega:ATmega328PB-AU U3
U 1 1 5EEF1B5F
P 5850 3500
F 0 "U3" H 6300 2050 50  0000 C CNN
F 1 "ATmega328PB-AU" H 5800 4450 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 5850 3500 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/40001906C.pdf" H 5850 3500 50  0001 C CNN
	1    5850 3500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW6
U 1 1 5EEF44A7
P 5550 6800
F 0 "SW6" H 5550 7035 50  0000 C CNN
F 1 "SW_SPST" H 5550 6944 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5550 6800 50  0001 C CNN
F 3 "~" H 5550 6800 50  0001 C CNN
	1    5550 6800
	0    -1   -1   0   
$EndComp
$Comp
L power:VDD #PWR014
U 1 1 5EEF7C12
P 2550 1100
F 0 "#PWR014" H 2550 950 50  0001 C CNN
F 1 "VDD" H 2565 1273 50  0000 C CNN
F 2 "" H 2550 1100 50  0001 C CNN
F 3 "" H 2550 1100 50  0001 C CNN
	1    2550 1100
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR01
U 1 1 5EEFD610
P 950 3050
F 0 "#PWR01" H 950 2900 50  0001 C CNN
F 1 "+BATT" H 965 3223 50  0000 C CNN
F 2 "" H 950 3050 50  0001 C CNN
F 3 "" H 950 3050 50  0001 C CNN
	1    950  3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5EEFE8A0
P 950 3350
F 0 "#PWR02" H 950 3100 50  0001 C CNN
F 1 "GND" H 955 3177 50  0000 C CNN
F 2 "" H 950 3350 50  0001 C CNN
F 3 "" H 950 3350 50  0001 C CNN
	1    950  3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3300 2700 3250
Wire Wire Line
	2700 3250 2550 3250
Wire Wire Line
	2550 3050 2700 3050
Wire Wire Line
	2700 3050 2700 3000
$Comp
L Device:C C7
U 1 1 5EF01EEE
P 3150 3000
F 0 "C7" V 3000 3050 50  0000 R CNN
F 1 "6pF" V 3200 2950 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3188 2850 50  0001 C CNN
F 3 "~" H 3150 3000 50  0001 C CNN
	1    3150 3000
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C8
U 1 1 5EF03AE5
P 3150 3300
F 0 "C8" V 3000 3350 50  0000 R CNN
F 1 "6pF" V 3200 3250 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3188 3150 50  0001 C CNN
F 3 "~" H 3150 3300 50  0001 C CNN
	1    3150 3300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5EF04CEC
P 3450 3150
F 0 "#PWR020" H 3450 2900 50  0001 C CNN
F 1 "GND" H 3455 2977 50  0000 C CNN
F 2 "" H 3450 3150 50  0001 C CNN
F 3 "" H 3450 3150 50  0001 C CNN
	1    3450 3150
	1    0    0    -1  
$EndComp
Text Label 1550 2950 0    50   ~ 0
SCL
Text Label 1550 3050 0    50   ~ 0
SDA
Wire Wire Line
	1550 2950 1750 2950
Wire Wire Line
	1750 3050 1550 3050
$Comp
L power:+5V #PWR08
U 1 1 5EF072BF
P 2150 2550
F 0 "#PWR08" H 2150 2400 50  0001 C CNN
F 1 "+5V" H 2050 2700 50  0000 C CNN
F 2 "" H 2150 2550 50  0001 C CNN
F 3 "" H 2150 2550 50  0001 C CNN
	1    2150 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR011
U 1 1 5EF0A7FB
P 2250 2550
F 0 "#PWR011" H 2250 2400 50  0001 C CNN
F 1 "+BATT" H 2350 2700 50  0000 C CNN
F 2 "" H 2250 2550 50  0001 C CNN
F 3 "" H 2250 2550 50  0001 C CNN
	1    2250 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5EF0B615
P 2150 3550
F 0 "#PWR09" H 2150 3300 50  0001 C CNN
F 1 "GND" H 2155 3377 50  0000 C CNN
F 2 "" H 2150 3550 50  0001 C CNN
F 3 "" H 2150 3550 50  0001 C CNN
	1    2150 3550
	1    0    0    -1  
$EndComp
NoConn ~ 1750 3250
$Comp
L Connector_Generic:Conn_02x03_Counter_Clockwise J2
U 1 1 5EF0CC53
P 9300 1400
F 0 "J2" H 9350 1717 50  0000 C CNN
F 1 "Prog" H 9350 1626 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 9300 1400 50  0001 C CNN
F 3 "~" H 9300 1400 50  0001 C CNN
	1    9300 1400
	1    0    0    -1  
$EndComp
Text Notes 5600 7350 0    50   ~ 0
Auto/Man
$Comp
L Connector:Screw_Terminal_01x02 J3
U 1 1 5EF18D25
P 9950 4750
F 0 "J3" H 10030 4742 50  0000 L CNN
F 1 "Output" H 10030 4651 50  0000 L CNN
F 2 "lanternfish:MC000048" H 9950 4750 50  0001 C CNN
F 3 "~" H 9950 4750 50  0001 C CNN
	1    9950 4750
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR035
U 1 1 5EF1A6AE
P 9750 4700
F 0 "#PWR035" H 9750 4550 50  0001 C CNN
F 1 "VDD" H 9765 4873 50  0000 C CNN
F 2 "" H 9750 4700 50  0001 C CNN
F 3 "" H 9750 4700 50  0001 C CNN
	1    9750 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 4850 9750 4950
$Comp
L power:GND #PWR036
U 1 1 5EF1B9AF
P 9750 5450
F 0 "#PWR036" H 9750 5200 50  0001 C CNN
F 1 "GND" H 9755 5277 50  0000 C CNN
F 2 "" H 9750 5450 50  0001 C CNN
F 3 "" H 9750 5450 50  0001 C CNN
	1    9750 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_SSSGD Q2
U 1 1 5EF2F28B
P 9650 5150
F 0 "Q2" H 9900 5250 50  0000 L CNN
F 1 "PSMN5R6-60YLX" H 9900 5150 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:LFPAK56" H 9850 5250 50  0001 C CNN
F 3 "~" H 9650 5150 50  0001 C CNN
	1    9650 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R22
U 1 1 5EF418FC
P 9250 5150
F 0 "R22" V 9043 5150 50  0000 C CNN
F 1 "220R" V 9134 5150 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 9180 5150 50  0001 C CNN
F 3 "~" H 9250 5150 50  0001 C CNN
	1    9250 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	9100 5150 9050 5150
Text Label 8900 5150 0    50   ~ 0
Gate
$Comp
L power:+5V #PWR031
U 1 1 5EF43165
P 9600 2400
F 0 "#PWR031" H 9600 2250 50  0001 C CNN
F 1 "+5V" H 9615 2573 50  0000 C CNN
F 2 "" H 9600 2400 50  0001 C CNN
F 3 "" H 9600 2400 50  0001 C CNN
	1    9600 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 5EF44744
P 9600 4000
F 0 "#PWR032" H 9600 3750 50  0001 C CNN
F 1 "GND" H 9605 3827 50  0000 C CNN
F 2 "" H 9600 4000 50  0001 C CNN
F 3 "" H 9600 4000 50  0001 C CNN
	1    9600 4000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 5EF496BE
P 4500 6800
F 0 "SW5" H 4500 7085 50  0000 C CNN
F 1 "SW_Push" H 4500 6994 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4500 7000 50  0001 C CNN
F 3 "~" H 4500 7000 50  0001 C CNN
	1    4500 6800
	0    -1   -1   0   
$EndComp
Text Label 1750 6550 2    50   ~ 0
SW1
Text Label 2850 6550 2    50   ~ 0
SW2
$Comp
L Device:Rotary_Encoder_Switch SW3
U 1 1 5EF5CC1B
P 2550 4850
F 0 "SW3" H 2550 4600 50  0000 C CNN
F 1 "PEC11R-4215F-S0024" H 2500 4200 50  0000 C CNN
F 2 "lanternfish:PEC11R-4215F-S0024" H 2400 5010 50  0001 C CNN
F 3 "~" H 2550 5110 50  0001 C CNN
	1    2550 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR022
U 1 1 5EF61AAF
P 4500 6200
F 0 "#PWR022" H 4500 6050 50  0001 C CNN
F 1 "+5V" H 4515 6373 50  0000 C CNN
F 2 "" H 4500 6200 50  0001 C CNN
F 3 "" H 4500 6200 50  0001 C CNN
	1    4500 6200
	1    0    0    -1  
$EndComp
Text Label 6850 4200 2    50   ~ 0
ROT_SW_A
Text Label 6850 4300 2    50   ~ 0
ROT_SW_B
Wire Wire Line
	6850 4300 6450 4300
Wire Wire Line
	6450 4200 6850 4200
Text Label 850  4750 0    50   ~ 0
ROT_SW_A
Text Label 850  4950 0    50   ~ 0
ROT_SW_B
Wire Wire Line
	2250 4850 2150 4850
Wire Wire Line
	2150 4850 2150 5150
$Comp
L power:+5V #PWR015
U 1 1 5EF6FFD1
P 2900 4300
F 0 "#PWR015" H 2900 4150 50  0001 C CNN
F 1 "+5V" H 2915 4473 50  0000 C CNN
F 2 "" H 2900 4300 50  0001 C CNN
F 3 "" H 2900 4300 50  0001 C CNN
	1    2900 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 4750 2850 4750
$Comp
L Device:R R10
U 1 1 5EF7541A
P 2900 4500
F 0 "R10" H 2650 4450 50  0000 L CNN
F 1 "10kR" H 2650 4550 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2830 4500 50  0001 C CNN
F 3 "~" H 2900 4500 50  0001 C CNN
	1    2900 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5EF75420
P 2900 5200
F 0 "#PWR016" H 2900 4950 50  0001 C CNN
F 1 "GND" H 2905 5027 50  0000 C CNN
F 2 "" H 2900 5200 50  0001 C CNN
F 3 "" H 2900 5200 50  0001 C CNN
	1    2900 5200
	1    0    0    -1  
$EndComp
Text Label 3650 4700 2    50   ~ 0
SW_SEL
$Comp
L Device:R R7
U 1 1 5EF7846B
P 2150 4500
F 0 "R7" H 2220 4546 50  0000 L CNN
F 1 "10kR" V 2150 4400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2080 4500 50  0001 C CNN
F 3 "~" H 2150 4500 50  0001 C CNN
	1    2150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4650 2150 4750
Wire Wire Line
	2150 4750 2250 4750
Wire Wire Line
	850  4750 1250 4750
Connection ~ 2150 4750
$Comp
L Device:R R3
U 1 1 5EF7D509
P 1700 4750
F 0 "R3" V 1600 4750 50  0000 C CNN
F 1 "10kR" V 1700 4750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1630 4750 50  0001 C CNN
F 3 "~" H 1700 4750 50  0001 C CNN
	1    1700 4750
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5EF806FD
P 1700 4950
F 0 "R4" V 1800 4950 50  0000 C CNN
F 1 "10kR" V 1700 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1630 4950 50  0001 C CNN
F 3 "~" H 1700 4950 50  0001 C CNN
	1    1700 4950
	0    -1   1    0   
$EndComp
Wire Wire Line
	850  4950 1500 4950
$Comp
L Device:C C1
U 1 1 5EF83074
P 1250 5200
F 0 "C1" H 1050 5250 50  0000 L CNN
F 1 "10nF" H 950 5150 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1288 5050 50  0001 C CNN
F 3 "~" H 1250 5200 50  0001 C CNN
	1    1250 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5EF83915
P 1500 5200
F 0 "C2" H 1615 5246 50  0000 L CNN
F 1 "10nF" H 1615 5155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1538 5050 50  0001 C CNN
F 3 "~" H 1500 5200 50  0001 C CNN
	1    1500 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 5050 1500 4950
Connection ~ 1500 4950
Wire Wire Line
	1500 4950 1550 4950
Wire Wire Line
	1250 5050 1250 4750
Connection ~ 1250 4750
Wire Wire Line
	1250 4750 1550 4750
$Comp
L power:GND #PWR05
U 1 1 5EF864C4
P 1500 5450
F 0 "#PWR05" H 1500 5200 50  0001 C CNN
F 1 "GND" H 1505 5277 50  0000 C CNN
F 2 "" H 1500 5450 50  0001 C CNN
F 3 "" H 1500 5450 50  0001 C CNN
	1    1500 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4750 2150 4750
Wire Wire Line
	1850 4950 2050 4950
Wire Wire Line
	2050 4950 2050 4650
Connection ~ 2050 4950
Wire Wire Line
	2050 4950 2250 4950
$Comp
L Device:R R6
U 1 1 5EF93584
P 2050 4500
F 0 "R6" H 1900 4550 50  0000 L CNN
F 1 "10kR" V 2050 4400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1980 4500 50  0001 C CNN
F 3 "~" H 2050 4500 50  0001 C CNN
	1    2050 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 4350 2100 4350
Wire Wire Line
	2100 4350 2100 4300
Wire Wire Line
	2100 4350 2150 4350
Connection ~ 2100 4350
$Comp
L power:+5V #PWR025
U 1 1 5EFAABBA
P 5550 6200
F 0 "#PWR025" H 5550 6050 50  0001 C CNN
F 1 "+5V" H 5565 6373 50  0000 C CNN
F 2 "" H 5550 6200 50  0001 C CNN
F 3 "" H 5550 6200 50  0001 C CNN
	1    5550 6200
	1    0    0    -1  
$EndComp
Text Label 5100 6550 2    50   ~ 0
SW4
$Comp
L power:+5V #PWR027
U 1 1 5EFBD1D6
P 5900 1750
F 0 "#PWR027" H 5900 1600 50  0001 C CNN
F 1 "+5V" H 5915 1923 50  0000 C CNN
F 2 "" H 5900 1750 50  0001 C CNN
F 3 "" H 5900 1750 50  0001 C CNN
	1    5900 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5EFC3148
P 5700 1850
F 0 "C12" V 5448 1850 50  0000 C CNN
F 1 "0.1uF" V 5539 1850 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5738 1700 50  0001 C CNN
F 3 "~" H 5700 1850 50  0001 C CNN
	1    5700 1850
	0    1    1    0   
$EndComp
$Comp
L Device:C C13
U 1 1 5EFC3B03
P 6100 1850
F 0 "C13" V 5848 1850 50  0000 C CNN
F 1 "0.1uF" V 5939 1850 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6138 1700 50  0001 C CNN
F 3 "~" H 6100 1850 50  0001 C CNN
	1    6100 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 1800 5850 1850
Connection ~ 5850 1850
Wire Wire Line
	5850 1800 5900 1800
Wire Wire Line
	5950 1800 5950 1850
Connection ~ 5950 1850
Wire Wire Line
	5900 1800 5900 1750
Connection ~ 5900 1800
Wire Wire Line
	5900 1800 5950 1800
$Comp
L power:GND #PWR029
U 1 1 5EFD5F5C
P 6250 1850
F 0 "#PWR029" H 6250 1600 50  0001 C CNN
F 1 "GND" H 6255 1677 50  0000 C CNN
F 2 "" H 6250 1850 50  0001 C CNN
F 3 "" H 6250 1850 50  0001 C CNN
	1    6250 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1850 5850 2000
Wire Wire Line
	5950 1850 5950 2000
$Comp
L power:GND #PWR024
U 1 1 5EFDBCA3
P 5550 1850
F 0 "#PWR024" H 5550 1600 50  0001 C CNN
F 1 "GND" H 5555 1677 50  0000 C CNN
F 2 "" H 5550 1850 50  0001 C CNN
F 3 "" H 5550 1850 50  0001 C CNN
	1    5550 1850
	1    0    0    -1  
$EndComp
Wire Notes Line
	800  4050 3700 4050
Wire Notes Line
	3700 5750 800  5750
Text Notes 850  4150 0    50   ~ 0
Rotary switch
$Comp
L Device:R R14
U 1 1 5EFF178D
P 4700 6550
F 0 "R14" V 4600 6550 50  0000 L CNN
F 1 "10kR" V 4800 6450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4630 6550 50  0001 C CNN
F 3 "~" H 4700 6550 50  0001 C CNN
	1    4700 6550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R15
U 1 1 5EFF2559
P 5550 6350
F 0 "R15" H 5450 6400 50  0000 R CNN
F 1 "10kR" H 5500 6300 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5480 6350 50  0001 C CNN
F 3 "~" H 5550 6350 50  0001 C CNN
	1    5550 6350
	1    0    0    1   
$EndComp
Text Label 6300 6550 2    50   ~ 0
SW_MAN
$Comp
L power:GND #PWR028
U 1 1 5EFF688A
P 5750 7050
F 0 "#PWR028" H 5750 6800 50  0001 C CNN
F 1 "GND" H 5755 6877 50  0000 C CNN
F 2 "" H 5750 7050 50  0001 C CNN
F 3 "" H 5750 7050 50  0001 C CNN
	1    5750 7050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5EFF707E
P 2450 1250
F 0 "C5" H 2335 1204 50  0000 R CNN
F 1 "0.33uF" H 2450 1350 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2488 1100 50  0001 C CNN
F 3 "~" H 2450 1250 50  0001 C CNN
	1    2450 1250
	-1   0    0    1   
$EndComp
$Comp
L Device:C C9
U 1 1 5EFFE9CC
P 3300 1250
F 0 "C9" H 3185 1204 50  0000 R CNN
F 1 "0.1uF" H 3300 1350 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3338 1100 50  0001 C CNN
F 3 "~" H 3300 1250 50  0001 C CNN
	1    3300 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 1100 3300 1100
Connection ~ 3300 1100
Wire Wire Line
	3300 1100 3400 1100
Connection ~ 2450 1100
Wire Wire Line
	2450 1100 2550 1100
Text Notes 1600 2150 0    50   ~ 0
Polarity protection\n
$Comp
L power:GND #PWR017
U 1 1 5F0056CF
P 3300 1900
F 0 "#PWR017" H 3300 1650 50  0001 C CNN
F 1 "GND" H 3305 1727 50  0000 C CNN
F 2 "" H 3300 1900 50  0001 C CNN
F 3 "" H 3300 1900 50  0001 C CNN
	1    3300 1900
	1    0    0    -1  
$EndComp
Text Notes 2650 2100 0    50   ~ 0
5V regulator
Text Notes 850  800  0    50   ~ 0
Power supply
Wire Notes Line
	6400 5850 6400 7700
Wire Notes Line
	800  7700 800  5850
Text Notes 850  5950 0    50   ~ 0
Switches
Wire Notes Line
	800  2350 3600 2350
Wire Notes Line
	3600 3950 800  3950
Text Notes 850  2450 0    50   ~ 0
Real Time Clock
Text Notes 8850 4550 0    50   ~ 0
Output switching
$Comp
L power:GND #PWR026
U 1 1 5F021D16
P 5850 5000
F 0 "#PWR026" H 5850 4750 50  0001 C CNN
F 1 "GND" H 5855 4827 50  0000 C CNN
F 2 "" H 5850 5000 50  0001 C CNN
F 3 "" H 5850 5000 50  0001 C CNN
	1    5850 5000
	1    0    0    -1  
$EndComp
Text Label 8850 1300 0    50   ~ 0
MISO
Text Label 8850 1400 0    50   ~ 0
SCK
Text Label 8850 1500 0    50   ~ 0
RST
Text Label 9800 1400 2    50   ~ 0
MOSI
Wire Wire Line
	9800 1400 9600 1400
Wire Wire Line
	9100 1300 8850 1300
Wire Wire Line
	9100 1500 8850 1500
Wire Wire Line
	8850 1400 9100 1400
$Comp
L power:GND #PWR034
U 1 1 5F02C35B
P 9650 1550
F 0 "#PWR034" H 9650 1300 50  0001 C CNN
F 1 "GND" H 9655 1377 50  0000 C CNN
F 2 "" H 9650 1550 50  0001 C CNN
F 3 "" H 9650 1550 50  0001 C CNN
	1    9650 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR033
U 1 1 5F02CE24
P 9650 1250
F 0 "#PWR033" H 9650 1100 50  0001 C CNN
F 1 "+5V" H 9665 1423 50  0000 C CNN
F 2 "" H 9650 1250 50  0001 C CNN
F 3 "" H 9650 1250 50  0001 C CNN
	1    9650 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 1300 9650 1300
Wire Wire Line
	9650 1300 9650 1250
Wire Wire Line
	9600 1500 9650 1500
Wire Wire Line
	9650 1500 9650 1550
Wire Notes Line
	9850 1800 9850 950 
Wire Notes Line
	9850 950  8800 950 
Wire Notes Line
	8800 950  8800 1800
Wire Notes Line
	8800 1800 9850 1800
Text Notes 8850 1100 0    50   ~ 0
Programming\ninterface
Text Label 8850 2600 0    50   ~ 0
LCD_E
Text Label 8850 2700 0    50   ~ 0
LCD_RW
Text Label 8850 2800 0    50   ~ 0
LCD_RS
Text Label 8850 3100 0    50   ~ 0
LCD_D0
Text Label 8850 3200 0    50   ~ 0
LCD_D1
Text Label 8850 3300 0    50   ~ 0
LCD_D2
Text Label 8850 3400 0    50   ~ 0
LCD_D3
Text Label 8850 3500 0    50   ~ 0
LCD_D4
Text Label 8850 3600 0    50   ~ 0
LCD_D5
Text Label 8850 3700 0    50   ~ 0
LCD_D6
Text Label 8850 3800 0    50   ~ 0
LCD_D7
Wire Wire Line
	9200 2600 8850 2600
Wire Wire Line
	8850 2700 9200 2700
Wire Wire Line
	9200 2800 8850 2800
Wire Wire Line
	8850 3100 9200 3100
Wire Wire Line
	9200 3200 8850 3200
Wire Wire Line
	8850 3300 9200 3300
Wire Wire Line
	9200 3400 8850 3400
Wire Wire Line
	8850 3500 9200 3500
Wire Wire Line
	9200 3600 8850 3600
Wire Wire Line
	8850 3700 9200 3700
Wire Wire Line
	9200 3800 8850 3800
$Comp
L Device:R_POT RV1
U 1 1 5F06A5F1
P 10250 2400
F 0 "RV1" H 10180 2354 50  0000 R CNN
F 1 "10kR" H 10180 2445 50  0000 R CNN
F 2 "lanternfish:RC33X-2" H 10250 2400 50  0001 C CNN
F 3 "~" H 10250 2400 50  0001 C CNN
	1    10250 2400
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR038
U 1 1 5F0704C8
P 10250 2250
F 0 "#PWR038" H 10250 2100 50  0001 C CNN
F 1 "+5V" H 10265 2423 50  0000 C CNN
F 2 "" H 10250 2250 50  0001 C CNN
F 3 "" H 10250 2250 50  0001 C CNN
	1    10250 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R24
U 1 1 5F071A6D
P 10250 2900
F 0 "R24" V 10350 2900 50  0000 C CNN
F 1 "220R" V 10250 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 10180 2900 50  0001 C CNN
F 3 "~" H 10250 2900 50  0001 C CNN
	1    10250 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	10000 2600 10050 2600
Wire Wire Line
	10050 2600 10050 2400
Wire Wire Line
	10050 2400 10100 2400
$Comp
L power:GND #PWR039
U 1 1 5F070BB0
P 10250 2550
F 0 "#PWR039" H 10250 2300 50  0001 C CNN
F 1 "GND" H 10255 2377 50  0000 C CNN
F 2 "" H 10250 2550 50  0001 C CNN
F 3 "" H 10250 2550 50  0001 C CNN
	1    10250 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR037
U 1 1 5F07E67D
P 10050 3550
F 0 "#PWR037" H 10050 3300 50  0001 C CNN
F 1 "GND" H 10055 3377 50  0000 C CNN
F 2 "" H 10050 3550 50  0001 C CNN
F 3 "" H 10050 3550 50  0001 C CNN
	1    10050 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 3150 10050 3000
Wire Wire Line
	10050 3000 10000 3000
Wire Wire Line
	10100 2900 10000 2900
Wire Wire Line
	10400 2900 10450 2900
Wire Wire Line
	10450 2900 10450 2850
$Comp
L power:+5V #PWR040
U 1 1 5F087D30
P 10450 2850
F 0 "#PWR040" H 10450 2700 50  0001 C CNN
F 1 "+5V" H 10465 3023 50  0000 C CNN
F 2 "" H 10450 2850 50  0001 C CNN
F 3 "" H 10450 2850 50  0001 C CNN
	1    10450 2850
	1    0    0    -1  
$EndComp
Text Label 10500 3350 2    50   ~ 0
LCD_BL
Wire Wire Line
	10500 3350 10350 3350
Wire Notes Line
	11000 2000 11000 4250
Wire Notes Line
	8800 4250 8800 2000
Text Notes 8850 2100 0    50   ~ 0
LCD Module
Text Label 6800 2300 2    50   ~ 0
LCD_E
Text Label 6800 2400 2    50   ~ 0
LCD_RW
Text Label 6800 2500 2    50   ~ 0
LCD_RS
Text Label 6800 3200 2    50   ~ 0
LCD_D0
Text Label 6800 4700 2    50   ~ 0
LCD_D1
Text Label 6800 4000 2    50   ~ 0
LCD_D2
Text Label 6800 3300 2    50   ~ 0
LCD_D3
Text Label 6800 4400 2    50   ~ 0
LCD_D4
Text Label 6800 4100 2    50   ~ 0
LCD_D5
Text Label 6800 3400 2    50   ~ 0
LCD_D6
Text Label 6800 3500 2    50   ~ 0
LCD_D7
Wire Wire Line
	6450 2300 6800 2300
Wire Wire Line
	6800 2400 6450 2400
Wire Wire Line
	6450 2500 6800 2500
Wire Wire Line
	6800 3200 6450 3200
Wire Wire Line
	6450 3300 6800 3300
Wire Wire Line
	6800 3400 6450 3400
Wire Wire Line
	6450 3500 6800 3500
Wire Wire Line
	6800 4000 6450 4000
Wire Wire Line
	6450 4100 6800 4100
Wire Wire Line
	6800 4400 6450 4400
Wire Wire Line
	6450 4700 6800 4700
Text Label 6800 3000 2    50   ~ 0
SW_MAN
Text Label 4900 4300 0    50   ~ 0
SW4
Text Label 4900 4200 0    50   ~ 0
SW3
Text Label 4900 4100 0    50   ~ 0
SW2
Text Label 4900 4000 0    50   ~ 0
SW1
Wire Wire Line
	4900 4000 5250 4000
Wire Wire Line
	5250 4100 4900 4100
Wire Wire Line
	4900 4300 5250 4300
Wire Wire Line
	5250 4200 4900 4200
Wire Wire Line
	6800 3000 6450 3000
Text Label 6800 2600 2    50   ~ 0
MOSI
Text Label 6800 2700 2    50   ~ 0
MISO
Text Label 6800 2800 2    50   ~ 0
SCK
Wire Wire Line
	6800 2600 6450 2600
Wire Wire Line
	6450 2700 6800 2700
Wire Wire Line
	6800 2800 6450 2800
Text Label 8150 3700 2    50   ~ 0
SCL
Text Label 8150 3600 2    50   ~ 0
SDA
Text Label 8150 3800 2    50   ~ 0
RST
Text Label 6800 4600 2    50   ~ 0
LCD_BL
Wire Wire Line
	6800 4600 6450 4600
Text Label 6800 2900 2    50   ~ 0
SW_SEL
Wire Wire Line
	6800 2900 6450 2900
Text Label 6800 4500 2    50   ~ 0
Gate
Wire Wire Line
	6800 4500 6450 4500
Text Notes 4550 4300 0    50   ~ 0
PCINT27
Text Notes 4550 4200 0    50   ~ 0
PCINT26\n
Text Notes 4550 4100 0    50   ~ 0
PCINT25
Text Notes 4550 4000 0    50   ~ 0
PCINT24
Wire Notes Line
	10750 5700 8800 5700
Wire Notes Line
	8800 4450 10750 4450
$Comp
L Device:R R21
U 1 1 5F1EE298
P 7750 3400
F 0 "R21" V 7750 3650 50  0000 L CNN
F 1 "10kR" V 7750 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7680 3400 50  0001 C CNN
F 3 "~" H 7750 3400 50  0001 C CNN
	1    7750 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 5F1FEA70
P 7400 3400
F 0 "R18" V 7400 3650 50  0000 L CNN
F 1 "10kR" V 7400 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7330 3400 50  0001 C CNN
F 3 "~" H 7400 3400 50  0001 C CNN
	1    7400 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3550 7750 3600
Wire Wire Line
	7750 3200 7750 3250
$Comp
L power:+5V #PWR030
U 1 1 5F20F3BF
P 7850 3150
F 0 "#PWR030" H 7850 3000 50  0001 C CNN
F 1 "+5V" H 7865 3323 50  0000 C CNN
F 2 "" H 7850 3150 50  0001 C CNN
F 3 "" H 7850 3150 50  0001 C CNN
	1    7850 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F21CDD1
P 1650 2650
F 0 "#PWR06" H 1650 2400 50  0001 C CNN
F 1 "GND" H 1655 2477 50  0000 C CNN
F 2 "" H 1650 2650 50  0001 C CNN
F 3 "" H 1650 2650 50  0001 C CNN
	1    1650 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5F21BFBB
P 1850 2600
F 0 "C4" V 1700 2650 50  0000 R CNN
F 1 "0.1uF" V 1950 2850 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1888 2450 50  0001 C CNN
F 3 "~" H 1850 2600 50  0001 C CNN
	1    1850 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 2550 2150 2600
Wire Wire Line
	2000 2600 2150 2600
Connection ~ 2150 2600
Wire Wire Line
	2150 2600 2150 2750
Wire Notes Line
	800  2350 800  3950
Wire Notes Line
	3600 2350 3600 3950
Wire Wire Line
	3300 3000 3350 3000
Wire Wire Line
	3300 3300 3350 3300
Wire Wire Line
	3350 3300 3350 3150
Wire Wire Line
	3350 3150 3450 3150
Connection ~ 3350 3150
Wire Wire Line
	3350 3150 3350 3000
Wire Wire Line
	2250 2550 2250 2750
Wire Wire Line
	1500 5400 1500 5350
Wire Wire Line
	1500 5400 1250 5400
Wire Wire Line
	1250 5400 1250 5350
Wire Wire Line
	1500 5400 1500 5450
Connection ~ 1500 5400
Text Notes 6900 4000 0    50   ~ 0
D0\n
Text Notes 6900 4100 0    50   ~ 0
D1
Text Notes 6900 4200 0    50   ~ 0
D2
Text Notes 6900 4300 0    50   ~ 0
D3
Text Notes 6900 4400 0    50   ~ 0
D4
Text Notes 6900 4500 0    50   ~ 0
D5
Text Notes 6900 4600 0    50   ~ 0
D6
Text Notes 6900 4700 0    50   ~ 0
D7
Text Notes 6900 2300 0    50   ~ 0
D8\n
Text Notes 6900 2400 0    50   ~ 0
D9
Text Notes 6900 2500 0    50   ~ 0
D10
Text Notes 6900 2600 0    50   ~ 0
D11
Text Notes 6900 2700 0    50   ~ 0
D12\n
Text Notes 6900 2800 0    50   ~ 0
D13
Text Notes 6900 3200 0    50   ~ 0
A0
Text Notes 6900 3300 0    50   ~ 0
A1
Text Notes 6900 3400 0    50   ~ 0
A2
Text Notes 6900 3500 0    50   ~ 0
A3
Text Notes 6900 2900 0    50   ~ 0
PCINT6
Text Notes 6900 3000 0    50   ~ 0
PCINT7\n
Wire Wire Line
	6450 3600 7650 3600
$Comp
L Device:R R17
U 1 1 5F3A34C2
P 7250 3400
F 0 "R17" V 7250 3650 50  0000 L CNN
F 1 "10kR" V 7250 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7180 3400 50  0001 C CNN
F 3 "~" H 7250 3400 50  0001 C CNN
	1    7250 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3200 7650 3200
Wire Notes Line
	3600 2250 800  2250
Wire Notes Line
	800  700  3600 700 
NoConn ~ 5250 2300
Wire Wire Line
	1650 2650 1650 2600
Wire Wire Line
	1650 2600 1700 2600
Wire Wire Line
	9750 5400 9850 5400
Wire Wire Line
	9850 5400 9850 5350
Connection ~ 9750 5400
Wire Wire Line
	9750 5400 9750 5450
Wire Wire Line
	9850 5400 9950 5400
Wire Wire Line
	9950 5400 9950 5350
Connection ~ 9850 5400
Wire Wire Line
	9750 5350 9750 5400
Wire Wire Line
	9750 4700 9750 4750
Wire Notes Line
	10750 4450 10750 5700
Wire Notes Line
	8800 4450 8800 5700
$Comp
L power:GND #PWR023
U 1 1 5EF4D959
P 4700 7050
F 0 "#PWR023" H 4700 6800 50  0001 C CNN
F 1 "GND" H 4705 6877 50  0000 C CNN
F 2 "" H 4700 7050 50  0001 C CNN
F 3 "" H 4700 7050 50  0001 C CNN
	1    4700 7050
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5EF79E38
P 2250 1100
F 0 "#FLG01" H 2250 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 2250 1250 50  0000 C CNN
F 2 "" H 2250 1100 50  0001 C CNN
F 3 "~" H 2250 1100 50  0001 C CNN
	1    2250 1100
	1    0    0    -1  
$EndComp
Connection ~ 2550 1100
Wire Wire Line
	2550 1100 2600 1100
Connection ~ 2250 1100
Wire Wire Line
	2250 1100 2450 1100
Wire Wire Line
	1350 1100 1400 1100
$Comp
L Device:R R5
U 1 1 5EF6F05C
P 1950 1650
F 0 "R5" H 1750 1700 50  0000 L CNN
F 1 "100kR" H 1650 1600 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1880 1650 50  0001 C CNN
F 3 "~" H 1950 1650 50  0001 C CNN
	1    1950 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1850 1950 1800
Wire Wire Line
	3300 1400 3300 1850
Wire Wire Line
	1950 1850 2450 1850
Connection ~ 3300 1850
Wire Wire Line
	3300 1850 3300 1900
Wire Wire Line
	1950 1850 1350 1850
Wire Wire Line
	1350 1200 1350 1850
Connection ~ 1950 1850
Wire Wire Line
	1600 1400 1600 1450
Wire Wire Line
	1950 1500 1950 1450
Wire Wire Line
	1600 1450 1950 1450
Connection ~ 1950 1450
Wire Wire Line
	1950 1450 1950 1400
Wire Wire Line
	2450 1400 2450 1850
Connection ~ 2450 1850
Wire Wire Line
	2450 1850 2900 1850
Wire Wire Line
	2900 1400 2900 1850
Connection ~ 2900 1850
Wire Wire Line
	2900 1850 3300 1850
Wire Notes Line
	3600 700  3600 2250
Wire Notes Line
	800  700  800  2250
$Comp
L Device:D_Zener_A1_K3 D1
U 1 1 5F05A17B
P 1950 1250
F 0 "D1" V 1850 1150 50  0000 L CNN
F 1 "BZX84W-B13X" H 1850 1400 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70_Handsoldering" H 1950 1250 50  0001 C CNN
F 3 "~" H 1950 1250 50  0001 C CNN
	1    1950 1250
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 1100 1950 1100
Connection ~ 1950 1100
Wire Wire Line
	1950 1100 2250 1100
$Comp
L Device:Q_NMOS_GSD Q3
U 1 1 5F060D89
P 10150 3350
F 0 "Q3" H 10000 3450 50  0000 L CNN
F 1 "SI2302DDS-T1-GE3" H 9350 3250 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 10350 3450 50  0001 C CNN
F 3 "~" H 10150 3350 50  0001 C CNN
	1    10150 3350
	-1   0    0    -1  
$EndComp
Wire Notes Line
	8800 4250 11000 4250
Wire Notes Line
	8800 2000 11000 2000
$Comp
L lanternfish:Abracon-ABS25 Y1
U 1 1 5F0BD3E9
P 2850 3150
F 0 "Y1" V 2850 2950 50  0000 L CNN
F 1 "ABS25-32.768KHZ-6-1-T" V 2500 2800 50  0000 L CNN
F 2 "lanternfish:Abracon_ABS25_4Pin_8mm_3.8mm" H 2850 3150 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1856019.pdf" H 2850 3150 50  0001 C CNN
	1    2850 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 3000 2850 3000
Wire Wire Line
	2700 3300 2850 3300
Connection ~ 2850 3000
Wire Wire Line
	2850 3000 3000 3000
Connection ~ 2850 3300
Wire Wire Line
	2850 3300 3000 3300
$Comp
L Device:R R23
U 1 1 5F0C61E6
P 9250 5250
F 0 "R23" V 9043 5250 50  0000 C CNN
F 1 "220R" V 9134 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 9180 5250 50  0001 C CNN
F 3 "~" H 9250 5250 50  0001 C CNN
	1    9250 5250
	0    1    -1   0   
$EndComp
Wire Wire Line
	9100 5250 9050 5250
Wire Wire Line
	9050 5250 9050 5150
Connection ~ 9050 5150
Wire Wire Line
	9050 5150 8900 5150
Wire Wire Line
	9450 5250 9450 5150
Wire Wire Line
	9400 5150 9450 5150
Connection ~ 9450 5150
Wire Wire Line
	9450 5250 9400 5250
Wire Wire Line
	7750 3600 8150 3600
Connection ~ 7750 3600
$Comp
L Device:R R19
U 1 1 5F11BB03
P 7500 3400
F 0 "R19" V 7500 3650 50  0000 L CNN
F 1 "10kR" V 7500 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7430 3400 50  0001 C CNN
F 3 "~" H 7500 3400 50  0001 C CNN
	1    7500 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R20
U 1 1 5F138AC6
P 7650 3400
F 0 "R20" V 7650 3650 50  0000 L CNN
F 1 "10kR" V 7650 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7580 3400 50  0001 C CNN
F 3 "~" H 7650 3400 50  0001 C CNN
	1    7650 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3200 7850 3200
Wire Wire Line
	7850 3200 7850 3150
Connection ~ 7750 3200
Wire Wire Line
	7650 3550 7650 3600
Connection ~ 7650 3600
Wire Wire Line
	7650 3600 7750 3600
Wire Wire Line
	7650 3250 7650 3200
Connection ~ 7650 3200
Wire Wire Line
	7650 3200 7500 3200
Wire Wire Line
	7400 3250 7400 3200
Wire Wire Line
	7400 3550 7400 3700
Connection ~ 7400 3700
Wire Wire Line
	7400 3700 7500 3700
Wire Wire Line
	6450 3700 7400 3700
Wire Wire Line
	6450 3800 7250 3800
Wire Wire Line
	7250 3250 7250 3200
Wire Wire Line
	7250 3200 7400 3200
Connection ~ 7400 3200
Wire Wire Line
	7500 3250 7500 3200
Connection ~ 7500 3200
Wire Wire Line
	7500 3200 7400 3200
Wire Wire Line
	7250 3550 7250 3800
Connection ~ 7250 3800
Wire Wire Line
	7250 3800 8150 3800
Wire Wire Line
	7500 3550 7500 3700
Connection ~ 7500 3700
Wire Wire Line
	7500 3700 8150 3700
$Comp
L Device:C C11
U 1 1 5F237B97
P 4900 6800
F 0 "C11" H 5015 6846 50  0000 L CNN
F 1 "10uF" H 5015 6755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4938 6650 50  0001 C CNN
F 3 "~" H 4900 6800 50  0001 C CNN
	1    4900 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 7000 4700 7000
Wire Wire Line
	4700 7000 4700 7050
Connection ~ 4700 7000
$Comp
L Device:R R13
U 1 1 5F259212
P 4500 6350
F 0 "R13" H 4250 6300 50  0000 L CNN
F 1 "10kR" H 4250 6400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4430 6350 50  0001 C CNN
F 3 "~" H 4500 6350 50  0001 C CNN
	1    4500 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 6550 5100 6550
Wire Wire Line
	4850 6550 4900 6550
Wire Wire Line
	4900 6550 4900 6650
Wire Wire Line
	4900 6950 4900 7000
Wire Wire Line
	4500 6500 4500 6550
Wire Wire Line
	4550 6550 4500 6550
Connection ~ 4500 6550
Wire Wire Line
	4500 6550 4500 6600
Connection ~ 4900 6550
$Comp
L Switch:SW_Push SW4
U 1 1 5F396131
P 3400 6800
F 0 "SW4" H 3400 7085 50  0000 C CNN
F 1 "SW_Push" H 3400 6994 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3400 7000 50  0001 C CNN
F 3 "~" H 3400 7000 50  0001 C CNN
	1    3400 6800
	0    -1   -1   0   
$EndComp
Text Label 4000 6550 2    50   ~ 0
SW3
$Comp
L power:+5V #PWR019
U 1 1 5F396138
P 3400 6200
F 0 "#PWR019" H 3400 6050 50  0001 C CNN
F 1 "+5V" H 3415 6373 50  0000 C CNN
F 2 "" H 3400 6200 50  0001 C CNN
F 3 "" H 3400 6200 50  0001 C CNN
	1    3400 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 5F39613E
P 3600 6550
F 0 "R12" V 3500 6550 50  0000 L CNN
F 1 "10kR" V 3700 6450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3530 6550 50  0001 C CNN
F 3 "~" H 3600 6550 50  0001 C CNN
	1    3600 6550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5F396144
P 3600 7050
F 0 "#PWR021" H 3600 6800 50  0001 C CNN
F 1 "GND" H 3605 6877 50  0000 C CNN
F 2 "" H 3600 7050 50  0001 C CNN
F 3 "" H 3600 7050 50  0001 C CNN
	1    3600 7050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5F39614A
P 3800 6800
F 0 "C10" H 3915 6846 50  0000 L CNN
F 1 "10uF" H 3915 6755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3838 6650 50  0001 C CNN
F 3 "~" H 3800 6800 50  0001 C CNN
	1    3800 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 7000 3600 7000
Wire Wire Line
	3600 7000 3600 7050
Connection ~ 3600 7000
$Comp
L Device:R R11
U 1 1 5F396153
P 3400 6350
F 0 "R11" H 3150 6300 50  0000 L CNN
F 1 "10kR" H 3150 6400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3330 6350 50  0001 C CNN
F 3 "~" H 3400 6350 50  0001 C CNN
	1    3400 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 6550 4000 6550
Wire Wire Line
	3750 6550 3800 6550
Wire Wire Line
	3800 6550 3800 6650
Wire Wire Line
	3800 6950 3800 7000
Wire Wire Line
	3600 7000 3800 7000
Wire Wire Line
	3400 6500 3400 6550
Wire Wire Line
	3450 6550 3400 6550
Connection ~ 3400 6550
Wire Wire Line
	3400 6550 3400 6600
Connection ~ 3800 6550
Wire Wire Line
	4700 7000 4900 7000
$Comp
L Switch:SW_Push SW2
U 1 1 5F3F4519
P 2250 6800
F 0 "SW2" H 2250 7085 50  0000 C CNN
F 1 "SW_Push" H 2250 6994 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2250 7000 50  0001 C CNN
F 3 "~" H 2250 7000 50  0001 C CNN
	1    2250 6800
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 5F3F4520
P 2250 6200
F 0 "#PWR012" H 2250 6050 50  0001 C CNN
F 1 "+5V" H 2265 6373 50  0000 C CNN
F 2 "" H 2250 6200 50  0001 C CNN
F 3 "" H 2250 6200 50  0001 C CNN
	1    2250 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5F3F4526
P 2450 6550
F 0 "R9" V 2350 6550 50  0000 L CNN
F 1 "10kR" V 2550 6450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2380 6550 50  0001 C CNN
F 3 "~" H 2450 6550 50  0001 C CNN
	1    2450 6550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5F3F452C
P 2450 7050
F 0 "#PWR013" H 2450 6800 50  0001 C CNN
F 1 "GND" H 2455 6877 50  0000 C CNN
F 2 "" H 2450 7050 50  0001 C CNN
F 3 "" H 2450 7050 50  0001 C CNN
	1    2450 7050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5F3F4532
P 2650 6800
F 0 "C6" H 2765 6846 50  0000 L CNN
F 1 "10uF" H 2765 6755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2688 6650 50  0001 C CNN
F 3 "~" H 2650 6800 50  0001 C CNN
	1    2650 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 7000 2450 7000
Wire Wire Line
	2450 7000 2450 7050
Connection ~ 2450 7000
$Comp
L Device:R R8
U 1 1 5F3F453B
P 2250 6350
F 0 "R8" H 2100 6300 50  0000 L CNN
F 1 "10kR" H 2000 6400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2180 6350 50  0001 C CNN
F 3 "~" H 2250 6350 50  0001 C CNN
	1    2250 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 6550 2850 6550
Wire Wire Line
	2600 6550 2650 6550
Wire Wire Line
	2650 6550 2650 6650
Wire Wire Line
	2650 6950 2650 7000
Wire Wire Line
	2450 7000 2650 7000
Wire Wire Line
	2250 6500 2250 6550
Wire Wire Line
	2300 6550 2250 6550
Connection ~ 2250 6550
Wire Wire Line
	2250 6550 2250 6600
Connection ~ 2650 6550
$Comp
L Switch:SW_Push SW1
U 1 1 5F405E07
P 1150 6800
F 0 "SW1" H 1150 7085 50  0000 C CNN
F 1 "SW_Push" H 1150 6994 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1150 7000 50  0001 C CNN
F 3 "~" H 1150 7000 50  0001 C CNN
	1    1150 6800
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5F405E0E
P 1150 6200
F 0 "#PWR03" H 1150 6050 50  0001 C CNN
F 1 "+5V" H 1165 6373 50  0000 C CNN
F 2 "" H 1150 6200 50  0001 C CNN
F 3 "" H 1150 6200 50  0001 C CNN
	1    1150 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5F405E14
P 1350 6550
F 0 "R2" V 1250 6550 50  0000 L CNN
F 1 "10kR" V 1450 6450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1280 6550 50  0001 C CNN
F 3 "~" H 1350 6550 50  0001 C CNN
	1    1350 6550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5F405E1A
P 1350 7050
F 0 "#PWR04" H 1350 6800 50  0001 C CNN
F 1 "GND" H 1355 6877 50  0000 C CNN
F 2 "" H 1350 7050 50  0001 C CNN
F 3 "" H 1350 7050 50  0001 C CNN
	1    1350 7050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5F405E20
P 1550 6800
F 0 "C3" H 1665 6846 50  0000 L CNN
F 1 "10uF" H 1665 6755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1588 6650 50  0001 C CNN
F 3 "~" H 1550 6800 50  0001 C CNN
	1    1550 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 7000 1350 7000
Wire Wire Line
	1350 7000 1350 7050
Connection ~ 1350 7000
$Comp
L Device:R R1
U 1 1 5F405E29
P 1150 6350
F 0 "R1" H 1000 6300 50  0000 L CNN
F 1 "10kR" H 900 6400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1080 6350 50  0001 C CNN
F 3 "~" H 1150 6350 50  0001 C CNN
	1    1150 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 6550 1750 6550
Wire Wire Line
	1500 6550 1550 6550
Wire Wire Line
	1550 6550 1550 6650
Wire Wire Line
	1550 6950 1550 7000
Wire Wire Line
	1350 7000 1550 7000
Wire Wire Line
	1150 6500 1150 6550
Wire Wire Line
	1200 6550 1150 6550
Connection ~ 1150 6550
Wire Wire Line
	1150 6550 1150 6600
Connection ~ 1550 6550
Wire Wire Line
	5550 6500 5550 6550
Wire Wire Line
	5550 6550 5600 6550
Wire Wire Line
	5550 6550 5550 6600
Connection ~ 5550 6550
$Comp
L Device:R R16
U 1 1 5F53169F
P 5750 6550
F 0 "R16" V 5850 6500 50  0000 L CNN
F 1 "10kR" V 5650 6450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5680 6550 50  0001 C CNN
F 3 "~" H 5750 6550 50  0001 C CNN
	1    5750 6550
	0    1    1    0   
$EndComp
$Comp
L Device:C C14
U 1 1 5F59FFF2
P 5950 6800
F 0 "C14" H 6065 6846 50  0000 L CNN
F 1 "10uF" H 6065 6755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5988 6650 50  0001 C CNN
F 3 "~" H 5950 6800 50  0001 C CNN
	1    5950 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 6650 5950 6550
Wire Wire Line
	5950 6550 5900 6550
Wire Wire Line
	5950 6550 6300 6550
Connection ~ 5950 6550
Wire Wire Line
	5550 7000 5750 7000
Wire Wire Line
	5950 7000 5950 6950
Wire Wire Line
	5750 7000 5750 7050
Connection ~ 5750 7000
Wire Wire Line
	5750 7000 5950 7000
Wire Notes Line
	800  5850 6400 5850
Wire Notes Line
	800  7700 6400 7700
Wire Wire Line
	2900 4650 2900 4700
Wire Wire Line
	2850 4950 2900 4950
Wire Wire Line
	2900 4700 2950 4700
Connection ~ 2900 4700
Wire Wire Line
	2900 4700 2900 4750
$Comp
L Device:R R25
U 1 1 5F72CF81
P 3100 4700
F 0 "R25" V 3200 4600 50  0000 L CNN
F 1 "10kR" V 3000 4600 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3030 4700 50  0001 C CNN
F 3 "~" H 3100 4700 50  0001 C CNN
	1    3100 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 5150 2900 5150
Wire Wire Line
	2900 5150 2900 4950
Wire Wire Line
	3250 4700 3300 4700
Wire Wire Line
	3300 4700 3300 4750
Wire Wire Line
	3300 4700 3650 4700
Connection ~ 3300 4700
$Comp
L Device:C C15
U 1 1 5F7879CF
P 3300 4900
F 0 "C15" H 3415 4946 50  0000 L CNN
F 1 "10nF" H 3415 4855 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3338 4750 50  0001 C CNN
F 3 "~" H 3300 4900 50  0001 C CNN
	1    3300 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5150 3300 5150
Wire Wire Line
	3300 5150 3300 5050
Connection ~ 2900 5150
Wire Wire Line
	2900 5200 2900 5150
Wire Wire Line
	2100 4300 2900 4300
Wire Wire Line
	2900 4300 2900 4350
Connection ~ 2900 4300
Wire Notes Line
	800  4050 800  5750
Wire Notes Line
	3700 4050 3700 5750
Text Notes 9350 5800 0    50   ~ 0
Note secondary GND for 25V ?\n
$EndSCHEMATC
