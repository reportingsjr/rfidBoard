EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:rfid
LIBS:rfidAndPOE-cache
EELAYER 24 0
EELAYER END
$Descr A2 23386 16535
encoding utf-8
Sheet 1 1
Title ""
Date "23 nov 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LTC4267-3 U?
U 1 1 5297896E
P 6885 2740
F 0 "U?" H 7185 3190 60  0000 C CNN
F 1 "LTC4267-3" H 6685 3190 60  0000 C CNN
F 2 "" H 6635 2840 60  0000 C CNN
F 3 "" H 6635 2840 60  0000 C CNN
	1    6885 2740
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D2
U 1 1 52997173
P 5685 2740
F 0 "D2" H 5685 2840 40  0000 C CNN
F 1 "SMAJ58A" H 5685 2640 40  0000 C CNN
F 2 "" H 5685 2740 60  0000 C CNN
F 3 "" H 5685 2740 60  0000 C CNN
	1    5685 2740
	0    -1   -1   0   
$EndComp
$Comp
L CP1 C5
U 1 1 529972BA
P 4285 2740
F 0 "C5" H 4335 2840 50  0000 L CNN
F 1 "4.7uF, 100v" H 4335 2640 50  0000 L CNN
F 2 "" H 4285 2740 60  0000 C CNN
F 3 "" H 4285 2740 60  0000 C CNN
	1    4285 2740
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 529972CF
P 4935 2740
F 0 "C1" H 4935 2840 40  0000 L CNN
F 1 "0.1uF, 100V, X7R" H 4941 2655 40  0000 L CNN
F 2 "" H 4973 2590 30  0000 C CNN
F 3 "" H 4935 2740 60  0000 C CNN
	1    4935 2740
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L1
U 1 1 52997C4A
P 6935 1040
F 0 "L1" V 6885 1040 40  0000 C CNN
F 1 "3.3uH" V 7035 1040 40  0000 C CNN
F 2 "" H 6935 1040 60  0000 C CNN
F 3 "" H 6935 1040 60  0000 C CNN
	1    6935 1040
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 52997DB0
P 8085 1240
F 0 "C2" H 8085 1340 40  0000 L CNN
F 1 "1uF, 100V" H 8091 1155 40  0000 L CNN
F 2 "" H 8123 1090 30  0000 C CNN
F 3 "" H 8085 1240 60  0000 C CNN
	1    8085 1240
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 52997DCE
P 8085 1890
F 0 "C4" H 8085 1990 40  0000 L CNN
F 1 "4.7uF, 10V" H 8091 1805 40  0000 L CNN
F 2 "" H 8123 1740 30  0000 C CNN
F 3 "" H 8085 1890 60  0000 C CNN
	1    8085 1890
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 52997EAC
P 7835 1690
F 0 "#PWR?" H 7835 1690 40  0001 C CNN
F 1 "GNDA" H 7835 1620 40  0000 C CNN
F 2 "" H 7835 1690 60  0000 C CNN
F 3 "" H 7835 1690 60  0000 C CNN
	1    7835 1690
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D5
U 1 1 52997F21
P 8535 1540
F 0 "D5" H 8535 1640 40  0000 C CNN
F 1 "1N5237B, 8.2V" H 8535 1440 40  0000 C CNN
F 2 "" H 8535 1540 60  0000 C CNN
F 3 "" H 8535 1540 60  0000 C CNN
	1    8535 1540
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 52997F58
P 8885 1290
F 0 "R2" V 8965 1290 40  0000 C CNN
F 1 "220K" V 8892 1291 40  0000 C CNN
F 2 "" V 8815 1290 30  0000 C CNN
F 3 "" H 8885 1290 30  0000 C CNN
	1    8885 1290
	1    0    0    -1  
$EndComp
$Comp
L NPN Q2
U 1 1 52997F92
P 9335 1540
F 0 "Q2" H 9335 1390 50  0000 R CNN
F 1 "MMBTA42" H 9335 1690 50  0000 R CNN
F 2 "" H 9335 1540 60  0000 C CNN
F 3 "" H 9335 1540 60  0000 C CNN
	1    9335 1540
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 52998077
P 9785 1290
F 0 "R3" V 9865 1290 40  0000 C CNN
F 1 "220K" V 9792 1291 40  0000 C CNN
F 2 "" V 9715 1290 30  0000 C CNN
F 3 "" H 9785 1290 30  0000 C CNN
	1    9785 1290
	1    0    0    -1  
$EndComp
$Comp
L DIODE D3
U 1 1 52998084
P 10135 1740
F 0 "D3" H 10135 1840 40  0000 C CNN
F 1 "BAS516" H 10135 1640 40  0000 C CNN
F 2 "" H 10135 1740 60  0000 C CNN
F 3 "" H 10135 1740 60  0000 C CNN
	1    10135 1740
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 52998098
P 10735 1740
F 0 "R6" V 10815 1740 40  0000 C CNN
F 1 "510R" V 10742 1741 40  0000 C CNN
F 2 "" V 10665 1740 30  0000 C CNN
F 3 "" H 10735 1740 30  0000 C CNN
	1    10735 1740
	0    -1   -1   0   
$EndComp
$Comp
L C C3
U 1 1 52998184
P 10335 1240
F 0 "C3" H 10335 1340 40  0000 L CNN
F 1 "68pF, 200V" H 10341 1155 40  0000 L CNN
F 2 "" H 10373 1090 30  0000 C CNN
F 3 "" H 10335 1240 60  0000 C CNN
	1    10335 1240
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 529981A2
P 10735 1440
F 0 "R7" V 10815 1440 40  0000 C CNN
F 1 "100R, 1/8W" V 10742 1441 40  0000 C CNN
F 2 "" V 10665 1440 30  0000 C CNN
F 3 "" H 10735 1440 30  0000 C CNN
	1    10735 1440
	0    -1   -1   0   
$EndComp
$Comp
L PA1134 T?
U 1 1 529983B2
P 11635 1390
F 0 "T?" H 11885 1890 50  0000 C CNN
F 1 "PA1134" H 11885 1790 50  0000 C CNN
F 2 "" V 11735 1240 60  0000 C CNN
F 3 "" V 11735 1240 60  0000 C CNN
	1    11635 1390
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 52998525
P 11585 1840
F 0 "#PWR?" H 11585 1840 40  0001 C CNN
F 1 "GNDA" H 11585 1770 40  0000 C CNN
F 2 "" H 11585 1840 60  0000 C CNN
F 3 "" H 11585 1840 60  0000 C CNN
	1    11585 1840
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_N Q1
U 1 1 5299874E
P 11235 2340
F 0 "Q1" H 11285 2590 60  0000 R CNN
F 1 "Si3440DV, NFET" V 11435 2790 60  0000 R CNN
F 2 "" H 11235 2340 60  0000 C CNN
F 3 "" H 11235 2340 60  0000 C CNN
	1    11235 2340
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 529987A2
P 11235 2940
F 0 "R4" V 11315 2940 40  0000 C CNN
F 1 "0.250R" V 11242 2941 40  0000 C CNN
F 2 "" V 11165 2940 30  0000 C CNN
F 3 "" H 11235 2940 30  0000 C CNN
	1    11235 2940
	1    0    0    -1  
$EndComp
$Comp
L R R400
U 1 1 529987B6
P 11435 2940
F 0 "R400" V 11515 2940 40  0000 C CNN
F 1 "0.250R" V 11442 2941 40  0000 C CNN
F 2 "" V 11365 2940 30  0000 C CNN
F 3 "" H 11435 2940 30  0000 C CNN
	1    11435 2940
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 529987CA
P 10485 2640
F 0 "R5" V 10565 2640 40  0000 C CNN
F 1 "4.7K" V 10492 2641 40  0000 C CNN
F 2 "" V 10415 2640 30  0000 C CNN
F 3 "" H 10485 2640 30  0000 C CNN
	1    10485 2640
	0    -1   -1   0   
$EndComp
$Comp
L GNDA #PWR?
U 1 1 529988A9
P 11335 3290
F 0 "#PWR?" H 11335 3290 40  0001 C CNN
F 1 "GNDA" H 11335 3220 40  0000 C CNN
F 2 "" H 11335 3290 60  0000 C CNN
F 3 "" H 11335 3290 60  0000 C CNN
	1    11335 3290
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 52998B9C
P 7735 2490
F 0 "#PWR?" H 7735 2490 40  0001 C CNN
F 1 "GNDA" H 7735 2420 40  0000 C CNN
F 2 "" H 7735 2490 60  0000 C CNN
F 3 "" H 7735 2490 60  0000 C CNN
	1    7735 2490
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 52998BB0
P 5985 2490
F 0 "#PWR?" H 5985 2490 40  0001 C CNN
F 1 "GNDA" H 5985 2420 40  0000 C CNN
F 2 "" H 5985 2490 60  0000 C CNN
F 3 "" H 5985 2490 60  0000 C CNN
	1    5985 2490
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 52998BC4
P 6285 3240
F 0 "#PWR?" H 6285 3240 40  0001 C CNN
F 1 "GNDA" H 6285 3170 40  0000 C CNN
F 2 "" H 6285 3240 60  0000 C CNN
F 3 "" H 6285 3240 60  0000 C CNN
	1    6285 3240
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 52998BD8
P 7485 3240
F 0 "#PWR?" H 7485 3240 40  0001 C CNN
F 1 "GNDA" H 7485 3170 40  0000 C CNN
F 2 "" H 7485 3240 60  0000 C CNN
F 3 "" H 7485 3240 60  0000 C CNN
	1    7485 3240
	1    0    0    -1  
$EndComp
NoConn ~ 6335 2840
$Comp
L MOSFET_N Q3
U 1 1 529FE736
P 9185 3240
F 0 "Q3" V 9035 3440 60  0000 R CNN
F 1 "2N7002" V 9385 3390 60  0000 R CNN
F 2 "" H 9185 3240 60  0000 C CNN
F 3 "" H 9185 3240 60  0000 C CNN
	1    9185 3240
	0    1    1    0   
$EndComp
$Comp
L DIODE D7
U 1 1 529FE790
P 9885 3540
F 0 "D7" H 9885 3640 40  0000 C CNN
F 1 "BAS516" H 9885 3440 40  0000 C CNN
F 2 "" H 9885 3540 60  0000 C CNN
F 3 "" H 9885 3540 60  0000 C CNN
	1    9885 3540
	0    1    1    0   
$EndComp
$Comp
L DIODE D4
U 1 1 529FE7EB
P 8635 3140
F 0 "D4" H 8635 3240 40  0000 C CNN
F 1 "BAS516" H 8635 3040 40  0000 C CNN
F 2 "" H 8635 3140 60  0000 C CNN
F 3 "" H 8635 3140 60  0000 C CNN
	1    8635 3140
	0    -1   -1   0   
$EndComp
$Comp
L GNDA #PWR?
U 1 1 529FE8B5
P 8835 3440
F 0 "#PWR?" H 8835 3440 40  0001 C CNN
F 1 "GNDA" H 8835 3370 40  0000 C CNN
F 2 "" H 8835 3440 60  0000 C CNN
F 3 "" H 8835 3440 60  0000 C CNN
	1    8835 3440
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 529FE931
P 8135 2940
F 0 "R1" V 8215 2940 40  0000 C CNN
F 1 "10k" V 8142 2941 40  0000 C CNN
F 2 "" V 8065 2940 30  0000 C CNN
F 3 "" H 8135 2940 30  0000 C CNN
	1    8135 2940
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 529FE945
P 8135 3740
F 0 "R8" V 8215 3740 40  0000 C CNN
F 1 "100k" V 8142 3741 40  0000 C CNN
F 2 "" V 8065 3740 30  0000 C CNN
F 3 "" H 8135 3740 30  0000 C CNN
	1    8135 3740
	0    -1   -1   0   
$EndComp
$Comp
L R R9
U 1 1 529FE959
P 9235 3740
F 0 "R9" V 9315 3740 40  0000 C CNN
F 1 "6.8k" V 9242 3741 40  0000 C CNN
F 2 "" V 9165 3740 30  0000 C CNN
F 3 "" H 9235 3740 30  0000 C CNN
	1    9235 3740
	0    -1   -1   0   
$EndComp
$Comp
L OPTOISOLATOR U?
U 1 1 529FF254
P 10735 3940
F 0 "U?" H 11070 4275 70  0000 C CNN
F 1 "PS2811" H 11385 3590 70  0000 C CNN
F 2 "" H 11335 3940 60  0000 C CNN
F 3 "" H 11335 3940 60  0000 C CNN
	1    10735 3940
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 529FF2D9
P 10640 4675
F 0 "#PWR?" H 10640 4675 40  0001 C CNN
F 1 "GNDA" H 10640 4605 40  0000 C CNN
F 2 "" H 10640 4675 60  0000 C CNN
F 3 "" H 10640 4675 60  0000 C CNN
	1    10640 4675
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 529FF9B6
P 12170 1385
F 0 "#PWR?" H 12170 1385 30  0001 C CNN
F 1 "GND" H 12170 1315 30  0001 C CNN
F 2 "" H 12170 1385 60  0000 C CNN
F 3 "" H 12170 1385 60  0000 C CNN
	1    12170 1385
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D1
U 1 1 529FFB39
P 12605 930
F 0 "D1" H 12605 1030 40  0000 C CNN
F 1 "SMB540" H 12605 830 40  0000 C CNN
F 2 "" H 12605 930 60  0000 C CNN
F 3 "" H 12605 930 60  0000 C CNN
	1    12605 930 
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 529FFB57
P 12655 1160
F 0 "R10" V 12735 1160 40  0000 C CNN
F 1 "10R" V 12662 1161 40  0000 C CNN
F 2 "" V 12585 1160 30  0000 C CNN
F 3 "" H 12655 1160 30  0000 C CNN
	1    12655 1160
	0    -1   -1   0   
$EndComp
$Comp
L C C6
U 1 1 529FFB7A
P 13190 1160
F 0 "C6" V 13145 1225 40  0000 L CNN
F 1 "470pF" V 13245 1220 40  0000 L CNN
F 2 "" H 13228 1010 30  0000 C CNN
F 3 "" H 13190 1160 60  0000 C CNN
	1    13190 1160
	0    1    1    0   
$EndComp
Text GLabel 13920 930  2    60   Input ~ 0
5VPoE
$Comp
L C C14
U 1 1 52A001DF
P 12980 1615
F 0 "C14" H 12980 1715 40  0000 L CNN
F 1 "100uF, 6.3V, X5R" V 12840 1345 40  0000 L CNN
F 2 "" H 13018 1465 30  0000 C CNN
F 3 "" H 12980 1615 60  0000 C CNN
	1    12980 1615
	1    0    0    -1  
$EndComp
$Comp
L CP1 C9
U 1 1 52A001F3
P 13305 1615
F 0 "C9" H 13355 1715 50  0000 L CNN
F 1 "220uF, 6.3v" V 13170 1385 50  0000 L CNN
F 2 "" H 13305 1615 60  0000 C CNN
F 3 "" H 13305 1615 60  0000 C CNN
	1    13305 1615
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 52A00211
P 13025 1885
F 0 "#PWR?" H 13025 1885 30  0001 C CNN
F 1 "GND" H 13025 1815 30  0001 C CNN
F 2 "" H 13025 1885 60  0000 C CNN
F 3 "" H 13025 1885 60  0000 C CNN
	1    13025 1885
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 52A00473
P 12600 1615
F 0 "C?" H 12600 1715 40  0000 L CNN
F 1 "100uF, 6.3V, X5R" V 12460 1345 40  0000 L CNN
F 2 "" H 12638 1465 30  0000 C CNN
F 3 "" H 12600 1615 60  0000 C CNN
	1    12600 1615
	1    0    0    -1  
$EndComp
$Comp
L R R14
U 1 1 52A00B47
P 13505 4290
F 0 "R14" V 13585 4290 40  0000 C CNN
F 1 "33.2k" V 13512 4291 40  0000 C CNN
F 2 "" V 13435 4290 30  0000 C CNN
F 3 "" H 13505 4290 30  0000 C CNN
	1    13505 4290
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 52A00D13
P 13505 3235
F 0 "R13" V 13585 3235 40  0000 C CNN
F 1 "100k, 1%" V 13512 3236 40  0000 C CNN
F 2 "" V 13435 3235 30  0000 C CNN
F 3 "" H 13505 3235 30  0000 C CNN
	1    13505 3235
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 52A00D3B
P 13035 2690
F 0 "R21" V 13115 2690 40  0000 C CNN
F 1 "470R" V 13042 2691 40  0000 C CNN
F 2 "" V 12965 2690 30  0000 C CNN
F 3 "" H 13035 2690 30  0000 C CNN
	1    13035 2690
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 52A00D4F
P 12135 2940
F 0 "R11" V 12215 2940 40  0000 C CNN
F 1 "1k" V 12142 2941 40  0000 C CNN
F 2 "" V 12065 2940 30  0000 C CNN
F 3 "" H 12135 2940 30  0000 C CNN
	1    12135 2940
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 52A00D63
P 11835 2890
F 0 "C12" H 11835 2990 40  0000 L CNN
F 1 "1uF" H 11841 2805 40  0000 L CNN
F 2 "" H 11873 2740 30  0000 C CNN
F 3 "" H 11835 2890 60  0000 C CNN
	1    11835 2890
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 52A00D77
P 12385 2890
F 0 "C13" H 12385 2990 40  0000 L CNN
F 1 "33nF" H 12391 2805 40  0000 L CNN
F 2 "" H 12423 2740 30  0000 C CNN
F 3 "" H 12385 2890 60  0000 C CNN
	1    12385 2890
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 52A00D8B
P 12335 3800
F 0 "C7" H 12335 3900 40  0000 L CNN
F 1 "27nF" H 12341 3715 40  0000 L CNN
F 2 "" H 12373 3650 30  0000 C CNN
F 3 "" H 12335 3800 60  0000 C CNN
	1    12335 3800
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 52A00DA9
P 12885 3600
F 0 "R12" V 12965 3600 40  0000 C CNN
F 1 "47k" V 12892 3601 40  0000 C CNN
F 2 "" V 12815 3600 30  0000 C CNN
F 3 "" H 12885 3600 30  0000 C CNN
	1    12885 3600
	0    -1   -1   0   
$EndComp
$Comp
L C C8
U 1 1 52A00DCC
P 11355 4540
F 0 "C8" V 11420 4630 40  0000 L CNN
F 1 "2.8nF, 250VAC, YCAP" V 11210 4220 40  0000 L CNN
F 2 "" H 11393 4390 30  0000 C CNN
F 3 "" H 11355 4540 60  0000 C CNN
	1    11355 4540
	0    -1   -1   0   
$EndComp
$Comp
L VREF D8
U 1 1 52A00EE8
P 12335 4420
F 0 "D8" H 12210 4455 40  0000 C CNN
F 1 "TLV431" H 12200 4380 40  0000 C CNN
F 2 "" V 12335 4430 60  0000 C CNN
F 3 "" V 12335 4430 60  0000 C CNN
	1    12335 4420
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 52A252C8
P 13505 4680
F 0 "#PWR?" H 13505 4680 30  0001 C CNN
F 1 "GND" H 13505 4610 30  0001 C CNN
F 2 "" H 13505 4680 60  0000 C CNN
F 3 "" H 13505 4680 60  0000 C CNN
	1    13505 4680
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 52A263CC
P 11835 3190
F 0 "#PWR?" H 11835 3190 30  0001 C CNN
F 1 "GND" H 11835 3120 30  0001 C CNN
F 2 "" H 11835 3190 60  0000 C CNN
F 3 "" H 11835 3190 60  0000 C CNN
	1    11835 3190
	1    0    0    -1  
$EndComp
$Comp
L BRIDGE_RECTIFIER D?
U 1 1 52A270C2
P 3675 1860
F 0 "D?" H 3585 2110 40  0000 C CNN
F 1 "CDNBS04-B08200" H 3335 1635 40  0000 C CNN
F 2 "" H 3450 2070 60  0000 C CNN
F 3 "" H 3450 2070 60  0000 C CNN
	1    3675 1860
	1    0    0    -1  
$EndComp
$Comp
L BRIDGE_RECTIFIER D?
U 1 1 52A27139
P 3675 2580
F 0 "D?" H 3585 2830 40  0000 C CNN
F 1 "CDNBS04-B08200" H 3335 2355 40  0000 C CNN
F 2 "" H 3450 2790 60  0000 C CNN
F 3 "" H 3450 2790 60  0000 C CNN
	1    3675 2580
	1    0    0    -1  
$EndComp
Wire Wire Line
	3370 3040 6335 3040
Connection ~ 4285 2290
Connection ~ 4935 2290
Wire Wire Line
	7685 2840 7435 2840
Connection ~ 6135 3040
Connection ~ 5685 3040
Connection ~ 4935 3040
Wire Wire Line
	3985 2290 5685 2290
Wire Wire Line
	4285 2940 4285 3040
Connection ~ 4285 3040
Wire Wire Line
	4935 2940 4935 3040
Wire Wire Line
	5685 2940 5685 3040
Wire Wire Line
	5685 2290 5685 2540
Wire Wire Line
	4935 2540 4935 2290
Wire Wire Line
	4285 2540 4285 2290
Connection ~ 5235 2290
Wire Wire Line
	7585 1040 7585 2740
Wire Wire Line
	7585 2740 7435 2740
Wire Wire Line
	5235 1040 5235 2290
Wire Wire Line
	6135 3040 6135 3440
Wire Wire Line
	6135 3440 7685 3440
Wire Wire Line
	7685 3440 7685 2840
Wire Wire Line
	5235 1040 6635 1040
Wire Wire Line
	7235 1040 11635 1040
Wire Wire Line
	8085 1440 8085 1690
Wire Wire Line
	7835 1690 7835 1590
Wire Wire Line
	7835 1590 8085 1590
Connection ~ 8085 1590
Wire Wire Line
	6085 2740 6335 2740
Wire Wire Line
	8335 1540 8085 1540
Connection ~ 8085 1540
Wire Wire Line
	8735 1540 9135 1540
Connection ~ 8885 1540
Wire Wire Line
	9435 1740 9935 1740
Wire Wire Line
	9785 1540 9785 1740
Connection ~ 9785 1740
Wire Wire Line
	9585 2090 9585 1740
Connection ~ 8085 2090
Connection ~ 9585 1740
Wire Wire Line
	10335 1740 10485 1740
Wire Wire Line
	10335 1440 10485 1440
Connection ~ 7585 1040
Wire Wire Line
	10985 1440 10985 1340
Wire Wire Line
	10985 1340 11635 1340
Wire Wire Line
	10985 1740 11235 1740
Wire Wire Line
	11235 1740 11235 1440
Wire Wire Line
	11235 1440 11635 1440
Connection ~ 10335 1040
Connection ~ 9785 1040
Connection ~ 8885 1040
Connection ~ 8085 1040
Wire Wire Line
	9435 1340 9435 1040
Connection ~ 9435 1040
Wire Wire Line
	11335 1340 11335 2140
Connection ~ 11335 1340
Wire Wire Line
	11335 2540 11335 2690
Wire Wire Line
	11235 2690 11435 2690
Connection ~ 11335 2690
Wire Wire Line
	10735 2640 11335 2640
Connection ~ 11335 2640
Wire Wire Line
	11235 3190 11435 3190
Wire Wire Line
	11335 3190 11335 3290
Connection ~ 11335 3190
Wire Wire Line
	7435 2640 10235 2640
Wire Wire Line
	6335 2640 6185 2640
Wire Wire Line
	6185 2640 6185 2340
Wire Wire Line
	6185 2340 11035 2340
Wire Wire Line
	11635 1740 11585 1740
Wire Wire Line
	11585 1740 11585 1840
Wire Wire Line
	7435 2440 7735 2440
Wire Wire Line
	7735 2440 7735 2490
Wire Wire Line
	7435 3140 7485 3140
Wire Wire Line
	7485 3040 7485 3240
Wire Wire Line
	6335 3140 6285 3140
Wire Wire Line
	6285 3140 6285 3240
Wire Wire Line
	7435 3040 7485 3040
Connection ~ 7485 3140
Wire Wire Line
	7435 2540 7485 2540
Wire Wire Line
	7485 2540 7485 2440
Connection ~ 7485 2440
Wire Wire Line
	5985 2440 5985 2490
Wire Wire Line
	5985 2440 6335 2440
Wire Wire Line
	9185 2940 9185 3040
Wire Wire Line
	8385 2940 9185 2940
Wire Wire Line
	8635 3340 8985 3340
Wire Wire Line
	8835 3340 8835 3440
Connection ~ 8835 3340
Wire Wire Line
	7435 2940 7885 2940
Connection ~ 8635 2940
Wire Wire Line
	7835 2940 7835 3740
Wire Wire Line
	7835 3740 7885 3740
Connection ~ 7835 2940
Wire Wire Line
	8385 3740 8985 3740
Wire Wire Line
	9485 3740 10785 3740
Wire Wire Line
	9385 3340 9885 3340
Wire Wire Line
	6335 2540 6235 2540
Wire Wire Line
	6235 2540 6235 2240
Wire Wire Line
	6235 2240 9585 2240
Wire Wire Line
	9585 2240 9585 3340
Connection ~ 9585 3340
Wire Wire Line
	8510 3890 8735 3890
Wire Wire Line
	8735 3890 8735 3740
Connection ~ 8735 3740
Connection ~ 9885 3740
Wire Wire Line
	10640 4090 10785 4090
Wire Wire Line
	12085 1340 12170 1340
Wire Wire Line
	12170 1310 12170 1385
Wire Wire Line
	12085 1310 12170 1310
Connection ~ 12170 1340
Wire Wire Line
	12085 1040 12405 1040
Wire Wire Line
	12405 930  12405 1160
Wire Wire Line
	12085 1070 12170 1070
Wire Wire Line
	12170 1070 12170 1040
Connection ~ 12170 1040
Connection ~ 12405 1040
Wire Wire Line
	12905 1160 12990 1160
Wire Wire Line
	12805 930  13920 930 
Wire Wire Line
	13390 1160 13505 1160
Wire Wire Line
	13505 930  13505 2985
Connection ~ 13505 930 
Wire Wire Line
	12600 1415 13505 1415
Connection ~ 13305 1415
Connection ~ 12980 1415
Wire Wire Line
	12600 1815 13305 1815
Connection ~ 12980 1815
Wire Wire Line
	13025 1885 13025 1815
Connection ~ 13025 1815
Wire Wire Line
	10640 4090 10640 4675
Wire Wire Line
	11155 4540 10640 4540
Connection ~ 10640 4540
Wire Wire Line
	11560 4540 13505 4540
Connection ~ 13505 1160
Connection ~ 13505 1415
Connection ~ 12335 4540
Wire Wire Line
	13505 3485 13505 4040
Wire Wire Line
	13505 4540 13505 4680
Wire Wire Line
	12335 4000 12335 4280
Wire Wire Line
	12445 4420 12640 4420
Wire Wire Line
	12640 4420 12640 3960
Wire Wire Line
	12640 3960 13505 3960
Connection ~ 13505 3960
Wire Wire Line
	11885 4090 12335 4090
Connection ~ 12335 4090
Wire Wire Line
	12335 3600 12635 3600
Wire Wire Line
	13135 3600 13505 3600
Connection ~ 13505 3600
Wire Wire Line
	11835 2690 12785 2690
Connection ~ 12385 2690
Connection ~ 12135 2690
Wire Wire Line
	12135 3190 12135 3740
Wire Wire Line
	12135 3740 11885 3740
Wire Wire Line
	12385 3090 12385 3290
Wire Wire Line
	12385 3290 12135 3290
Connection ~ 12135 3290
Wire Wire Line
	11835 3090 11835 3190
Wire Wire Line
	13285 2690 13505 2690
Wire Wire Line
	13505 2690 13505 2685
Connection ~ 13505 2685
Connection ~ 3985 2290
Wire Wire Line
	3985 1860 3985 2580
Wire Wire Line
	3370 1860 3370 3040
Connection ~ 3370 2580
$Comp
L TST P?
U 1 1 52A279E6
P 13430 930
F 0 "P?" H 13430 1230 40  0000 C CNN
F 1 "+5V" H 13430 1180 30  0000 C CNN
F 2 "" H 13430 930 60  0000 C CNN
F 3 "" H 13430 930 60  0000 C CNN
	1    13430 930 
	1    0    0    -1  
$EndComp
$Comp
L TST P?
U 1 1 52A279FA
P 13015 4540
F 0 "P?" H 13015 4840 40  0000 C CNN
F 1 "GND" H 13015 4790 30  0000 C CNN
F 2 "" H 13015 4540 60  0000 C CNN
F 3 "" H 13015 4540 60  0000 C CNN
	1    13015 4540
	1    0    0    -1  
$EndComp
$Comp
L TST P?
U 1 1 52A27A0E
P 4130 2285
F 0 "P?" H 4130 2585 40  0000 C CNN
F 1 "PoE+" H 4130 2535 30  0000 C CNN
F 2 "" H 4130 2285 60  0000 C CNN
F 3 "" H 4130 2285 60  0000 C CNN
	1    4130 2285
	1    0    0    -1  
$EndComp
$Comp
L TST P?
U 1 1 52A27A22
P 4075 3035
F 0 "P?" H 4075 3335 40  0000 C CNN
F 1 "PoE-" H 4075 3285 30  0000 C CNN
F 2 "" H 4075 3035 60  0000 C CNN
F 3 "" H 4075 3035 60  0000 C CNN
	1    4075 3035
	1    0    0    -1  
$EndComp
Text Notes 5665 1660 0    60   ~ 0
Note: GNDA is from ethernet. \nGND on the rest of the circuit is\nisolated from this.
$Comp
L LED D?
U 1 1 52A27A6E
P 13790 1690
F 0 "D?" H 13790 1790 50  0000 C CNN
F 1 "5V LED" H 13795 1575 50  0000 C CNN
F 2 "" H 13790 1690 60  0000 C CNN
F 3 "" H 13790 1690 60  0000 C CNN
	1    13790 1690
	0    1    1    0   
$EndComp
Wire Wire Line
	13790 930  13790 1060
Connection ~ 13790 930 
$Comp
L GND #PWR?
U 1 1 52A27D1F
P 13790 1955
F 0 "#PWR?" H 13790 1955 30  0001 C CNN
F 1 "GND" H 13790 1885 30  0001 C CNN
F 2 "" H 13790 1955 60  0000 C CNN
F 3 "" H 13790 1955 60  0000 C CNN
	1    13790 1955
	1    0    0    -1  
$EndComp
Wire Wire Line
	13790 1890 13790 1955
$Comp
L RESISTOR R?
U 1 1 52A27F11
P 13790 1240
F 0 "R?" V 13870 1240 40  0000 C CNN
F 1 "2.8k" V 13700 1245 40  0000 C CNN
F 2 "" V 13720 1240 30  0000 C CNN
F 3 "" H 13790 1240 30  0000 C CNN
	1    13790 1240
	1    0    0    -1  
$EndComp
Wire Wire Line
	13790 1490 13790 1420
Text Label 6085 2740 0    60   ~ 0
PVcc
Text Label 7830 2090 0    60   ~ 0
PVcc
Wire Wire Line
	7830 2090 9585 2090
Text Label 8510 3890 0    60   ~ 0
PVcc
$EndSCHEMATC
