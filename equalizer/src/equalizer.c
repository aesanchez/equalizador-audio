#include "sapi.h"
#include "sapi_timer.h"
#include "ui.h"
#include "filter1.h"
#include "filter2.h"
#include "filter3.h"
#include "filter4.h"
#include "fir_q31.h"
#include "db_table.h"

#define USAR_FUNCIONES_ASSEMBLER 1

fir_q31_t filtro1;
fir_q31_t filtro2;
fir_q31_t filtro3;
fir_q31_t filtro4;

int history_1[FILTER1_TAP_NUM];
int history_2[FILTER2_TAP_NUM];
int history_3[FILTER3_TAP_NUM];
int history_4[FILTER4_TAP_NUM];

int y;
int y1;
int y2;
int y3;
int y4;

uint16_t band_levels[4] = {0,0,0,0};

uint16_t adc_sample_flag = 0;
#define SAMPLING_FREQUENCY 44000
uint16_t analogValue = 0;

void equalizer_loop(void)
{
	if(adc_sample_flag==0) return;
	adc_sample_flag = 0;
	//flag cada 44khz
#if (USAR_FUNCIONES_ASSEMBLER)
	y1 = asm_fir_q31_get(&filtro1) - 512;
	y2 = asm_fir_q31_get(&filtro2);
	y3 = asm_fir_q31_get(&filtro3);
	y4 = asm_fir_q31_get(&filtro4);
#else
	y1 = fir_q31_get(&filtro1) - 512;
	y2 = fir_q31_get(&filtro2);
	y3 = fir_q31_get(&filtro3);
	y4 = fir_q31_get(&filtro4);
#endif
	y1 = (int)(y1 * db_table[band_levels[0]]);
	y2 = (int)(y2 * db_table[band_levels[1]]);
	y3 = (int)(y3 * db_table[band_levels[2]]);
	y4 = (int)(y4 * db_table[band_levels[3]]);
	y = (y1 + y2 + y3 + y4) + 512;
	if (y > 1023)
		y = 1023;
	else if (y < 0)
		y = 0;
	dacWrite(DAC, y);
	//debug para frecuencia de señal
	gpioToggle(T_COL0);
}

void *sampling_interrupt(void)
{
	//deberia preguntar 400khz y y estoy leyendo a 44khz
	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, &analogValue);
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //repetir conversion

#if(USAR_FUNCIONES_ASSEMBLER)
		asm_fir_q31_put(&filtro1, analogValue);
        asm_fir_q31_put(&filtro2, analogValue);
        asm_fir_q31_put(&filtro3, analogValue);
        asm_fir_q31_put(&filtro4, analogValue);
#else
        fir_q31_put(&filtro1, analogValue);	
        fir_q31_put(&filtro2, analogValue);
        fir_q31_put(&filtro3, analogValue);
        fir_q31_put(&filtro4, analogValue);
#endif

	adc_sample_flag=1;	
}

void equalizer_init(void)
{
	fir_q31_init(&filtro1, history_1, filter1_taps, FILTER1_TAP_NUM);
	fir_q31_init(&filtro2, history_2, filter2_taps, FILTER2_TAP_NUM);
	fir_q31_init(&filtro3, history_3, filter3_taps, FILTER3_TAP_NUM);
	fir_q31_init(&filtro4, history_4, filter4_taps, FILTER4_TAP_NUM);

	adcConfig(ADC_ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH1, ENABLE);
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //iniciar conversion

	dacConfig(DAC_ENABLE);

	Timer_Init(0, (EDU_CIAA_NXP_CLOCK_SPEED / SAMPLING_FREQUENCY), sampling_interrupt);
}