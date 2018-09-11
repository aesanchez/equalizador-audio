#include "clock.h"
char HH = 23;
char MM = 59;
char SS = 55;

//asumimos que es llamado cada 1 segundo
void clock_tick(void) {
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
//el string que pasa por referencia debe ser de minimo 9 caracteres(8+caracter nulo)
void clock_get_time_as_str(char str[]) {
	str[0] = HH / 10 + '0';
	str[1] = HH % 10 + '0';
	str[2] = ':';
	str[3] = MM / 10 + '0';
	str[4] = MM % 10 + '0';
	str[5] = ':';
	str[6] = SS / 10 + '0';
	str[7] = SS % 10 + '0';
	str[8] = '\0';
}

void clock_set_time(char hh, char mm, char ss) {
	if (hh < IGNORE_HH)
		HH = hh;
	if (mm < IGNORE_MM)
		MM = mm;
	if (ss < IGNORE_SS)
		SS = ss;
}