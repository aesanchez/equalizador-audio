#include "menu.h"
#include "sapi.h"
#include "db_table.h"

#define TEC_UP GPIO8
#define TEC_RIGHT GPIO7
#define TEC_OK GPIO5
#define TEC_DOWN GPIO3
#define TEC_LEFT GPIO1
#define NO_KEY 0

#define MENU_SIZE 5
#define RESET_OPTION (MENU_SIZE - 1)

void menu_start(void);
void menu_print(void);
void menu_loop(void);
void menu_scroll_up(void);
void menu_scroll_down(void);
float menu_get_level(int);

char current_option = 0;
char previous_key_pressed = NO_KEY;

const char *menu[MENU_SIZE] = {
	"Banda 1",
	"Banda 2",
	"Banda 3",
	"Banda 4",
	"Reset"};

char band_levels[4] = {0, 0, 0, 0};
char str[3];

void menu_start()
{
	gpioConfig(TEC_UP, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_RIGHT, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_OK, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_DOWN, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_LEFT, GPIO_INPUT_PULLUP);
	menu_print();
}

void menu_print()
{
	lcdClear();
	lcdSendStringRaw(">>");
	lcdSendStringRaw(menu[current_option]);
	if (current_option != RESET_OPTION)
	{
		if (band_levels[current_option] == 22)
		{
			lcdSendStringRaw(" OFF");
		}
		else
		{
			if (band_levels[current_option] != 0)
				lcdSendStringRaw(" -");
			else
				lcdSendStringRaw(" ");
			str[0] = band_levels[current_option] / 10 + '0';
			str[1] = band_levels[current_option] % 10 + '0';
			str[2] = '\0';
			lcdSendStringRaw(str);
			lcdSendStringRaw(" dB");
		}
	}
	lcdGoToXY(1, 2);
	lcdSendStringRaw(menu[(current_option + 1) % MENU_SIZE]);
}

void menu_loop()
{
	if (!gpioRead(TEC_UP))
		previous_key_pressed = TEC_UP;
	else if (previous_key_pressed == TEC_UP)
	{
		menu_scroll_up();
		menu_print();
		previous_key_pressed = NO_KEY;
	}

	if (!gpioRead(TEC_DOWN))
		previous_key_pressed = TEC_DOWN;
	else if (previous_key_pressed == TEC_DOWN)
	{
		menu_scroll_down();
		menu_print();
		previous_key_pressed = NO_KEY;
	}

	if (!gpioRead(TEC_LEFT))
		previous_key_pressed = TEC_LEFT;
	else if (previous_key_pressed == TEC_LEFT)
	{
		if (current_option != RESET_OPTION)
		{
			if (band_levels[current_option] != 0)
				band_levels[current_option] -= 2;
			menu_print();
		}
		previous_key_pressed = NO_KEY;
	}

	if (!gpioRead(TEC_RIGHT))
		previous_key_pressed = TEC_RIGHT;
	else if (previous_key_pressed == TEC_RIGHT)
	{
		if (current_option != RESET_OPTION)
		{
			if (band_levels[current_option] != 22)
				band_levels[current_option] += 2;
			menu_print();
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
		menu_print();
		previous_key_pressed = NO_KEY;
	}	
}

void menu_scroll_up()
{
	if (current_option == 0)
		current_option = MENU_SIZE;
	current_option--;
}
void menu_scroll_down()
{
	current_option = (current_option + 1) % MENU_SIZE;
}

float menu_get_level(int band)
{
	if (band < 0 || band > 3)
		return 0;
	return db_table[band_levels[band] / 2];
}