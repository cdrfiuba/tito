EESchema Schematic File Version 2  date Tue 12 Apr 2011 03:40:38 PM ART
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
LIBS:reg_5v
LIBS:placa_sensores-cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "12 apr 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	7000 4200 7000 4450
Wire Wire Line
	7200 4750 7200 4100
Wire Wire Line
	7200 4750 5750 4750
Connection ~ 7350 4050
Wire Wire Line
	5750 4150 5950 4150
Wire Wire Line
	4750 3650 6200 3650
Wire Wire Line
	7000 4000 7350 4000
Wire Wire Line
	7000 4150 7000 4100
Connection ~ 7000 4000
Connection ~ 7000 4100
Connection ~ 7000 4200
Connection ~ 6200 4200
Connection ~ 6200 4100
Connection ~ 6200 4000
Connection ~ 5750 4750
Connection ~ 5750 4450
Connection ~ 5750 4150
Connection ~ 5750 3850
Connection ~ 5150 3850
Connection ~ 5250 3850
Connection ~ 5250 4150
Connection ~ 5150 4150
Connection ~ 5150 4450
Connection ~ 5250 4450
Wire Wire Line
	5150 4450 5250 4450
Wire Wire Line
	5150 4750 5250 4750
Wire Wire Line
	5150 3850 5250 3850
Connection ~ 4750 4150
Connection ~ 4750 3850
Connection ~ 4750 4450
Wire Wire Line
	5150 4150 5250 4150
Connection ~ 4750 4750
Connection ~ 5250 4750
Connection ~ 5150 4750
Wire Wire Line
	5750 3850 5950 3850
Wire Wire Line
	5950 3850 5950 4100
Wire Wire Line
	5950 4100 6200 4100
Wire Wire Line
	7350 4000 7350 4050
Wire Wire Line
	4750 3650 4750 4750
Wire Wire Line
	6200 3650 6200 4000
Wire Wire Line
	7000 4100 7200 4100
Wire Wire Line
	7000 4450 5750 4450
Wire Wire Line
	5950 4150 5950 4200
Wire Wire Line
	5950 4200 6200 4200
$Comp
L GND #PWR01
U 1 1 4DA3121B
P 7350 4050
F 0 "#PWR01" H 7350 4050 30  0001 C CNN
F 1 "GND" H 7350 3980 30  0001 C CNN
	1    7350 4050
	1    0    0    -1  
$EndComp
Text Notes 6050 4200 0    60   ~ 0
LED 2
Text Notes 6050 4100 0    60   ~ 0
LED 1\n
Text Notes 7000 4200 0    60   ~ 0
LED 3
Text Notes 7000 4100 0    60   ~ 0
LED 4
Text Notes 7000 4000 0    60   ~ 0
GND
Text Notes 5950 4000 0    60   ~ 0
5v input
$Comp
L LED D3
U 1 1 4DA308A8
P 4950 4450
F 0 "D3" H 4950 4550 50  0000 C CNN
F 1 "LED" H 4950 4350 50  0000 C CNN
	1    4950 4450
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4DA308A7
P 5500 4450
F 0 "R3" V 5580 4450 50  0000 C CNN
F 1 "220" V 5500 4450 50  0000 C CNN
	1    5500 4450
	0    1    1    0   
$EndComp
$Comp
L CONN_3X2 P1
U 1 1 4DA30867
P 6600 4150
F 0 "P1" H 6600 4400 50  0000 C CNN
F 1 "CONN_3X2" V 6600 4200 40  0000 C CNN
	1    6600 4150
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4DA30433
P 5500 4750
F 0 "R4" V 5580 4750 50  0000 C CNN
F 1 "220" V 5500 4750 50  0000 C CNN
	1    5500 4750
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 4DA301BB
P 5500 4150
F 0 "R2" V 5580 4150 50  0000 C CNN
F 1 "220" V 5500 4150 50  0000 C CNN
	1    5500 4150
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 4DA301B3
P 5500 3850
F 0 "R1" V 5580 3850 50  0000 C CNN
F 1 "220" V 5500 3850 50  0000 C CNN
	1    5500 3850
	0    1    1    0   
$EndComp
$Comp
L LED D4
U 1 1 4DA30122
P 4950 4750
F 0 "D4" H 4950 4850 50  0000 C CNN
F 1 "LED" H 4950 4650 50  0000 C CNN
	1    4950 4750
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 4DA30121
P 4950 4150
F 0 "D2" H 4950 4250 50  0000 C CNN
F 1 "LED" H 4950 4050 50  0000 C CNN
	1    4950 4150
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 4DA30119
P 4950 3850
F 0 "D1" H 4950 3950 50  0000 C CNN
F 1 "LED" H 4950 3750 50  0000 C CNN
	1    4950 3850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
