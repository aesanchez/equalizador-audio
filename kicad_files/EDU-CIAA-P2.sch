EESchema Schematic File Version 4
LIBS:equalizador_audio-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
Title "Poncho Equalizador de Audio"
Date "2018-11-01"
Rev "1.0"
Comp "Taller de Proyecto 1 - UNLP"
Comment1 "Grupo 11"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L equalizador_audio-rescue:GND-poncho_grande-rescue-equalizador_audio-rescue #PWR?
U 1 1 5C03D013
P 4500 4700
AR Path="/560A0C15/5C03D013" Ref="#PWR?"  Part="1" 
AR Path="/5C03D013" Ref="#PWR?"  Part="1" 
AR Path="/5C00C011/5C03D013" Ref="#PWR0113"  Part="1" 
AR Path="/5C00815E/5C0082D9/5C03D013" Ref="#PWR?"  Part="1" 
F 0 "#PWR0113" H 4500 4700 30  0001 C CNN
F 1 "GND" H 4500 4630 30  0001 C CNN
F 2 "" H 4500 4700 60  0000 C CNN
F 3 "" H 4500 4700 60  0000 C CNN
	1    4500 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 4550 4850 4550
Wire Wire Line
	4500 2750 4500 2850
Wire Wire Line
	4500 2850 4500 2950
Wire Wire Line
	4500 2950 4500 3150
Wire Wire Line
	4500 3150 4500 3250
Wire Wire Line
	4500 3250 4500 3450
Wire Wire Line
	4500 3450 4500 3550
Wire Wire Line
	4500 3550 4500 3850
Wire Wire Line
	4500 3850 4500 3950
Wire Wire Line
	4500 3950 4500 4450
Wire Wire Line
	4500 4450 4500 4550
Wire Wire Line
	4500 4550 4500 4700
Wire Wire Line
	4500 2750 4850 2750
Connection ~ 4500 4550
Wire Wire Line
	4850 2850 4500 2850
Connection ~ 4500 2850
Wire Wire Line
	4850 2950 4500 2950
Connection ~ 4500 2950
Wire Wire Line
	4850 3150 4500 3150
Connection ~ 4500 3150
Wire Wire Line
	4850 3250 4500 3250
Connection ~ 4500 3250
Wire Wire Line
	4850 3450 4500 3450
Connection ~ 4500 3450
Wire Wire Line
	4850 3550 4500 3550
Connection ~ 4500 3550
Wire Wire Line
	4850 3850 4500 3850
Connection ~ 4500 3850
Wire Wire Line
	4850 3950 4500 3950
Connection ~ 4500 3950
Wire Wire Line
	4850 4450 4500 4450
Connection ~ 4500 4450
Wire Wire Line
	4850 3750 3800 3750
Wire Wire Line
	6050 3650 6600 3650
Wire Wire Line
	6050 3750 6600 3750
Wire Wire Line
	6050 3850 6600 3850
Wire Wire Line
	6050 3950 6600 3950
Wire Wire Line
	6050 4050 6600 4050
Text HLabel 3800 3750 0    60   Input ~ 0
LCD_EN
Text HLabel 6600 3650 2    60   BiDi ~ 0
LCD4
Text HLabel 6600 3750 2    60   BiDi ~ 0
RS
Text HLabel 6600 3850 2    60   BiDi ~ 0
LCD3
Text HLabel 6600 3950 2    60   BiDi ~ 0
LCD2
Text HLabel 6600 4050 2    60   BiDi ~ 0
LCD1
$Comp
L equalizador_audio-rescue:Conn_Poncho2P_2x_20x2-poncho_grande-rescue-equalizador_audio-rescue XA?
U 2 1 5C03D07F
P 5100 2950
AR Path="/560A0C15/5C03D07F" Ref="XA?"  Part="2" 
AR Path="/5C03D07F" Ref="XA?"  Part="2" 
AR Path="/5C00C011/5C03D07F" Ref="XA1"  Part="2" 
AR Path="/5C00815E/5C0082D9/5C03D07F" Ref="XA?"  Part="2" 
F 0 "XA1" H 5400 3350 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 5450 1250 60  0000 C CNN
F 2 "Poncho_Esqueleto:Conn_Poncho_Completo" H 5350 1150 60  0000 C CNN
F 3 "" H 5100 2950 60  0000 C CNN
	2    5100 2950
	1    0    0    -1  
$EndComp
NoConn ~ 6050 2750
NoConn ~ 6050 2850
NoConn ~ 6050 2950
NoConn ~ 6050 3050
NoConn ~ 6050 3150
NoConn ~ 6050 3250
NoConn ~ 6050 3350
NoConn ~ 6050 3450
NoConn ~ 6050 3550
NoConn ~ 4850 4350
NoConn ~ 4850 4250
NoConn ~ 4850 4150
NoConn ~ 4850 4050
NoConn ~ 4850 3650
NoConn ~ 4850 3350
NoConn ~ 4850 3050
Wire Wire Line
	6050 4150 6600 4150
Text HLabel 6600 4550 2    60   BiDi ~ 0
TEC_UP
Text HLabel 6600 4250 2    60   BiDi ~ 0
TEC_DOWN
Text HLabel 6600 4350 2    60   BiDi ~ 0
TEC_OK
Text HLabel 6600 4150 2    60   BiDi ~ 0
TEC_LEFT
Text HLabel 6600 4450 2    60   BiDi ~ 0
TEC_RIGHT
Wire Wire Line
	6050 4250 6600 4250
Wire Wire Line
	6050 4350 6600 4350
Wire Wire Line
	6050 4450 6600 4450
Wire Wire Line
	6050 4550 6600 4550
$Comp
L power:+5V #PWR0111
U 1 1 5BEFF789
P 6250 2650
AR Path="/5C00C011/5BEFF789" Ref="#PWR0111"  Part="1" 
AR Path="/5C00815E/5C0082D9/5BEFF789" Ref="#PWR?"  Part="1" 
F 0 "#PWR0111" H 6250 2500 50  0001 C CNN
F 1 "+5V" H 6265 2823 50  0000 C CNN
F 2 "" H 6250 2650 50  0001 C CNN
F 3 "" H 6250 2650 50  0001 C CNN
	1    6250 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2650 6250 2650
$Comp
L power:+3.3V #PWR0112
U 1 1 5BEFFBDF
P 4500 2650
AR Path="/5C00C011/5BEFFBDF" Ref="#PWR0112"  Part="1" 
AR Path="/5C00815E/5C0082D9/5BEFFBDF" Ref="#PWR?"  Part="1" 
F 0 "#PWR0112" H 4500 2500 50  0001 C CNN
F 1 "+3.3V" H 4515 2823 50  0000 C CNN
F 2 "" H 4500 2650 50  0001 C CNN
F 3 "" H 4500 2650 50  0001 C CNN
	1    4500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2650 4500 2650
$EndSCHEMATC
