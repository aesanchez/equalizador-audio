#include "sapi.h"
#include "ui.h"
#include "equalizer.h"

int main(void)
{
	boardConfig();
	
	equalizer_init();	
	ui_init();

	delay_t ui_delay;
	delayConfig(&ui_delay, 50);

	while (1)
	{
		equalizer_loop();
		if (delayRead(&ui_delay))
			ui_loop();
	}
	return 0;
}