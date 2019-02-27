#include "sapi.h"
#include "sapi_timer.h"

uint32_t counter = 0;

#define STEPS_TOTAL 10
#define FREQUENCY 20000 //Hz
#define SIGNAL_REFRESH_FREQUENCY (FREQUENCY*STEPS_TOTAL)

uint16_t triangle_signal [STEPS_TOTAL] = {
	0,
	204,
	408,
	612,
	816,
	1023,
	816,
	612,
	408,
	204
};

uint16_t index = 0;

void * triangle_func(void){
	dacWrite(DAC, (int)(triangle_signal[index]));
	index = (index+1)%STEPS_TOTAL;
}

int main_gen(void)
{
	boardConfig();
	uartConfig(UART_USB, 115200);
	dacConfig(DAC_ENABLE); /* DAC */

	Timer_Init(0,(EDU_CIAA_NXP_CLOCK_SPEED/SIGNAL_REFRESH_FREQUENCY),triangle_func);
	/* loop */
	while (1)
	{
	}
	return 0;
}