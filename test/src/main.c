#include "sapi.h"
#include "menu.h"
#include "my_lcd.h"
#include "adc_dac.h"

int main(void)
{
	boardConfig();

	adc_dac_init();
	my_lcd_init();
	menu_init();

	delay_t lcd_delay;
	delayConfig(&lcd_delay, 50);

	/* loop */
	while (1)
	{
		adc_dac_loop();	

		if (delayRead(&lcd_delay))
		{
			menu_loop();
		}
	}
	return 0;
}