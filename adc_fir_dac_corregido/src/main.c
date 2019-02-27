#include "adc.h"
#include "dac.h"
#include "filter1.h"
#include "filter2.h"
#include "filter3.h"
#include "filter4.h"
#include "fir_q31.h"

#define USAR_FUNCIONES_ASSEMBLER	1

//debug con TEC
#define T_COL0_P 1
#define T_COL0_P_ 5
#define T_COL0_GPIO 1
#define T_COL0_PIN 8
uint32_t pinStatus = 0;

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

static void initHardware(void)
{
#if defined(__USE_LPCOPEN)
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
	//Init debug con T_COL0
	Chip_GPIO_Init(LPC_GPIO_PORT);
	Chip_SCU_PinMux(T_COL0_P, T_COL0_P_, MD_PUP, FUNC0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, T_COL0_GPIO, (1 << T_COL0_PIN), 1);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, T_COL0_GPIO, (1 << T_COL0_PIN));

	fir_q31_init(&filtro1, history_1, filter1_taps, FILTER1_TAP_NUM);
	fir_q31_init(&filtro2, history_2, filter2_taps, FILTER2_TAP_NUM);
	fir_q31_init(&filtro3, history_3, filter3_taps, FILTER3_TAP_NUM);
	fir_q31_init(&filtro4, history_4, filter4_taps, FILTER4_TAP_NUM);

	initHardware();

	while (1)
	{
		if (adcFlag)
		{
			adcFlag = 0;
#if(USAR_FUNCIONES_ASSEMBLER)			
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
			y = (y1 + y2 + y3 + y4) + 512;
			if (y > 1023)
				y = 1023;
			else if (y < 0)
				y = 0;

			dacWrite(y);
			
			//debug frecuencia de muestreo
			//Si tenemos frecuencia de muestreo 44000 el osciloscopio debe mostrar una frecuencia de 22000
			if (pinStatus)
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, T_COL0_GPIO, T_COL0_PIN, 0);
			else
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, T_COL0_GPIO, T_COL0_PIN, 1);
			pinStatus = (pinStatus + 1) % 2;
		}
	}
}
