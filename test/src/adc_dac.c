#include "adc_dac.h"
#include "sapi.h"
#include "menu.h"

uint16_t muestra = 0;
uint16_t status = 0;

void adc_dac_init(void)
{
	adcConfig(ADC_ENABLE); /* ADC */
	dacConfig(DAC_ENABLE); /* DAC */
}

void adc_dac_loop(void)
{
	muestra = adcRead(CH1);
	/*
    del adc leo aprox 0.5 - 3.3 Volts
    por lo tanto de 155 - 1023
    si quiero expandirlo a todo el rango
    muestra - 155 >>> de 0 a 868
    (muestra - 155) * 1.178571 >>> de 0 a 1023
    */
   	//muestra = (uint16_t)((muestra - 155) * 1.178571);
	dacWrite(DAC, muestra);

	//debug
	if (status)
		gpioWrite(T_COL0, ON);
	else
		gpioWrite(T_COL0, OFF);
	status = (status + 1) % 2;
}