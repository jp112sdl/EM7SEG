EESchema Schematic File Version 4
EELAYER 30 0
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
L EM7SEG_DRIVER-rescue:EM7SEG-Device U1
U 1 1 5E42D318
P 7730 2660
F 0 "U1" H 7690 2430 50  0000 L CNN
F 1 "EM7SEG" H 7610 2310 50  0000 L CNN
F 2 "additional:em7seg" H 7730 2660 50  0001 C CNN
F 3 "" H 7730 2660 50  0001 C CNN
	1    7730 2660
	1    0    0    -1  
$EndComp
Text Label 3320 6560 0    50   ~ 0
VS
$Comp
L power:GND #PWR07
U 1 1 5E44770C
P 2120 4830
F 0 "#PWR07" H 2120 4580 50  0001 C CNN
F 1 "GND" H 2125 4657 50  0000 C CNN
F 2 "" H 2120 4830 50  0001 C CNN
F 3 "" H 2120 4830 50  0001 C CNN
	1    2120 4830
	1    0    0    -1  
$EndComp
Text GLabel 8380 2260 2    50   Input ~ 0
B1
Text GLabel 8380 2360 2    50   Input ~ 0
B2
Text GLabel 8380 2860 2    50   Input ~ 0
C1
Text GLabel 8380 2960 2    50   Input ~ 0
C2
Text GLabel 7080 2960 0    50   Input ~ 0
E2
Text GLabel 7080 2860 0    50   Input ~ 0
E1
Text GLabel 7080 2660 0    50   Input ~ 0
G2
Text GLabel 7080 2560 0    50   Input ~ 0
G1
Text GLabel 7080 2360 0    50   Input ~ 0
F2
Text GLabel 7080 2260 0    50   Input ~ 0
F1
Text GLabel 7680 1760 1    50   Input ~ 0
A1
Text GLabel 7780 1760 1    50   Input ~ 0
A2
Text GLabel 7680 3560 3    50   Input ~ 0
D2
Text GLabel 7780 3560 3    50   Input ~ 0
D1
NoConn ~ 2620 6160
NoConn ~ 2620 6060
Text GLabel 1220 5860 0    50   Output ~ 0
IN_A1
Text GLabel 1220 5760 0    50   Output ~ 0
IN_A2
Text GLabel 1220 5660 0    50   Output ~ 0
IN_B1
Text GLabel 1220 5560 0    50   Output ~ 0
IN_B2
Text GLabel 1220 5460 0    50   Output ~ 0
IN_C1
Text GLabel 1220 5360 0    50   Output ~ 0
IN_C2
Text GLabel 1220 5260 0    50   Output ~ 0
IN_D1
Text GLabel 1220 5160 0    50   Output ~ 0
IN_D2
Text GLabel 1220 6760 0    50   Output ~ 0
IN_E1
Text GLabel 1220 6660 0    50   Output ~ 0
IN_E2
Text GLabel 1220 6560 0    50   Output ~ 0
IN_F1
Text GLabel 1220 6460 0    50   Output ~ 0
IN_F2
Text GLabel 1220 6360 0    50   Output ~ 0
IN_G1
Text GLabel 1220 6260 0    50   Output ~ 0
IN_G2
$Comp
L power:GND #PWR0101
U 1 1 5E49F24B
P 4080 5260
F 0 "#PWR0101" H 4080 5010 50  0001 C CNN
F 1 "GND" H 4085 5087 50  0000 C CNN
F 2 "" H 4080 5260 50  0001 C CNN
F 3 "" H 4080 5260 50  0001 C CNN
	1    4080 5260
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion:MCP23017_SP U2
U 1 1 5E414079
P 1920 5960
F 0 "U2" V 1940 5930 50  0000 C CNN
F 1 "MCP23017_SP" V 1800 5880 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 2120 4960 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf" H 2120 4860 50  0001 L CNN
	1    1920 5960
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5E4A711D
P 3320 6560
F 0 "#FLG0102" H 3320 6635 50  0001 C CNN
F 1 "PWR_FLAG" H 3320 6733 50  0001 C CNN
F 2 "" H 3320 6560 50  0001 C CNN
F 3 "~" H 3320 6560 50  0001 C CNN
	1    3320 6560
	0    -1   -1   0   
$EndComp
$Comp
L L9110:L9110 U9
U 1 1 5E422161
P 5550 1850
F 0 "U9" H 5550 1430 60  0000 C CNN
F 1 "L9110S" H 5560 1550 60  0000 C CNN
F 2 "Package_SO:SOP-8_3.9x4.9mm_P1.27mm" H 5550 1519 60  0001 C CNN
F 3 "" H 5550 1850 60  0000 C CNN
	1    5550 1850
	-1   0    0    1   
$EndComp
$Comp
L L9110:L9110 U8
U 1 1 5E4238A0
P 5560 2730
F 0 "U8" H 5560 2330 60  0000 C CNN
F 1 "L9110S" H 5560 2440 60  0000 C CNN
F 2 "Package_SO:SOP-8_3.9x4.9mm_P1.27mm" H 5560 2399 60  0001 C CNN
F 3 "" H 5560 2730 60  0000 C CNN
	1    5560 2730
	-1   0    0    1   
$EndComp
$Comp
L L9110:L9110 U7
U 1 1 5E42463D
P 5590 3660
F 0 "U7" H 5590 3260 60  0000 C CNN
F 1 "L9110S" H 5590 3350 60  0000 C CNN
F 2 "Package_SO:SOP-8_3.9x4.9mm_P1.27mm" H 5590 3329 60  0001 C CNN
F 3 "" H 5590 3660 60  0000 C CNN
	1    5590 3660
	-1   0    0    1   
$EndComp
$Comp
L L9110:L9110 U3
U 1 1 5E429115
P 7710 1230
F 0 "U3" H 7710 810 60  0000 C CNN
F 1 "L9110S" H 7710 910 60  0000 C CNN
F 2 "Package_SO:SOP-8_3.9x4.9mm_P1.27mm" H 7710 899 60  0001 C CNN
F 3 "" H 7710 1230 60  0000 C CNN
	1    7710 1230
	-1   0    0    1   
$EndComp
$Comp
L L9110:L9110 U6
U 1 1 5E42A470
P 7720 4220
F 0 "U6" H 7720 3820 60  0000 C CNN
F 1 "L9110S" H 7720 3910 60  0000 C CNN
F 2 "Package_SO:SOP-8_3.9x4.9mm_P1.27mm" H 7720 3889 60  0001 C CNN
F 3 "" H 7720 4220 60  0000 C CNN
	1    7720 4220
	-1   0    0    1   
$EndComp
$Comp
L L9110:L9110 U5
U 1 1 5E42B459
P 9800 3350
F 0 "U5" H 9800 3770 60  0000 C CNN
F 1 "L9110S" H 9800 3670 60  0000 C CNN
F 2 "Package_SO:SOP-8_3.9x4.9mm_P1.27mm" H 9800 3681 60  0001 C CNN
F 3 "" H 9800 3350 60  0000 C CNN
	1    9800 3350
	1    0    0    -1  
$EndComp
$Comp
L L9110:L9110 U4
U 1 1 5E42C132
P 9790 2150
F 0 "U4" H 9790 2570 60  0000 C CNN
F 1 "L9110S" H 9790 2470 60  0000 C CNN
F 2 "Package_SO:SOP-8_3.9x4.9mm_P1.27mm" H 9790 2481 60  0001 C CNN
F 3 "" H 9790 2150 60  0000 C CNN
	1    9790 2150
	1    0    0    -1  
$EndComp
Text GLabel 8260 1380 2    50   Output ~ 0
A1
Text GLabel 8260 1080 2    50   Output ~ 0
A2
Text GLabel 6100 2000 2    50   Output ~ 0
F1
Text GLabel 6100 1700 2    50   Output ~ 0
F2
Text GLabel 6110 2880 2    50   Output ~ 0
G1
Text GLabel 6110 2580 2    50   Output ~ 0
G2
Text GLabel 6140 3810 2    50   Output ~ 0
E1
Text GLabel 6140 3510 2    50   Output ~ 0
E2
Text GLabel 8270 4070 2    50   Output ~ 0
D2
Text GLabel 8270 4370 2    50   Output ~ 0
D1
Text GLabel 9250 3500 0    50   Output ~ 0
C2
Text GLabel 9250 3200 0    50   Output ~ 0
C1
Text GLabel 9240 2000 0    50   Output ~ 0
B1
Text GLabel 9240 2300 0    50   Output ~ 0
B2
Wire Wire Line
	5000 1700 4690 1700
Wire Wire Line
	4690 1700 4690 2000
Wire Wire Line
	4690 2000 5000 2000
$Comp
L power:GND #PWR0102
U 1 1 5E4250FB
P 4690 2000
F 0 "#PWR0102" H 4690 1750 50  0001 C CNN
F 1 "GND" H 4695 1827 50  0000 C CNN
F 2 "" H 4690 2000 50  0001 C CNN
F 3 "" H 4690 2000 50  0001 C CNN
	1    4690 2000
	1    0    0    -1  
$EndComp
Connection ~ 4690 2000
Wire Wire Line
	5010 2580 4700 2580
Wire Wire Line
	4700 2580 4700 2880
Wire Wire Line
	4700 2880 5010 2880
$Comp
L power:GND #PWR0103
U 1 1 5E425828
P 4700 2880
F 0 "#PWR0103" H 4700 2630 50  0001 C CNN
F 1 "GND" H 4705 2707 50  0000 C CNN
F 2 "" H 4700 2880 50  0001 C CNN
F 3 "" H 4700 2880 50  0001 C CNN
	1    4700 2880
	1    0    0    -1  
$EndComp
Connection ~ 4700 2880
Wire Wire Line
	7160 1080 6850 1080
Wire Wire Line
	6850 1080 6850 1380
Wire Wire Line
	6850 1380 7160 1380
$Comp
L power:GND #PWR0104
U 1 1 5E425C98
P 6850 1380
F 0 "#PWR0104" H 6850 1130 50  0001 C CNN
F 1 "GND" H 6855 1207 50  0000 C CNN
F 2 "" H 6850 1380 50  0001 C CNN
F 3 "" H 6850 1380 50  0001 C CNN
	1    6850 1380
	1    0    0    -1  
$EndComp
Connection ~ 6850 1380
Wire Wire Line
	5040 3510 4730 3510
Wire Wire Line
	4730 3510 4730 3810
Wire Wire Line
	4730 3810 5040 3810
$Comp
L power:GND #PWR0105
U 1 1 5E4261CA
P 4730 3810
F 0 "#PWR0105" H 4730 3560 50  0001 C CNN
F 1 "GND" H 4735 3637 50  0000 C CNN
F 2 "" H 4730 3810 50  0001 C CNN
F 3 "" H 4730 3810 50  0001 C CNN
	1    4730 3810
	1    0    0    -1  
$EndComp
Connection ~ 4730 3810
Wire Wire Line
	7170 4070 6860 4070
Wire Wire Line
	6860 4070 6860 4370
Wire Wire Line
	6860 4370 7170 4370
$Comp
L power:GND #PWR0106
U 1 1 5E426A6C
P 6860 4370
F 0 "#PWR0106" H 6860 4120 50  0001 C CNN
F 1 "GND" H 6865 4197 50  0000 C CNN
F 2 "" H 6860 4370 50  0001 C CNN
F 3 "" H 6860 4370 50  0001 C CNN
	1    6860 4370
	1    0    0    -1  
$EndComp
Connection ~ 6860 4370
Wire Wire Line
	10340 2000 10660 2000
Wire Wire Line
	10660 2000 10660 2300
Wire Wire Line
	10660 2300 10340 2300
$Comp
L power:GND #PWR0107
U 1 1 5E42972D
P 10660 2300
F 0 "#PWR0107" H 10660 2050 50  0001 C CNN
F 1 "GND" H 10665 2127 50  0000 C CNN
F 2 "" H 10660 2300 50  0001 C CNN
F 3 "" H 10660 2300 50  0001 C CNN
	1    10660 2300
	1    0    0    -1  
$EndComp
Connection ~ 10660 2300
Wire Wire Line
	10350 3200 10670 3200
Wire Wire Line
	10670 3200 10670 3500
Wire Wire Line
	10670 3500 10350 3500
$Comp
L power:GND #PWR0108
U 1 1 5E42A745
P 10670 3500
F 0 "#PWR0108" H 10670 3250 50  0001 C CNN
F 1 "GND" H 10675 3327 50  0000 C CNN
F 2 "" H 10670 3500 50  0001 C CNN
F 3 "" H 10670 3500 50  0001 C CNN
	1    10670 3500
	1    0    0    -1  
$EndComp
Connection ~ 10670 3500
Wire Wire Line
	8260 1180 8340 1180
Wire Wire Line
	8340 1180 8340 1230
Wire Wire Line
	8340 1280 8260 1280
Wire Wire Line
	6100 1800 6180 1800
Wire Wire Line
	6180 1900 6100 1900
Wire Wire Line
	6110 2680 6190 2680
Wire Wire Line
	6190 2680 6190 2730
Wire Wire Line
	6190 2780 6110 2780
Wire Wire Line
	6140 3610 6220 3610
Wire Wire Line
	6220 3610 6220 3660
Wire Wire Line
	6220 3710 6140 3710
Text Label 6330 3660 0    50   ~ 0
VS
Wire Wire Line
	9250 3300 9160 3300
Wire Wire Line
	9160 3300 9160 3350
Wire Wire Line
	9160 3400 9250 3400
Wire Wire Line
	8270 4170 8350 4170
Wire Wire Line
	8350 4270 8270 4270
Text Label 9040 3350 2    50   ~ 0
VS
Wire Wire Line
	9240 2100 9150 2100
Wire Wire Line
	9150 2100 9150 2160
Wire Wire Line
	9150 2200 9240 2200
Text GLabel 7160 1180 0    50   Input ~ 0
IN_A1
Text GLabel 7160 1280 0    50   Input ~ 0
IN_A2
Text GLabel 5000 1800 0    50   Input ~ 0
IN_F1
Text GLabel 5000 1900 0    50   Input ~ 0
IN_F2
Text GLabel 5010 2680 0    50   Input ~ 0
IN_G1
Text GLabel 5010 2780 0    50   Input ~ 0
IN_G2
Text GLabel 5040 3610 0    50   Input ~ 0
IN_E1
Text GLabel 5040 3710 0    50   Input ~ 0
IN_E2
Text GLabel 7170 4170 0    50   Input ~ 0
IN_D1
Text GLabel 7170 4270 0    50   Input ~ 0
IN_D2
Text GLabel 10340 2200 2    50   Input ~ 0
IN_B1
Text GLabel 10340 2100 2    50   Input ~ 0
IN_B2
Text GLabel 10350 3400 2    50   Input ~ 0
IN_C1
Text GLabel 10350 3300 2    50   Input ~ 0
IN_C2
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5E434D29
P 2120 4830
F 0 "#FLG01" H 2120 4905 50  0001 C CNN
F 1 "PWR_FLAG" H 2120 5003 50  0001 C CNN
F 2 "" H 2120 4830 50  0001 C CNN
F 3 "~" H 2120 4830 50  0001 C CNN
	1    2120 4830
	1    0    0    -1  
$EndComp
Wire Wire Line
	1920 7060 1920 7080
Wire Wire Line
	3790 5160 3970 5160
Wire Wire Line
	3970 5260 3790 5260
Wire Wire Line
	3970 5160 3970 5260
Wire Wire Line
	3970 5360 3970 5260
Wire Wire Line
	3790 5360 3970 5360
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 5E43266B
P 3890 6210
F 0 "J1" V 3750 6240 50  0000 R CNN
F 1 "I2C_PWR_IN" V 3830 6430 50  0000 R CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x05_P2.00mm_Vertical" H 3890 6210 50  0001 C CNN
F 3 "~" H 3890 6210 50  0001 C CNN
	1    3890 6210
	0    1    1    0   
$EndComp
Connection ~ 3970 5260
$Comp
L power:GND #PWR0109
U 1 1 5E4381C3
P 3320 7040
F 0 "#PWR0109" H 3320 6790 50  0001 C CNN
F 1 "GND" H 3325 6867 50  0000 C CNN
F 2 "" H 3320 7040 50  0001 C CNN
F 3 "" H 3320 7040 50  0001 C CNN
	1    3320 7040
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0110
U 1 1 5E43A3B2
P 3320 6480
F 0 "#PWR0110" H 3320 6330 50  0001 C CNN
F 1 "+12V" H 3335 6653 50  0000 C CNN
F 2 "" H 3320 6480 50  0001 C CNN
F 3 "" H 3320 6480 50  0001 C CNN
	1    3320 6480
	1    0    0    -1  
$EndComp
Wire Wire Line
	3320 6480 3320 6560
Wire Wire Line
	3320 6960 3320 7040
Connection ~ 3320 6560
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5E4420B2
P 5330 5950
F 0 "#FLG0101" H 5330 6025 50  0001 C CNN
F 1 "PWR_FLAG" H 5330 6123 50  0001 C CNN
F 2 "" H 5330 5950 50  0001 C CNN
F 3 "~" H 5330 5950 50  0001 C CNN
	1    5330 5950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5E4438F7
P 4850 5810
F 0 "R1" H 4910 5810 50  0000 L CNN
F 1 "10k" V 4850 5730 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4780 5810 50  0001 C CNN
F 3 "~" H 4850 5810 50  0001 C CNN
	1    4850 5810
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5E4466F8
P 5330 6250
F 0 "#PWR0111" H 5330 6000 50  0001 C CNN
F 1 "GND" H 5335 6077 50  0000 C CNN
F 2 "" H 5330 6250 50  0001 C CNN
F 3 "" H 5330 6250 50  0001 C CNN
	1    5330 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E4481FA
P 5330 6100
F 0 "C1" H 5445 6146 50  0000 L CNN
F 1 "100n" H 5445 6055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5368 5950 50  0001 C CNN
F 3 "~" H 5330 6100 50  0001 C CNN
	1    5330 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3970 5260 4080 5260
Wire Wire Line
	1920 4860 1920 4830
Wire Wire Line
	1920 4830 2120 4830
Connection ~ 2120 4830
Wire Wire Line
	2620 5160 3250 5160
Wire Wire Line
	3490 5260 2980 5260
Wire Wire Line
	2620 5360 2720 5360
$Comp
L Device:R R2
U 1 1 5E476472
P 2720 5210
F 0 "R2" H 2740 5360 50  0000 L CNN
F 1 "10k" V 2720 5140 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2650 5210 50  0001 C CNN
F 3 "~" H 2720 5210 50  0001 C CNN
	1    2720 5210
	1    0    0    -1  
$EndComp
Connection ~ 2720 5360
Wire Wire Line
	2720 5360 3490 5360
$Comp
L Device:R R3
U 1 1 5E47709A
P 2980 5110
F 0 "R3" H 3020 5250 50  0000 L CNN
F 1 "10k" V 2980 5040 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2910 5110 50  0001 C CNN
F 3 "~" H 2980 5110 50  0001 C CNN
	1    2980 5110
	1    0    0    -1  
$EndComp
Connection ~ 2980 5260
Wire Wire Line
	2980 5260 2620 5260
$Comp
L Device:R R4
U 1 1 5E47858D
P 3250 5010
F 0 "R4" H 3290 5150 50  0000 L CNN
F 1 "10k" V 3250 4940 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3180 5010 50  0001 C CNN
F 3 "~" H 3250 5010 50  0001 C CNN
	1    3250 5010
	1    0    0    -1  
$EndComp
Connection ~ 3250 5160
Wire Wire Line
	3250 5160 3490 5160
Wire Wire Line
	2720 5060 2720 4680
Wire Wire Line
	2720 4680 2980 4680
Wire Wire Line
	3250 4680 3250 4860
Wire Wire Line
	2980 4960 2980 4680
Connection ~ 2980 4680
Wire Wire Line
	2980 4680 3250 4680
Wire Wire Line
	2980 4680 2980 4560
$Comp
L power:+5V #PWR05
U 1 1 5E48754C
P 5330 5950
F 0 "#PWR05" H 5330 5800 50  0001 C CNN
F 1 "+5V" H 5345 6123 50  0000 C CNN
F 2 "" H 5330 5950 50  0001 C CNN
F 3 "" H 5330 5950 50  0001 C CNN
	1    5330 5950
	1    0    0    -1  
$EndComp
Connection ~ 5330 5950
$Comp
L power:+5V #PWR01
U 1 1 5E48EF5C
P 2740 7030
F 0 "#PWR01" H 2740 6880 50  0001 C CNN
F 1 "+5V" H 2755 7203 50  0000 C CNN
F 2 "" H 2740 7030 50  0001 C CNN
F 3 "" H 2740 7030 50  0001 C CNN
	1    2740 7030
	1    0    0    -1  
$EndComp
Wire Wire Line
	3060 6860 3060 7080
Wire Wire Line
	1920 7080 2740 7080
Wire Wire Line
	2740 7030 2740 7080
Connection ~ 2740 7080
Wire Wire Line
	2740 7080 3060 7080
$Comp
L power:+5V #PWR02
U 1 1 5E49EAE9
P 2980 4560
F 0 "#PWR02" H 2980 4410 50  0001 C CNN
F 1 "+5V" H 2995 4733 50  0000 C CNN
F 2 "" H 2980 4560 50  0001 C CNN
F 3 "" H 2980 4560 50  0001 C CNN
	1    2980 4560
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5E4A1977
P 4850 5660
F 0 "#PWR03" H 4850 5510 50  0001 C CNN
F 1 "+5V" H 4865 5833 50  0000 C CNN
F 2 "" H 4850 5660 50  0001 C CNN
F 3 "" H 4850 5660 50  0001 C CNN
	1    4850 5660
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E4A20D6
P 4850 6110
F 0 "C2" H 4965 6156 50  0000 L CNN
F 1 "100n" H 4965 6065 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4888 5960 50  0001 C CNN
F 3 "~" H 4850 6110 50  0001 C CNN
	1    4850 6110
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5E4A29B6
P 4850 6260
F 0 "#PWR04" H 4850 6010 50  0001 C CNN
F 1 "GND" H 4855 6087 50  0000 C CNN
F 2 "" H 4850 6260 50  0001 C CNN
F 3 "" H 4850 6260 50  0001 C CNN
	1    4850 6260
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5960 4650 5960
Connection ~ 4850 5960
Text GLabel 4650 5960 0    50   Input ~ 0
RESET
Text GLabel 2620 5860 2    50   Input ~ 0
RESET
Wire Wire Line
	6330 3660 6220 3660
Connection ~ 6220 3660
Wire Wire Line
	6220 3660 6220 3710
Text Label 6300 2730 0    50   ~ 0
VS
Wire Wire Line
	6300 2730 6190 2730
Connection ~ 6190 2730
Wire Wire Line
	6190 2730 6190 2780
Text Label 6290 1840 0    50   ~ 0
VS
Wire Wire Line
	6290 1840 6180 1840
Wire Wire Line
	6180 1800 6180 1840
Connection ~ 6180 1840
Wire Wire Line
	6180 1840 6180 1900
Text Label 8450 1230 0    50   ~ 0
VS
Wire Wire Line
	8450 1230 8340 1230
Connection ~ 8340 1230
Wire Wire Line
	8340 1230 8340 1280
Text Label 8460 4210 0    50   ~ 0
VS
Wire Wire Line
	8460 4210 8350 4210
Wire Wire Line
	8350 4170 8350 4210
Connection ~ 8350 4210
Wire Wire Line
	8350 4210 8350 4270
Wire Wire Line
	9040 3350 9160 3350
Connection ~ 9160 3350
Wire Wire Line
	9160 3350 9160 3400
Text Label 9030 2160 2    50   ~ 0
VS
Wire Wire Line
	9030 2160 9150 2160
Connection ~ 9150 2160
Wire Wire Line
	9150 2160 9150 2200
$Comp
L Jumper:SolderJumper_2_Open JP3
U 1 1 5E43B2A6
P 3640 5360
F 0 "JP3" H 3430 5390 50  0000 C CNN
F 1 "A2" H 3860 5390 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 3640 5360 50  0001 C CNN
F 3 "~" H 3640 5360 50  0001 C CNN
	1    3640 5360
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 5E43AE44
P 3640 5260
F 0 "JP2" H 3430 5290 50  0000 C CNN
F 1 "A1" H 3860 5290 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 3640 5260 50  0001 C CNN
F 3 "~" H 3640 5260 50  0001 C CNN
	1    3640 5260
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5E43A594
P 3640 5160
F 0 "JP1" H 3430 5190 50  0000 C CNN
F 1 "A0" H 3860 5190 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 3640 5160 50  0001 C CNN
F 3 "~" H 3640 5160 50  0001 C CNN
	1    3640 5160
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5E4574E7
P 3890 7330
F 0 "J2" V 3730 7370 50  0000 R CNN
F 1 "I2C_PWR_OUT" V 3820 7580 50  0000 R CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x05_P2.00mm_Vertical" H 3890 7330 50  0001 C CNN
F 3 "~" H 3890 7330 50  0001 C CNN
	1    3890 7330
	0    1    -1   0   
$EndComp
Wire Wire Line
	3690 6560 3690 6410
Wire Wire Line
	3320 6560 3690 6560
Wire Wire Line
	3790 6660 3790 6410
Wire Wire Line
	2620 6660 3790 6660
Wire Wire Line
	3890 6760 3890 6410
Wire Wire Line
	2620 6760 3890 6760
Wire Wire Line
	3990 6860 3990 6410
Wire Wire Line
	3060 6860 3990 6860
Wire Wire Line
	4090 6960 4090 6410
Wire Wire Line
	3320 6960 4090 6960
Wire Wire Line
	3690 7130 3690 6560
Connection ~ 3690 6560
Wire Wire Line
	3790 7130 3790 6660
Connection ~ 3790 6660
Wire Wire Line
	3890 7130 3890 6760
Connection ~ 3890 6760
Wire Wire Line
	3990 7130 3990 6860
Connection ~ 3990 6860
Wire Wire Line
	4090 7130 4090 6960
Connection ~ 4090 6960
$Comp
L Device:LED D1
U 1 1 5E49CFB4
P 2080 3400
F 0 "D1" V 2027 3478 50  0000 L CNN
F 1 "LED" V 2118 3478 50  0000 L CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2080 3400 50  0001 C CNN
F 3 "~" H 2080 3400 50  0001 C CNN
	1    2080 3400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 5E49EA5B
P 2080 3100
F 0 "R5" H 2150 3146 50  0000 L CNN
F 1 "330" H 2150 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2010 3100 50  0001 C CNN
F 3 "~" H 2080 3100 50  0001 C CNN
	1    2080 3100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5E4A2752
P 2080 3550
F 0 "#PWR08" H 2080 3300 50  0001 C CNN
F 1 "GND" H 2085 3377 50  0000 C CNN
F 2 "" H 2080 3550 50  0001 C CNN
F 3 "" H 2080 3550 50  0001 C CNN
	1    2080 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 5E4A2A6C
P 2080 2950
F 0 "#PWR06" H 2080 2800 50  0001 C CNN
F 1 "+5V" H 2095 3123 50  0000 C CNN
F 2 "" H 2080 2950 50  0001 C CNN
F 3 "" H 2080 2950 50  0001 C CNN
	1    2080 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5E4A4BDB
P 2520 3400
F 0 "D2" V 2467 3478 50  0000 L CNN
F 1 "LED" V 2558 3478 50  0000 L CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2520 3400 50  0001 C CNN
F 3 "~" H 2520 3400 50  0001 C CNN
	1    2520 3400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R7
U 1 1 5E4A4BE1
P 2520 3100
F 0 "R7" H 2590 3146 50  0000 L CNN
F 1 "1k" H 2590 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2450 3100 50  0001 C CNN
F 3 "~" H 2520 3100 50  0001 C CNN
	1    2520 3100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E4A4BE7
P 2520 3550
F 0 "#PWR010" H 2520 3300 50  0001 C CNN
F 1 "GND" H 2525 3377 50  0000 C CNN
F 2 "" H 2520 3550 50  0001 C CNN
F 3 "" H 2520 3550 50  0001 C CNN
	1    2520 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR09
U 1 1 5E4A78AE
P 2520 2950
F 0 "#PWR09" H 2520 2800 50  0001 C CNN
F 1 "+12V" H 2535 3123 50  0000 C CNN
F 2 "" H 2520 2950 50  0001 C CNN
F 3 "" H 2520 2950 50  0001 C CNN
	1    2520 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5E4742A7
P 1660 3400
F 0 "D3" V 1607 3478 50  0000 L CNN
F 1 "LED" V 1698 3478 50  0000 L CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1660 3400 50  0001 C CNN
F 3 "~" H 1660 3400 50  0001 C CNN
	1    1660 3400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 5E4742AD
P 1660 3100
F 0 "R6" H 1730 3146 50  0000 L CNN
F 1 "330" H 1730 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1590 3100 50  0001 C CNN
F 3 "~" H 1660 3100 50  0001 C CNN
	1    1660 3100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5E4742B3
P 1660 3550
F 0 "#PWR011" H 1660 3300 50  0001 C CNN
F 1 "GND" H 1665 3377 50  0000 C CNN
F 2 "" H 1660 3550 50  0001 C CNN
F 3 "" H 1660 3550 50  0001 C CNN
	1    1660 3550
	1    0    0    -1  
$EndComp
Text GLabel 1660 2950 1    50   Input ~ 0
B6
Text GLabel 1220 6160 0    50   Output ~ 0
B6
Wire Notes Line
	2670 2720 2670 3800
Wire Notes Line
	2670 3800 1430 3800
Wire Notes Line
	1430 3800 1430 2710
Wire Notes Line
	1430 2710 2670 2710
Text Notes 1800 2700 0    50   ~ 0
Indicator LEDs
Text GLabel 3390 2550 2    50   Input ~ 0
IN_A1
Text GLabel 3390 2640 2    50   Input ~ 0
IN_A2
Text GLabel 3390 2730 2    50   Input ~ 0
IN_B1
Text GLabel 3390 2820 2    50   Input ~ 0
IN_B2
Text GLabel 3390 2910 2    50   Input ~ 0
IN_C1
Text GLabel 3390 3000 2    50   Input ~ 0
IN_C2
Text GLabel 3390 3090 2    50   Input ~ 0
IN_D1
Text GLabel 3390 3180 2    50   Input ~ 0
IN_D2
Text GLabel 3390 3270 2    50   Input ~ 0
IN_E1
Text GLabel 3390 3360 2    50   Input ~ 0
IN_E2
Text GLabel 3390 3450 2    50   Input ~ 0
IN_F1
Text GLabel 3390 3540 2    50   Input ~ 0
IN_F2
Text GLabel 3390 3630 2    50   Input ~ 0
IN_G1
Text GLabel 3390 3720 2    50   Input ~ 0
IN_G2
$Comp
L Device:R R11
U 1 1 5E51DE79
P 3240 2820
F 0 "R11" V 3240 3240 50  0000 L CNN
F 1 "10k" V 3240 2740 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 2820 50  0001 C CNN
F 3 "~" H 3240 2820 50  0001 C CNN
	1    3240 2820
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 5E51E600
P 3240 2730
F 0 "R10" V 3240 3150 50  0000 L CNN
F 1 "10k" V 3240 2650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 2730 50  0001 C CNN
F 3 "~" H 3240 2730 50  0001 C CNN
	1    3240 2730
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 5E51ED14
P 3240 2640
F 0 "R9" V 3240 3060 50  0000 L CNN
F 1 "10k" V 3240 2560 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 2640 50  0001 C CNN
F 3 "~" H 3240 2640 50  0001 C CNN
	1    3240 2640
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 5E51F19D
P 3240 2550
F 0 "R8" V 3240 2970 50  0000 L CNN
F 1 "10k" V 3240 2470 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 2550 50  0001 C CNN
F 3 "~" H 3240 2550 50  0001 C CNN
	1    3240 2550
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 5E51F497
P 3240 3180
F 0 "R15" V 3240 3600 50  0000 L CNN
F 1 "10k" V 3240 3100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3180 50  0001 C CNN
F 3 "~" H 3240 3180 50  0001 C CNN
	1    3240 3180
	0    1    1    0   
$EndComp
$Comp
L Device:R R14
U 1 1 5E51F99E
P 3240 3090
F 0 "R14" V 3240 3510 50  0000 L CNN
F 1 "10k" V 3240 3010 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3090 50  0001 C CNN
F 3 "~" H 3240 3090 50  0001 C CNN
	1    3240 3090
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 5E51FCD7
P 3240 3000
F 0 "R13" V 3240 3420 50  0000 L CNN
F 1 "10k" V 3240 2920 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3000 50  0001 C CNN
F 3 "~" H 3240 3000 50  0001 C CNN
	1    3240 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 5E52004F
P 3240 2910
F 0 "R12" V 3240 3330 50  0000 L CNN
F 1 "10k" V 3240 2830 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 2910 50  0001 C CNN
F 3 "~" H 3240 2910 50  0001 C CNN
	1    3240 2910
	0    1    1    0   
$EndComp
$Comp
L Device:R R19
U 1 1 5E520388
P 3240 3540
F 0 "R19" V 3240 3960 50  0000 L CNN
F 1 "10k" V 3240 3460 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3540 50  0001 C CNN
F 3 "~" H 3240 3540 50  0001 C CNN
	1    3240 3540
	0    1    1    0   
$EndComp
$Comp
L Device:R R18
U 1 1 5E5209F4
P 3240 3450
F 0 "R18" V 3240 3870 50  0000 L CNN
F 1 "10k" V 3240 3370 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3450 50  0001 C CNN
F 3 "~" H 3240 3450 50  0001 C CNN
	1    3240 3450
	0    1    1    0   
$EndComp
$Comp
L Device:R R17
U 1 1 5E520D57
P 3240 3360
F 0 "R17" V 3240 3780 50  0000 L CNN
F 1 "10k" V 3240 3280 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3360 50  0001 C CNN
F 3 "~" H 3240 3360 50  0001 C CNN
	1    3240 3360
	0    1    1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 5E521306
P 3240 3270
F 0 "R16" V 3240 3690 50  0000 L CNN
F 1 "10k" V 3240 3190 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3270 50  0001 C CNN
F 3 "~" H 3240 3270 50  0001 C CNN
	1    3240 3270
	0    1    1    0   
$EndComp
$Comp
L Device:R R21
U 1 1 5E5217B9
P 3240 3720
F 0 "R21" V 3240 4140 50  0000 L CNN
F 1 "10k" V 3240 3640 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3720 50  0001 C CNN
F 3 "~" H 3240 3720 50  0001 C CNN
	1    3240 3720
	0    1    1    0   
$EndComp
$Comp
L Device:R R20
U 1 1 5E521D3E
P 3240 3630
F 0 "R20" V 3250 4050 50  0000 L CNN
F 1 "10k" V 3240 3550 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3170 3630 50  0001 C CNN
F 3 "~" H 3240 3630 50  0001 C CNN
	1    3240 3630
	0    1    1    0   
$EndComp
Wire Wire Line
	3090 2550 3090 2640
Connection ~ 3090 2640
Wire Wire Line
	3090 2640 3090 2730
Connection ~ 3090 2730
Wire Wire Line
	3090 3720 3090 3630
Wire Wire Line
	3090 3630 3090 3540
Connection ~ 3090 3630
Wire Wire Line
	3090 3450 3090 3540
Connection ~ 3090 3540
Wire Wire Line
	3090 3360 3090 3450
Connection ~ 3090 3450
Connection ~ 3090 3360
Wire Wire Line
	3090 3180 3090 3270
Wire Wire Line
	3090 3090 3090 3180
Connection ~ 3090 3180
Wire Wire Line
	3090 3000 3090 3090
Connection ~ 3090 3090
Wire Wire Line
	3090 2730 3090 2820
Connection ~ 3090 2820
Wire Wire Line
	3090 2820 3090 2910
Wire Wire Line
	3090 2910 3090 3000
Connection ~ 3090 2910
Connection ~ 3090 3000
Wire Wire Line
	3090 3270 3090 3360
Connection ~ 3090 3270
Wire Notes Line
	3840 2480 3840 3930
Wire Notes Line
	3840 3930 3010 3930
Wire Notes Line
	3010 3930 3010 2480
Wire Notes Line
	3010 2480 3840 2480
Text Notes 3170 2460 0    50   ~ 0
 Pulldowns for \nL9110S Inputs
$Comp
L power:GND #PWR0112
U 1 1 5E4F2D98
P 3090 3720
F 0 "#PWR0112" H 3090 3470 50  0001 C CNN
F 1 "GND" H 3095 3547 50  0000 C CNN
F 2 "" H 3090 3720 50  0001 C CNN
F 3 "" H 3090 3720 50  0001 C CNN
	1    3090 3720
	1    0    0    -1  
$EndComp
Connection ~ 3090 3720
$Comp
L Connector:Conn_01x01_Male J3
U 1 1 5E4F53BB
P 1020 6060
F 0 "J3" H 980 6100 50  0000 C CNN
F 1 "Pad_IO16" H 930 6100 50  0001 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 1020 6060 50  0001 C CNN
F 3 "~" H 1020 6060 50  0001 C CNN
	1    1020 6060
	1    0    0    -1  
$EndComp
$EndSCHEMATC
