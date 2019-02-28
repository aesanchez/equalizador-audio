#include "sapi.h"
#include "menu.h"
#include "my_lcd.h"
#include "signal.h"

int main(void)
{
	boardConfig();
	my_lcd_init();
	menu_start();
	signal_init();	

	delay_t lcd_delay;
	delayConfig(&lcd_delay, 50);

	while (1)
	{
		signal_loop();
		if (delayRead(&lcd_delay))
		{
			menu_loop();
		}
	}
	return 0;
}