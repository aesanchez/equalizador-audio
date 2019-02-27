#include "adc.h"
#include "dac.h"
#include "lowpass.h"
#include "bandpass.h"
#include "filter1.h"
#include "filter2.h"
#include "filter3.h"
#include "filter4.h"
#include "fir_q31.h"

fir_q31_t filtro;
int history_band[BANDPASS_TAP_NUM];
int history_1[FILTER1_TAP_NUM];
int history_2[FILTER2_TAP_NUM];
int history_3[FILTER3_TAP_NUM];
int history_4[FILTER4_TAP_NUM];

int y[500];

static void initHardware(void)
{
#if defined (__USE_LPCOPEN)
#if !defined(NO_BOARD_LIB)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "Off"
    Board_LED_Set(0, false);
#endif
#endif
   adcInit();
   dacInit();
}

int main(void)
{
	int i=0, offset;
	// fir_q31_init(&filtro, history_1, filter1_taps, FILTER1_TAP_NUM);
	// fir_q31_init(&filtro, history_2, filter2_taps, FILTER2_TAP_NUM);
	// fir_q31_init(&filtro, history_3, filter3_taps, FILTER3_TAP_NUM);
	// fir_q31_init(&filtro, history_4, filter4_taps, FILTER4_TAP_NUM);
	// fir_q31_init(&filtro, history_band, bandpass_taps, BANDPASS_TAP_NUM);
 	offset=512;//pasabanda
	// offset = -100; // o = 0 para pasa bajos

	initHardware();

	while(1)
	{
		if(adcFlag)
		{
			adcFlag=0;

			y[i] = fir_q31_get(&filtro)+offset;
			if(y[i]>0x3FF) y[i] = 0x3FF;
			else if(y[i]<0) y[i] = 0;
			dacWrite(y[i]);
			i++;
			if(i==500)
				i=0;
		}
	}
}
