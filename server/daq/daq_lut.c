/*
 * daq_lut.c
 *
 */


#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../daq/daq_lut.h"

typedef struct {
	float x;
	float y;
}lookup_table;

lookup_table lut0[LUT_GROESSE]; // 2 pages;
lookup_table lut1[LUT_GROESSE];
lookup_table lut2[LUT_GROESSE];
lookup_table lut3[LUT_GROESSE];

void DAQ_set_lut(uint8_t lut_id, uint8_t row, float x_value, float y_value) {
	//lut--;
	switch(lut_id){
	case 0:
		lut0[row].x = x_value;
		lut0[row].y = y_value;
		break;
	case 1:
		lut1[row].x = x_value;
		lut1[row].y = y_value;
		break;
	case 2:
		lut2[row].x = x_value;
		lut2[row].y = y_value;
		break;
	case 3:
		lut3[row].x = x_value;
		lut3[row].y = y_value;
		break;
	default:
		lut0[row].x = x_value;
		lut0[row].y = y_value;
		break;
	}
}
void DAQ_set_ldr(uint8_t lut_id) {
	DAQ_set_lut(lut_id, 0, 3837, 0.5);
	DAQ_set_lut(lut_id, 1, 3638, 1);
	DAQ_set_lut(lut_id, 2, 2666, 5);
	DAQ_set_lut(lut_id, 3, 2048, 10);
	DAQ_set_lut(lut_id, 4, 1678, 15);
	DAQ_set_lut(lut_id, 5, 1429, 20);
	DAQ_set_lut(lut_id, 6, 1248, 25);
	DAQ_set_lut(lut_id, 7, 1110, 30);
	DAQ_set_lut(lut_id, 8, 1001, 35);
	DAQ_set_lut(lut_id, 9, 913, 40);
	DAQ_set_lut(lut_id, 10, 779, 50);
	DAQ_set_lut(lut_id, 11, 680, 60);
	DAQ_set_lut(lut_id, 12, 605, 70);
	DAQ_set_lut(lut_id, 13, 546, 80);
	DAQ_set_lut(lut_id, 14, 498, 90);
	DAQ_set_lut(lut_id, 15, 457, 100);
	DAQ_set_lut(lut_id, 16, 395, 120);
	DAQ_set_lut(lut_id, 17, 348, 140);
	DAQ_set_lut(lut_id, 18, 312, 160);
	DAQ_set_lut(lut_id, 19, 282, 180);
	DAQ_set_lut(lut_id, 20, 258, 200);
	DAQ_set_lut(lut_id, 21, 234, 225);
	DAQ_set_lut(lut_id, 22, 214, 250);
	DAQ_set_lut(lut_id, 23, 197, 275);
	DAQ_set_lut(lut_id, 24, 183, 300);
	DAQ_set_lut(lut_id, 25, 171, 325);
	DAQ_set_lut(lut_id, 26, 160, 350);
	DAQ_set_lut(lut_id, 27, 151, 375);
	DAQ_set_lut(lut_id, 28, 142, 400);
	DAQ_set_lut(lut_id, 29, 135, 425);
	DAQ_set_lut(lut_id, 30, 128, 450);
	DAQ_set_lut(lut_id, 31, 123, 475);
	DAQ_set_lut(lut_id, 32, 117, 500);
	DAQ_set_lut(lut_id, 33, 112, 525);
	DAQ_set_lut(lut_id, 34, 108, 550);
	DAQ_set_lut(lut_id, 35, 104, 575);
	DAQ_set_lut(lut_id, 36, 100, 600);
	DAQ_set_lut(lut_id, 37, 96, 625);
	DAQ_set_lut(lut_id, 38, 93, 650);
	DAQ_set_lut(lut_id, 39, 90, 675);
	DAQ_set_lut(lut_id, 40, 87, 700);
	DAQ_set_lut(lut_id, 41, 84, 725);
	DAQ_set_lut(lut_id, 42, 82, 750);
	DAQ_set_lut(lut_id, 43, 80, 775);
	DAQ_set_lut(lut_id, 44, 77, 800);
	DAQ_set_lut(lut_id, 45, 75, 825);
	DAQ_set_lut(lut_id, 46, 73, 850);
	DAQ_set_lut(lut_id, 47, 71, 875);
	DAQ_set_lut(lut_id, 48, 70, 900);
	DAQ_set_lut(lut_id, 49, 68, 925);
	DAQ_set_lut(lut_id, 50, 66, 950);
	DAQ_set_lut(lut_id, 51, 65, 975);
	DAQ_set_lut(lut_id, 52, 63, 1000);
	DAQ_set_lut(lut_id, 53, 61, 1050);
	DAQ_set_lut(lut_id, 54, 58, 1100);
	DAQ_set_lut(lut_id, 55, 56, 1150);
	DAQ_set_lut(lut_id, 56, 54, 1200);
	DAQ_set_lut(lut_id, 57, 52, 1250);
	DAQ_set_lut(lut_id, 58, 50, 1300);
	DAQ_set_lut(lut_id, 59, 48, 1350);
	DAQ_set_lut(lut_id, 60, 47, 1400);
	DAQ_set_lut(lut_id, 61, 45, 1450);
	DAQ_set_lut(lut_id, 62, 44, 1500);
	DAQ_set_lut(lut_id, 63, 43, 1550);
	DAQ_set_lut(lut_id, 64, 42, 1600);
	DAQ_set_lut(lut_id, 65, 40, 1650);
	DAQ_set_lut(lut_id, 66, 39, 1700);
	DAQ_set_lut(lut_id, 67, 38, 1750);
	DAQ_set_lut(lut_id, 68, 37, 1800);
	DAQ_set_lut(lut_id, 69, 36, 1850);
	DAQ_set_lut(lut_id, 70, 36, 1900);
	DAQ_set_lut(lut_id, 71, 35, 1950);
	DAQ_set_lut(lut_id, 72, 34, 2000);
	DAQ_set_lut(lut_id, 73, 33, 2050);
	DAQ_set_lut(lut_id, 74, 33, 2100);
	DAQ_set_lut(lut_id, 75, 32, 2150);
	DAQ_set_lut(lut_id, 76, 31, 2200);
	DAQ_set_lut(lut_id, 77, 31, 2250);
	DAQ_set_lut(lut_id, 78, 30, 2300);
	DAQ_set_lut(lut_id, 79, 29, 2350);
	DAQ_set_lut(lut_id, 80, 29, 2400);
	DAQ_set_lut(lut_id, 81, 28, 2450);
	DAQ_set_lut(lut_id, 82, 28, 2500);
	DAQ_set_lut(lut_id, 83, 27, 2550);
	DAQ_set_lut(lut_id, 84, 27, 2600);
	DAQ_set_lut(lut_id, 85, 26, 2650);
	DAQ_set_lut(lut_id, 86, 26, 2700);
	DAQ_set_lut(lut_id, 87, 25, 2750);
	DAQ_set_lut(lut_id, 88, 25, 2800);
	DAQ_set_lut(lut_id, 89, 25, 2850);
	DAQ_set_lut(lut_id, 90, 24, 2900);
	DAQ_set_lut(lut_id, 91, 24, 2950);
	DAQ_set_lut(lut_id, 92, 24, 3000);
	DAQ_set_lut(lut_id, 93, 18, 4000);
	DAQ_set_lut(lut_id, 94, 15, 5000);
	DAQ_set_lut(lut_id, 95, 12, 6000);
	DAQ_set_lut(lut_id, 96, 11, 7000);
	DAQ_set_lut(lut_id, 97, 9, 8000);
	DAQ_set_lut(lut_id, 98, 8, 9000);
	DAQ_set_lut(lut_id, 99, 8, 10000);
	DAQ_set_lut(lut_id, 100, 7, 11000);
	DAQ_set_lut(lut_id, 101, 6, 12000);
	DAQ_set_lut(lut_id, 102, 6, 13000);
	DAQ_set_lut(lut_id, 103, 6, 14000);
	DAQ_set_lut(lut_id, 104, 5, 15000);
	DAQ_set_lut(lut_id, 105, 5, 16000);
	DAQ_set_lut(lut_id, 106, 5, 17000);
	DAQ_set_lut(lut_id, 107, 4, 18000);
	DAQ_set_lut(lut_id, 108, 4, 19000);
	DAQ_set_lut(lut_id, 109, 4, 20000);
	DAQ_set_lut(lut_id, 110, 4, 21000);
	DAQ_set_lut(lut_id, 111, 3, 30000);
	DAQ_set_lut(lut_id, 112, 2, 35000);
	DAQ_set_lut(lut_id, 113, 2, 40000);
	DAQ_set_lut(lut_id, 114, 2, 45000);
	DAQ_set_lut(lut_id, 115, 1, 50000);
	DAQ_set_lut(lut_id, 116, 1, 55000);
	DAQ_set_lut(lut_id, 117, 1, 60000);
	DAQ_set_lut(lut_id, 118, 1, 65000);
	DAQ_set_lut(lut_id, 119, 1, 70000);
	DAQ_set_lut(lut_id, 120, 1, 75000);
	DAQ_set_lut(lut_id, 121, 1, 80000);
	DAQ_set_lut(lut_id, 122, 1, 85000);
	DAQ_set_lut(lut_id, 123, 1, 90000);
	DAQ_set_lut(lut_id, 124, 1, 95000);
	DAQ_set_lut(lut_id, 125, 1, 100000);
	DAQ_set_lut(lut_id, 126, 0, 105000);
	DAQ_set_lut(lut_id, 127, 0, 110000);
	DAQ_set_lut(lut_id, 128, 0, 115000);

}

void DAQ_set_ntc(uint8_t lut_id) {
	DAQ_set_lut(lut_id, 0, 3740, -40);
	DAQ_set_lut(lut_id, 1, 3722, -39);
	DAQ_set_lut(lut_id, 2, 3703, -38);
	DAQ_set_lut(lut_id, 3, 3683, -37);
	DAQ_set_lut(lut_id, 4, 3663, -36);
	DAQ_set_lut(lut_id, 5, 3643, -35);
	DAQ_set_lut(lut_id, 6, 3621, -34);
	DAQ_set_lut(lut_id, 7, 3599, -33);
	DAQ_set_lut(lut_id, 8, 3576, -32);
	DAQ_set_lut(lut_id, 9, 3553, -31);
	DAQ_set_lut(lut_id, 10, 3528, -30);
	DAQ_set_lut(lut_id, 11, 3503, -29);
	DAQ_set_lut(lut_id, 12, 3476, -28);
	DAQ_set_lut(lut_id, 13, 3449, -27);
	DAQ_set_lut(lut_id, 14, 3422, -26);
	DAQ_set_lut(lut_id, 15, 3393, -25);
	DAQ_set_lut(lut_id, 16, 3364, -24);
	DAQ_set_lut(lut_id, 17, 3334, -23);
	DAQ_set_lut(lut_id, 18, 3304, -22);
	DAQ_set_lut(lut_id, 19, 3273, -21);
	DAQ_set_lut(lut_id, 20, 3241, -20);
	DAQ_set_lut(lut_id, 21, 3208, -19);
	DAQ_set_lut(lut_id, 22, 3174, -18);
	DAQ_set_lut(lut_id, 23, 3140, -17);
	DAQ_set_lut(lut_id, 24, 3105, -16);
	DAQ_set_lut(lut_id, 25, 3069, -15);
	DAQ_set_lut(lut_id, 26, 3033, -14);
	DAQ_set_lut(lut_id, 27, 2996, -13);
	DAQ_set_lut(lut_id, 28, 2959, -12);
	DAQ_set_lut(lut_id, 29, 2921, -11);
	DAQ_set_lut(lut_id, 30, 2883, -10);
	DAQ_set_lut(lut_id, 31, 2843, -9);
	DAQ_set_lut(lut_id, 32, 2804, -8);
	DAQ_set_lut(lut_id, 33, 2764, -7);
	DAQ_set_lut(lut_id, 34, 2723, -6);
	DAQ_set_lut(lut_id, 35, 2682, -5);
	DAQ_set_lut(lut_id, 36, 2641, -4);
	DAQ_set_lut(lut_id, 37, 2600, -3);
	DAQ_set_lut(lut_id, 38, 2559, -2);
	DAQ_set_lut(lut_id, 39, 2517, -1);
	DAQ_set_lut(lut_id, 40, 2475, 0);
	DAQ_set_lut(lut_id, 41, 2433, 1);
	DAQ_set_lut(lut_id, 42, 2390, 2);
	DAQ_set_lut(lut_id, 43, 2348, 3);
	DAQ_set_lut(lut_id, 44, 2306, 4);
	DAQ_set_lut(lut_id, 45, 2263, 5);
	DAQ_set_lut(lut_id, 46, 2221, 6);
	DAQ_set_lut(lut_id, 47, 2179, 7);
	DAQ_set_lut(lut_id, 48, 2137, 8);
	DAQ_set_lut(lut_id, 49, 2096, 9);
	DAQ_set_lut(lut_id, 50, 2054, 10);
	DAQ_set_lut(lut_id, 51, 2012, 11);
	DAQ_set_lut(lut_id, 52, 1971, 12);
	DAQ_set_lut(lut_id, 53, 1930, 13);
	DAQ_set_lut(lut_id, 54, 1889, 14);
	DAQ_set_lut(lut_id, 55, 1849, 15);
	DAQ_set_lut(lut_id, 56, 1809, 16);
	DAQ_set_lut(lut_id, 57, 1770, 17);
	DAQ_set_lut(lut_id, 58, 1730, 18);
	DAQ_set_lut(lut_id, 59, 1692, 19);
	DAQ_set_lut(lut_id, 60, 1655, 20);
	DAQ_set_lut(lut_id, 61, 1616, 21);
	DAQ_set_lut(lut_id, 62, 1580, 22);
	DAQ_set_lut(lut_id, 63, 1543, 23);
	DAQ_set_lut(lut_id, 64, 1507, 24);
	DAQ_set_lut(lut_id, 65, 1471, 25);
	DAQ_set_lut(lut_id, 66, 1436, 26);
	DAQ_set_lut(lut_id, 67, 1402, 27);
	DAQ_set_lut(lut_id, 68, 1368, 28);
	DAQ_set_lut(lut_id, 69, 1335, 29);
	DAQ_set_lut(lut_id, 70, 1302, 30);
	DAQ_set_lut(lut_id, 71, 1286, 31);
	DAQ_set_lut(lut_id, 72, 1238, 32);
	DAQ_set_lut(lut_id, 73, 1207, 33);
	DAQ_set_lut(lut_id, 74, 1177, 34);
	DAQ_set_lut(lut_id, 75, 1147, 35);
	DAQ_set_lut(lut_id, 76, 1118, 36);
	DAQ_set_lut(lut_id, 77, 1090, 37);
	DAQ_set_lut(lut_id, 78, 1062, 38);
	DAQ_set_lut(lut_id, 79, 1073, 39);
	DAQ_set_lut(lut_id, 80, 1009, 40);
	DAQ_set_lut(lut_id, 81, 982, 41);
	DAQ_set_lut(lut_id, 82, 957, 42);
	DAQ_set_lut(lut_id, 83, 932, 43);
	DAQ_set_lut(lut_id, 84, 1006, 44);
	DAQ_set_lut(lut_id, 85, 884, 45);
	DAQ_set_lut(lut_id, 86, 861, 46);
	DAQ_set_lut(lut_id, 87, 839, 47);
	DAQ_set_lut(lut_id, 88, 817, 48);
	DAQ_set_lut(lut_id, 89, 795, 49);
	DAQ_set_lut(lut_id, 90, 775, 50);
	DAQ_set_lut(lut_id, 91, 791, 51);
	DAQ_set_lut(lut_id, 92, 734, 52);
	DAQ_set_lut(lut_id, 93, 715, 53);
	DAQ_set_lut(lut_id, 94, 696, 54);
	DAQ_set_lut(lut_id, 95, 678, 55);
	DAQ_set_lut(lut_id, 96, 660, 56);
	DAQ_set_lut(lut_id, 97, 642, 57);
	DAQ_set_lut(lut_id, 98, 625, 58);
	DAQ_set_lut(lut_id, 99, 609, 59);
	DAQ_set_lut(lut_id, 100, 626, 60);
	DAQ_set_lut(lut_id, 101, 577, 61);
}
void DAQ_calc_value(float *lut_x, float *lut_y, uint16_t adc_value, float *result){
	float m;
	for (uint8_t i = 0; i < LUT_GROESSE; i++){
		if (*lut_x < adc_value) {
			m = (*lut_y - *(lut_y-2)) / (*lut_x - *(lut_x - 2));
			*result = m * (adc_value - *lut_x) + *lut_y;
			break;
		}
		lut_x = lut_x + 2;
		lut_y = lut_y + 2;
	}
}
void DAQ_value_from_lut(uint8_t lut_id, uint16_t adc_value, float *result) {

	switch (lut_id) {
	case 0:
		DAQ_calc_value(&lut0[0].x, &lut0[0].y,  adc_value, result);
		break;
	case 1:
		DAQ_calc_value(&lut1[0].x, &(lut1[0]).y, adc_value, result);
		break;
	case 2:
		DAQ_calc_value(&lut2[0].x, &(lut2[0]).y, adc_value, result);
		break;
	case 3:
		DAQ_calc_value(&lut3[0].x, &lut3[0].y, adc_value, result);
		break;
	default:
		DAQ_calc_value(&lut0[0].x, &lut0[0].y, adc_value, result);
		break;
	}
}

