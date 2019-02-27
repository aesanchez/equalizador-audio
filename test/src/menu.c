#include "menu.h"
#include "sapi.h"
#include "db_table.h"
#define MENU_SIZE 5
char current_option = 0;
char previous_key_pressed = 0;

const char *menu[MENU_SIZE] = {
	"Banda 1",
	"Banda 2",
	"Banda 3",
	"Banda 4",
	"Reset"};
char level[4] = {0, 0, 0, 0};
char str[3];

void menu_init(void)
{
	gpioConfig(TEC_UP, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_RIGHT, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_OK, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_DOWN, GPIO_INPUT_PULLUP);
	gpioConfig(TEC_LEFT, GPIO_INPUT_PULLUP);
	menu_print();
}

void menu_print(void)
{
	lcdClear();
	lcdSendStringRaw(">>");
	lcdSendStringRaw(menu[current_option]);
	if (current_option != MENU_SIZE - 1)
	{
		if(level[current_option]!= 0) lcdSendStringRaw(" -");
		else lcdSendStringRaw(" ");
		str[0] = level[current_option] / 10 + '0';
		str[1] = level[current_option] % 10 + '0';
		str[2] = '\0';
		lcdSendStringRaw(str);
		lcdSendStringRaw(" dB");
	}
	lcdGoToXY(1, 2);
	lcdSendStringRaw(menu[(current_option + 1) % MENU_SIZE]);
}

void menu_loop(void)
{
	if (!gpioRead(TEC_UP))
		previous_key_pressed = 1;
	else
	{
		//no es apretada
		//se solto?
		if (previous_key_pressed == 1)
		{
			menu_move_up();
			menu_print();
			previous_key_pressed = 0;
		}
	}
	if (!gpioRead(TEC_DOWN))
		previous_key_pressed = 2;
	else
	{
		//no es apretada
		//se solto?
		if (previous_key_pressed == 2)
		{
			menu_move_down();
			menu_print();
			previous_key_pressed = 0;
		}
	}
	if (!gpioRead(TEC_LEFT))
		previous_key_pressed = 3;
	else
	{
		//no es apretada
		//se solto?
		if (previous_key_pressed == 3)
		{
			if (current_option != MENU_SIZE - 1)
			{
				if (level[current_option] != 0)
					level[current_option]-=2;
				menu_print();
			}
			previous_key_pressed = 0;
		}
	}
	if (!gpioRead(TEC_RIGHT))
		previous_key_pressed = 4;
	else
	{
		//no es apretada
		//se solto?
		if (previous_key_pressed == 4)
		{
			if (current_option != MENU_SIZE - 1)
			{
				if (level[current_option] != 20)
					level[current_option]+=2;
				menu_print();
			}
			previous_key_pressed = 0;
		}
	}
	if (!gpioRead(TEC_OK))
		previous_key_pressed = 5;
	else
	{
		//no es apretada
		//se solto?
		if (previous_key_pressed == 5)
		{
			if (current_option == MENU_SIZE - 1)
			{
				level[0] = 0;
				level[1] = 0;
				level[2] = 0;
				level[3] = 0;
			}
			menu_print();
			previous_key_pressed = 0;
		}
	}
}

void menu_move_up(void)
{
	if (current_option == 0)
		current_option = MENU_SIZE - 1;
	else
		current_option -= 1;
}
void menu_move_down(void)
{
	if (current_option == MENU_SIZE - 1)
		current_option = 0;
	else
		current_option += 1;
}

float menu_get_level(void){
	return db_table[level[0]/2];
}