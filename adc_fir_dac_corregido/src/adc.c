#include "board.h"
#include "fir_q31.h"
#include "main.h"

//debug con TEC
#define T_COL0_P 1
#define T_COL0_P_ 5
#define T_COL0_GPIO 1
#define T_COL0_PIN 8
uint32_t pinStatus = 0;

int adcFlag = 0;

#define LPC_ADC LPC_ADC0
#define ADC_IRQn ADC0_IRQn


/************ TIMER setup ************/
#define FRECUENCIA_MUESTREO 44000
#define TICKRATE_HZ (FRECUENCIA_MUESTREO * 2)

#define LPC_TIMER LPC_TIMER3
#define NVIC_TIMER_IRQ TIMER3_IRQn
#define TIMER_IRQHandler void TIMER3_IRQHandler(void)

#define CHIP_RGU_TIMER_RST RGU_TIMER3_RST
#define CHIP_CLK_TIMER CLK_MX_TIMER3

#define LPC_TIMER_MATCH_INT_NUM 3

void TIMER_setup()
{

    Chip_TIMER_Init(LPC_TIMER);

    Chip_RGU_TriggerReset(CHIP_RGU_TIMER_RST);

    while (Chip_RGU_InReset(CHIP_RGU_TIMER_RST))
    {
    }

    uint32_t timerFreq = Chip_Clock_GetRate(CHIP_CLK_TIMER);

    Chip_TIMER_Reset(LPC_TIMER);
    Chip_TIMER_MatchEnableInt(LPC_TIMER, LPC_TIMER_MATCH_INT_NUM);
    Chip_TIMER_SetMatch(LPC_TIMER, LPC_TIMER_MATCH_INT_NUM, (timerFreq / TICKRATE_HZ));
    Chip_TIMER_ResetOnMatchEnable(LPC_TIMER, LPC_TIMER_MATCH_INT_NUM);
    Chip_TIMER_ExtMatchControlSet(LPC_TIMER, 1, TIMER_EXTMATCH_TOGGLE, LPC_TIMER_MATCH_INT_NUM);
    Chip_TIMER_Enable(LPC_TIMER);

    LPC_GIMA->ADCSTART0_IN = 0x4;
}
TIMER_IRQHandler
{

    if (Chip_TIMER_MatchPending(LPC_TIMER, LPC_TIMER_MATCH_INT_NUM))
    {
        Chip_TIMER_ClearMatch(LPC_TIMER, LPC_TIMER_MATCH_INT_NUM);
    }
}

/************ ADC setup ************/
void adcInit(void)
{

    TIMER_setup();

    Chip_SCU_ADC_Channel_Config(0, ADC_CH1);

    static ADC_CLOCK_SETUP_T ADCSetup;

    Chip_ADC_Init(LPC_ADC0, &ADCSetup);
    Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
    Chip_ADC_SetSampleRate(LPC_ADC0, &ADCSetup, ADC_MAX_SAMPLE_RATE);
    Chip_ADC_SetResolution(LPC_ADC0, &ADCSetup, ADC_10BITS);
    Chip_ADC_SetBurstCmd(LPC_ADC0, DISABLE);
    Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH1, ENABLE);
    Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_ON_CTOUT15, ADC_TRIGGERMODE_RISING);

    NVIC_EnableIRQ(ADC0_IRQn);
    NVIC_ClearPendingIRQ(ADC0_IRQn);

    //NVIC_EnableIRQ(NVIC_TIMER_IRQ);
    //NVIC_ClearPendingIRQ(NVIC_TIMER_IRQ);

    //Init debug con T_COL0
    Chip_GPIO_Init(LPC_GPIO_PORT);
    Chip_SCU_PinMux(T_COL0_P, T_COL0_P_, MD_PUP, FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, T_COL0_GPIO, (1 << T_COL0_PIN), 1);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, T_COL0_GPIO, (1 << T_COL0_PIN));
}

void ADC0_IRQHandler(void)
{
    static uint16_t data;
    Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, &data); //leer el resultado borra el flag de int
    fir_q31_put(&filtro, data);

    //debug frecuencia de muestreo
    //Si tenemos frecuencia de muestreo 44000 el osciloscopio debe mostrar una frecuencia de 22000
    if (pinStatus)
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, T_COL0_GPIO, T_COL0_PIN, 0);
    else
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, T_COL0_GPIO, T_COL0_PIN, 1);
    pinStatus = (pinStatus+1) % 2;

    adcFlag = 1;
}
