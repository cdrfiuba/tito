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
LIBS:L298
LIBS:7805b
LIBS:reg_204-5
LIBS:cny70
LIBS:tcrt1000
LIBS:drv8833
LIBS:placa_principal-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date "5 jun 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DRV8833 U?
U 1 1 53910CF9
P 5050 3200
F 0 "U?" H 5100 3550 60  0000 C CNN
F 1 "DRV8833" H 5050 3650 60  0000 C CNN
F 2 "~" H 5050 3200 60  0000 C CNN
F 3 "~" H 5050 3200 60  0000 C CNN
	1    5050 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 53910CFF
P 3300 3100
F 0 "#PWR?" H 3300 3100 30  0001 C CNN
F 1 "GND" H 3300 3030 30  0001 C CNN
F 2 "" H 3300 3100 60  0000 C CNN
F 3 "" H 3300 3100 60  0000 C CNN
	1    3300 3100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53910D0B
P 4100 2550
F 0 "R?" V 4180 2550 40  0000 C CNN
F 1 "R" V 4107 2551 40  0000 C CNN
F 2 "~" V 4030 2550 30  0000 C CNN
F 3 "~" H 4100 2550 30  0000 C CNN
	1    4100 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3350 4350 3350
Wire Wire Line
	3250 3050 4350 3050
Wire Wire Line
	4100 2850 4350 2850
Wire Wire Line
	4100 2850 4100 2800
Wire Wire Line
	5800 3550 5750 3550
Wire Wire Line
	5750 3450 5800 3450
Wire Wire Line
	5750 2850 5800 2850
Wire Wire Line
	5800 2950 5750 2950
Wire Wire Line
	3550 3150 4350 3150
Wire Wire Line
	3550 2950 4350 2950
Wire Wire Line
	3550 3250 4350 3250
$Comp
L GND #PWR?
U 1 1 53910D28
P 5800 3200
F 0 "#PWR?" H 5800 3200 30  0001 C CNN
F 1 "GND" H 5800 3130 30  0001 C CNN
F 2 "" H 5800 3200 60  0000 C CNN
F 3 "" H 5800 3200 60  0000 C CNN
	1    5800 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3150 5800 3150
Wire Wire Line
	5800 3150 5800 3200
Wire Wire Line
	5750 3350 6850 3350
Wire Wire Line
	6850 3350 6850 3750
$Comp
L C C?
U 1 1 53910D3D
P 7000 3500
F 0 "C?" H 7000 3600 40  0000 L CNN
F 1 "10 nF" H 7006 3415 40  0000 L CNN
F 2 "~" H 7038 3350 30  0000 C CNN
F 3 "~" H 7000 3500 60  0000 C CNN
	1    7000 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3750 7000 3750
Wire Wire Line
	7000 3750 7000 3700
Wire Wire Line
	7000 3300 7000 3250
Connection ~ 7000 3250
Wire Wire Line
	5750 3050 8000 3050
$Comp
L CAPAPOL C?
U 1 1 53910D48
P 8000 3300
F 0 "C?" H 8050 3400 40  0000 L CNN
F 1 "2,2 uF" H 8050 3200 40  0000 L CNN
F 2 "~" H 8100 3150 30  0000 C CNN
F 3 "~" H 8000 3300 300 0000 C CNN
	1    8000 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3500 8000 3550
$Comp
L GND #PWR?
U 1 1 53910D4F
P 8000 3550
F 0 "#PWR?" H 8000 3550 30  0001 C CNN
F 1 "GND" H 8000 3480 30  0001 C CNN
F 2 "" H 8000 3550 60  0000 C CNN
F 3 "" H 8000 3550 60  0000 C CNN
	1    8000 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3050 8000 3100
Wire Wire Line
	7300 3250 7300 3300
$Comp
L CAPAPOL C?
U 1 1 53910D57
P 7300 3500
F 0 "C?" H 7350 3600 40  0000 L CNN
F 1 "2200 uF" H 7350 3400 40  0000 L CNN
F 2 "~" H 7400 3350 30  0000 C CNN
F 3 "~" H 7300 3500 300 0000 C CNN
	1    7300 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3700 7300 3750
$Comp
L GND #PWR?
U 1 1 53910D5E
P 7300 3750
F 0 "#PWR?" H 7300 3750 30  0001 C CNN
F 1 "GND" H 7300 3680 30  0001 C CNN
F 2 "" H 7300 3750 60  0000 C CNN
F 3 "" H 7300 3750 60  0000 C CNN
	1    7300 3750
	1    0    0    -1  
$EndComp
Connection ~ 7300 3250
Wire Wire Line
	7700 3250 7700 3300
$Comp
L C C?
U 1 1 53910D67
P 7700 3500
F 0 "C?" H 7700 3600 40  0000 L CNN
F 1 "10 nF" H 7706 3415 40  0000 L CNN
F 2 "~" H 7738 3350 30  0000 C CNN
F 3 "~" H 7700 3500 60  0000 C CNN
	1    7700 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3700 7700 3750
$Comp
L GND #PWR?
U 1 1 53910D6E
P 7700 3750
F 0 "#PWR?" H 7700 3750 30  0001 C CNN
F 1 "GND" H 7700 3680 30  0001 C CNN
F 2 "" H 7700 3750 60  0000 C CNN
F 3 "" H 7700 3750 60  0000 C CNN
	1    7700 3750
	1    0    0    -1  
$EndComp
Text HLabel 4050 2250 0    60   Input ~ 0
+BATT
Wire Wire Line
	4050 2250 4700 2250
Wire Wire Line
	3300 3050 3300 3100
Text HLabel 3250 3050 0    60   Input ~ 0
GND
Connection ~ 3300 3050
Wire Wire Line
	3400 3350 3400 3050
Connection ~ 3400 3050
Text HLabel 5800 2850 2    60   Input ~ 0
Motor A Entrada 1
Text HLabel 5800 2950 2    60   Input ~ 0
Motor A Entrada 2
Text HLabel 5800 3450 2    60   Input ~ 0
Motor B Entrada 2
Text HLabel 5800 3550 2    60   Input ~ 0
Motor B Entrada 1
$Comp
L CONN_2 P?
U 1 1 5391385D
P 6000 2150
F 0 "P?" V 5950 2150 40  0000 C CNN
F 1 "Motor 2" V 6050 2150 40  0000 C CNN
F 2 "" H 6000 2150 60  0001 C CNN
F 3 "" H 6000 2150 60  0001 C CNN
	1    6000 2150
	-1   0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 53913863
P 6000 1700
F 0 "P?" V 5950 1700 40  0000 C CNN
F 1 "Motor 1" V 6050 1700 40  0000 C CNN
F 2 "" H 6000 1700 60  0001 C CNN
F 3 "" H 6000 1700 60  0001 C CNN
	1    6000 1700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6350 1600 7150 1600
Wire Wire Line
	6350 1800 7150 1800
Wire Wire Line
	6350 2050 7150 2050
Wire Wire Line
	6350 2250 7150 2250
Text Label 3550 3450 0    60   ~ 0
Motor B salida 1
Wire Wire Line
	3550 3450 4350 3450
Text Label 3550 3250 0    60   ~ 0
Motor B salida 2
Text Label 3550 3150 0    60   ~ 0
Motor A salida 2
Text Label 3550 2950 0    60   ~ 0
Motor A salida 1
Text Label 7150 1600 2    60   ~ 0
Motor A salida 1
Text Label 7150 1800 2    60   ~ 0
Motor A salida 2
Text Label 7150 2250 2    60   ~ 0
Motor B salida 2
Text Label 7150 2050 2    60   ~ 0
Motor B salida 1
Wire Wire Line
	4100 2250 4100 2300
Text Label 4700 2250 2    60   ~ 0
Alimentacion
Connection ~ 4100 2250
Text Label 6250 3200 0    60   ~ 0
Alimentacion
Wire Wire Line
	5750 3250 7700 3250
Wire Wire Line
	6850 3200 6850 3250
Connection ~ 6850 3250
Wire Wire Line
	6850 3200 6250 3200
$Comp
L GND #PWR?
U 1 1 5392D7DF
P 8650 2050
F 0 "#PWR?" H 8650 2050 30  0001 C CNN
F 1 "GND" H 8650 1980 30  0001 C CNN
F 2 "" H 8650 2050 60  0001 C CNN
F 3 "" H 8650 2050 60  0001 C CNN
	1    8650 2050
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K?
U 1 1 5392D7E5
P 8250 1900
F 0 "K?" V 8200 1900 50  0000 C CNN
F 1 "Servo" V 8300 1900 40  0000 C CNN
F 2 "" H 8250 1900 60  0001 C CNN
F 3 "" H 8250 1900 60  0001 C CNN
	1    8250 1900
	-1   0    0    1   
$EndComp
$Comp
L CAPAPOL C?
U 1 1 5392D7F2
P 9100 1900
F 0 "C?" H 9150 2000 50  0000 L CNN
F 1 "100uF" H 9150 1800 50  0000 L CNN
F 2 "" H 9100 1900 60  0001 C CNN
F 3 "" H 9100 1900 60  0001 C CNN
	1    9100 1900
	1    0    0    -1  
$EndComp
Connection ~ 8650 2000
Wire Wire Line
	8850 2000 8850 2100
Wire Wire Line
	8850 2100 9100 2100
Connection ~ 8650 1800
Wire Wire Line
	8800 1800 8800 1700
Wire Wire Line
	8800 1700 9100 1700
Wire Wire Line
	8600 1900 8850 1900
Wire Wire Line
	8650 2000 8650 2050
Wire Wire Line
	8600 2000 8850 2000
Wire Wire Line
	8650 1650 8650 1800
Wire Wire Line
	8600 1800 8800 1800
Text HLabel 8650 1650 0    60   Input ~ 12
Alimentacion Servo
Text HLabel 8950 1550 0    60   Input ~ 12
Control Servo
Text Label 8850 1900 2    60   ~ 0
servo
Wire Wire Line
	8950 1550 9200 1550
Text Label 9200 1550 2    60   ~ 0
servo
$EndSCHEMATC
