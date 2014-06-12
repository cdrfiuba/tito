EESchema Schematic File Version 2  date jue 12 jun 2014 20:15:01 ART
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
LIBS:L298
LIBS:7805b
LIBS:reg_204-5
LIBS:tcrt1000
LIBS:drv8833
LIBS:placa_principal-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 4 4
Title ""
Date "12 jun 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5250 2100 5350 2100
Connection ~ 3900 3050
Wire Wire Line
	3900 3200 3900 3000
Wire Wire Line
	4100 4850 3900 4850
Wire Wire Line
	6050 5700 5850 5700
Connection ~ 5850 5550
Wire Wire Line
	5850 5700 5850 5550
Wire Wire Line
	7150 3650 6950 3650
Wire Wire Line
	6950 3650 6950 3550
Wire Wire Line
	5250 2300 6050 2300
Wire Wire Line
	7250 2750 5600 2750
Wire Wire Line
	7250 3950 6650 3950
Wire Wire Line
	6150 3800 3750 3800
Wire Wire Line
	6150 3800 6150 3600
Wire Wire Line
	6650 3950 6650 3250
Wire Wire Line
	6650 3050 6950 3050
Wire Wire Line
	6950 3050 6950 3150
Wire Wire Line
	5650 5000 5500 5000
Wire Wire Line
	6650 5700 7250 5700
Wire Wire Line
	6150 5350 6150 5550
Wire Wire Line
	6650 5700 6650 5000
Wire Wire Line
	6650 4800 6950 4800
Wire Wire Line
	6950 4800 6950 4900
Wire Wire Line
	6150 5550 5150 5550
Connection ~ 7250 3950
Wire Wire Line
	7250 5700 7250 2750
Wire Wire Line
	3900 3400 3900 3500
Wire Wire Line
	3900 3500 4950 3500
Wire Wire Line
	5650 3050 4950 3050
Wire Wire Line
	3900 5250 3900 5350
Wire Wire Line
	3900 5350 4950 5350
Wire Wire Line
	5650 4800 4950 4800
Wire Wire Line
	3750 3800 3750 3250
Wire Wire Line
	3900 3050 3750 3050
Wire Wire Line
	6050 2300 6050 2750
Connection ~ 6050 2750
Wire Wire Line
	5500 3700 5500 3800
Connection ~ 5500 3800
Wire Wire Line
	4900 3300 4950 3300
Wire Wire Line
	4950 3050 4950 3500
Connection ~ 4950 3300
Wire Wire Line
	5650 3250 5500 3250
Wire Wire Line
	5500 3250 5500 3300
Wire Wire Line
	5150 3050 5150 3300
Connection ~ 5150 3050
Wire Wire Line
	5150 3700 5150 3800
Connection ~ 5150 3800
Wire Wire Line
	4950 4800 4950 5350
Wire Wire Line
	4950 5150 4900 5150
Connection ~ 4950 5150
Wire Wire Line
	5500 5000 5500 5050
Wire Wire Line
	5500 5550 5500 5450
Wire Wire Line
	5150 4800 5150 5050
Wire Wire Line
	5150 5550 5150 5450
Connection ~ 5500 5550
Wire Wire Line
	3800 3050 3800 2900
Connection ~ 3800 3050
Wire Wire Line
	4150 3750 4150 3800
Connection ~ 4150 3800
Wire Wire Line
	5600 2750 5600 3050
Connection ~ 5600 3050
Wire Wire Line
	5350 2100 5350 1950
Wire Wire Line
	5550 3200 5550 3250
Connection ~ 5550 3250
Wire Wire Line
	5550 4950 5550 5000
Connection ~ 5550 5000
Connection ~ 4500 3800
Wire Wire Line
	4500 3800 4500 3950
Wire Wire Line
	4500 3950 4700 3950
Wire Wire Line
	6950 5300 6950 5400
Wire Wire Line
	6950 5400 7150 5400
Wire Wire Line
	3900 4850 3900 5050
Wire Wire Line
	3900 3000 4050 3000
Text Label 4050 3000 2    60   ~ 0
VDD
Text Label 4100 4850 2    60   ~ 0
VDD
Text Label 6050 5700 2    60   ~ 0
GND
Text Label 7150 5400 2    60   ~ 0
GND
Text Label 7150 3650 2    60   ~ 0
GND
Text Label 4700 3950 2    60   ~ 0
GND
$Comp
L C C?
U 1 1 5390D675
P 6950 3350
F 0 "C?" H 7000 3450 50  0000 L CNN
F 1 "10 n" H 7000 3250 50  0000 L CNN
	1    6950 3350
	1    0    0    -1  
$EndComp
$Comp
L REG_104-5 U?
U 1 1 5390D681
P 6150 3150
F 0 "U?" H 5900 3350 60  0000 C CNN
F 1 "REG_104-5" H 6150 3450 60  0000 C CNN
	1    6150 3150
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 5390D68D
P 3400 3150
F 0 "P?" V 3350 3150 40  0000 C CNN
F 1 "Batería 7,2V" V 3450 3150 40  0000 C CNN
	1    3400 3150
	-1   0    0    1   
$EndComp
$Comp
L CAPAPOL C?
U 1 1 5390D693
P 5500 3500
F 0 "C?" H 5550 3600 50  0000 L CNN
F 1 "220 u" H 5550 3400 50  0000 L CNN
	1    5500 3500
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 5390D699
P 4900 2200
F 0 "P?" V 4850 2200 40  0000 C CNN
F 1 "Batería 3,6V" V 4950 2200 40  0000 C CNN
	1    4900 2200
	-1   0    0    1   
$EndComp
$Comp
L C C?
U 1 1 5390D6CB
P 6950 5100
F 0 "C?" H 7000 5200 50  0000 L CNN
F 1 "10 n" H 7000 5000 50  0000 L CNN
	1    6950 5100
	1    0    0    -1  
$EndComp
$Comp
L REG_104-5 U?
U 1 1 5390D6D1
P 6150 4900
F 0 "U?" H 5900 5100 60  0000 C CNN
F 1 "REG_104-3.3" H 6150 5200 60  0000 C CNN
	1    6150 4900
	1    0    0    -1  
$EndComp
$Comp
L CAPAPOL C?
U 1 1 5390D6DD
P 5500 5250
F 0 "C?" H 5550 5350 50  0000 L CNN
F 1 "220 u" H 5550 5150 50  0000 L CNN
	1    5500 5250
	1    0    0    -1  
$EndComp
$Comp
L DUAL_SWITCH_INV SW?
U 1 1 5390D6F5
P 4400 3300
F 0 "SW?" H 4200 3450 50  0000 C CNN
F 1 "DUAL_SWITCH_INV" H 4250 3150 50  0000 C CNN
	1    4400 3300
	-1   0    0    1   
$EndComp
$Comp
L DUAL_SWITCH_INV SW?
U 1 1 5390D6FB
P 4400 5150
F 0 "SW?" H 4200 5300 50  0000 C CNN
F 1 "DUAL_SWITCH_INV" H 4250 5000 50  0000 C CNN
	1    4400 5150
	-1   0    0    1   
$EndComp
$Comp
L C C?
U 1 1 5390D8D2
P 5150 3500
F 0 "C?" H 5150 3600 40  0000 L CNN
F 1 "100 n" H 5156 3415 40  0000 L CNN
F 2 "~" H 5188 3350 30  0000 C CNN
F 3 "~" H 5150 3500 60  0000 C CNN
	1    5150 3500
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5390DAD4
P 5150 5250
F 0 "C?" H 5150 5350 40  0000 L CNN
F 1 "100 n" H 5156 5165 40  0000 L CNN
F 2 "~" H 5188 5100 30  0000 C CNN
F 3 "~" H 5150 5250 60  0000 C CNN
	1    5150 5250
	1    0    0    -1  
$EndComp
Text HLabel 3800 2900 0    60   Input ~ 0
Vdd
Text HLabel 4150 3750 0    60   Input ~ 0
Gnd
Text HLabel 5350 1950 0    60   Input ~ 0
+Batt
Text HLabel 5550 3200 0    60   Input ~ 0
+5V
Text HLabel 5550 4950 0    60   Input ~ 0
+3,3V
$EndSCHEMATC
