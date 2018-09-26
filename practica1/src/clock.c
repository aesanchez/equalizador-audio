#include "clock.h"
char HH = 23;
char MM = 59;
char SS = 55;
char DS = 0; //decima de segundo

//asumimos que es llamado cada 1 segundo
void clock_tick_sec(void) {
	SS++;
	if (SS == 60) {
		SS = 0;
		MM++;
		if (MM == 60) {
			MM = 0;
			HH++;
			if (HH == 24) {
				HH = 0;
			}
		}
	}
}
void clock_tick_dsec(void){
	DS++;
	if(DS == 10){
		DS=0;
		//paso un segundo
		clock_tick_sec();
	}
}
//el string que pasa por referencia debe ser de minimo 11 caracteres(+caracter nulo)
void clock_get_time_as_str(char str[]) {
	str[0] = HH / 10 + '0';
	str[1] = HH % 10 + '0';
	str[2] = ':';
	str[3] = MM / 10 + '0';
	str[4] = MM % 10 + '0';
	str[5] = ':';
	str[6] = SS / 10 + '0';
	str[7] = SS % 10 + '0';
	str[8] = ':';
	str[9] = DS  + '0';
	str[10] = '\0';
}