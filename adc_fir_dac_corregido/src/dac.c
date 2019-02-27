#include "board.h"

void dacInit(void)
{
	Chip_DAC_Init(LPC_DAC);
#ifdef lpc4337_m4
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DMA_ENA);
#endif
}

void dacWrite(uint32_t v)
{
	Chip_DAC_UpdateValue(LPC_DAC, v);
}
