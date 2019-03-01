#include "ui.h"
#include "my_lcd.h"
#include "sapi.h"
#include "equalizer.h"

#define TEC_UP GPIO8
#define TEC_RIGHT GPIO7
#define TEC_OK GPIO5
#define TEC_DOWN GPIO3
#define TEC_LEFT GPIO1
#define NO_KEY 0

#define MENU_SIZE 5
#define RESET_OPTION (MENU_SIZE - 1)

void ui_init(void);
void ui_print(void);
void ui_loop(void);
void ui_scroll_up(void);
void ui_scroll_down(void);

char current_option = 0;
char previous_key_pressed = NO_KEY;

const char * menu[MENU_SIZE] = {
	"Banda 1",
	"Banda 2",
	"Banda 3",
	"Banda 4",
	"Reset"};

char str[3];

void ui_init()
{
	my_lcd_init();
	gpioConfig(TEC_UP, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_RIGHT, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_OK, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_DOWN, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_LEFT, GPIO_INPUT_PULLUP);
	ui_print();
}

void ui_print()
{
	lcdClear();
	lcdSendStringRaw(">>");
	lcdSendStringRaw(menu[current_option]);
	if (current_option != RESET_OPTION)
	{
		if (band_levels[current_option] == 11)
		{
			lcdSendStringRaw(" OFF");
		}
		else
		{
			if (band_levels[current_option] != 0)
				lcdSendStringRaw(" -");
			else
				lcdSendStringRaw(" ");
			str[0] = (band_levels[current_option]*2) / 10 + '0';
			str[1] = (band_levels[current_option]*2) % 10 + '0';
			str[2] = '\0';
			lcdSendStringRaw(str);
			lcdSendStringRaw(" dB");
		}
	}
	lcdGoToXY(1, 2);
	lcdSendStringRaw(menu[(current_option + 1) % MENU_SIZE]);
}

void ui_loop()
{
	if (!gpioRead(TEC_UP))
		previous_key_pressed = TEC_UP;
	else if (previous_key_pressed == TEC_UP)
	{
		ui_scroll_up();
		ui_print();
		previous_key_pressed = NO_KEY;
	}

	if (!gpioRead(TEC_DOWN))
		previous_key_pressed = TEC_DOWN;
	else if (previous_key_pressed == TEC_DOWN)
	{
		ui_scroll_down();
		ui_print();
		previous_key_pressed = NO_KEY;
	}

	if (!gpioRead(TEC_LEFT))
		previous_key_pressed = TEC_LEFT;
	else if (previous_key_pressed == TEC_LEFT)
	{
		if (current_option != RESET_OPTION)
		{
			if (band_levels[current_option] != 0)
				band_levels[current_option]--;
			ui_print();
		}
		previous_key_pressed = NO_KEY;
	}

	if (!gpioRead(TEC_RIGHT))
		previous_key_pressed = TEC_RIGHT;
	else if (previous_key_pressed == TEC_RIGHT)
	{
		if (current_option != RESET_OPTION)
		{
			if (band_levels[current_option] != 11)
				band_levels[current_option]++;
			ui_print();
		}
		previous_key_pressed = NO_KEY;
	}

	if (!gpioRead(TEC_OK))
		previous_key_pressed = TEC_OK;
	else if (previous_key_pressed == TEC_OK)
	{
		if (current_option == RESET_OPTION)
		{
			band_levels[0] = 0;
			band_levels[1] = 0;
			band_levels[2] = 0;
			band_levels[3] = 0;
		}
		ui_print();
		previous_key_pressed = NO_KEY;
	}	
}

void ui_scroll_up()
{
	if (current_option == 0)
		current_option = MENU_SIZE;
	current_option--;
}
void ui_scroll_down()
{
	current_option = (current_option + 1) % MENU_SIZE;
}