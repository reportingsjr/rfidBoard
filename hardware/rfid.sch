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
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
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
$Comp
L CR95HF U?
U 1 1 541504F3
P 3525 2245
F 0 "U?" H 3990 3230 39  0000 C CNN
F 1 "CR95HF" H 3015 3230 39  0000 C CNN
F 2 "" H 3485 2765 20  0000 C CNN
F 3 "" H 3485 2765 20  0000 C CNN
	1    3525 2245
	1    0    0    -1  
$EndComp
$Comp
L MURATA_CRYSTAL_SMD X?
U 1 1 54173929
P 2365 2700
F 0 "X?" H 2250 2620 30  0000 C CNN
F 1 "27.12MHz" H 2260 2785 30  0000 L CNN
F 2 "" H 2365 2700 60  0000 C CNN
F 3 "" H 2365 2700 60  0000 C CNN
	1    2365 2700
	0    1    1    0   
$EndComp
$Comp
L capacitor C?
U 1 1 54173C81
P 2020 2530
F 0 "C?" H 2040 2605 40  0000 L CNN
F 1 "4pF" H 2050 2465 40  0000 L CNN
F 2 "" H 2058 2380 30  0000 C CNN
F 3 "" H 2020 2530 60  0000 C CNN
	1    2020 2530
	0    1    1    0   
$EndComp
$Comp
L capacitor C?
U 1 1 54173DFA
P 2020 2870
F 0 "C?" H 2040 2945 40  0000 L CNN
F 1 "4pF" H 2050 2805 40  0000 L CNN
F 2 "" H 2058 2720 30  0000 C CNN
F 3 "" H 2020 2870 60  0000 C CNN
	1    2020 2870
	0    1    1    0   
$EndComp
Wire Wire Line
	2130 2530 2635 2530
Wire Wire Line
	2365 2530 2365 2565
Wire Wire Line
	2635 2530 2635 2645
Wire Wire Line
	2635 2645 2785 2645
Connection ~ 2365 2530
Wire Wire Line
	2130 2870 2635 2870
Wire Wire Line
	2365 2870 2365 2835
Wire Wire Line
	2635 2870 2635 2745
Wire Wire Line
	2635 2745 2785 2745
Connection ~ 2365 2870
$Comp
L GND #PWR?
U 1 1 54173FD6
P 1670 2730
F 0 "#PWR?" H 1670 2730 30  0001 C CNN
F 1 "GND" H 1670 2660 30  0001 C CNN
F 2 "" H 1670 2730 60  0000 C CNN
F 3 "" H 1670 2730 60  0000 C CNN
	1    1670 2730
	1    0    0    -1  
$EndComp
Wire Wire Line
	1910 2530 1800 2530
Wire Wire Line
	1800 2530 1800 2870
Wire Wire Line
	1800 2870 1910 2870
Wire Wire Line
	1800 2660 1670 2660
Wire Wire Line
	1670 2660 1670 2730
Connection ~ 1800 2660
$Comp
L capacitor C?
U 1 1 54175E86
P 2690 3385
F 0 "C?" H 2710 3460 40  0000 L CNN
F 1 "1nF" H 2720 3320 40  0000 L CNN
F 2 "" H 2728 3235 30  0000 C CNN
F 3 "" H 2690 3385 60  0000 C CNN
	1    2690 3385
	1    0    0    -1  
$EndComp
Wire Wire Line
	2785 3180 2690 3180
Wire Wire Line
	2690 3180 2690 3275
$Comp
L GND #PWR?
U 1 1 54175FA9
P 2690 3545
F 0 "#PWR?" H 2690 3545 30  0001 C CNN
F 1 "GND" H 2690 3475 30  0001 C CNN
F 2 "" H 2690 3545 60  0000 C CNN
F 3 "" H 2690 3545 60  0000 C CNN
	1    2690 3545
	1    0    0    -1  
$EndComp
Wire Wire Line
	2690 3495 2690 3545
Text Notes 2220 3280 0    39   ~ 0
Reserved Pins
Text GLabel 3495 1050 1    60   Input ~ 0
3V3
Wire Wire Line
	3495 1175 3495 1050
Text GLabel 2575 3100 0    60   Input ~ 0
3V3
Wire Wire Line
	2785 3100 2575 3100
$EndSCHEMATC
