#include "menu.h"
#include "sapi.h"
#include "db_table.h"

#define TEC_UP GPIO8
#define TEC_RIGHT GPIO7
#define TEC_OK GPIO5
#define TEC_DOWN GPIO3
#define TEC_LEFT GPIO1

#define MENU_SIZE 5

void menu_start(void);
void menu_print(void);
void menu_loop(void);
void menu_scroll_up(void);
void menu_scroll_down(void);
float menu_get_level(int);

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
	if (current_option != MENU_SIZE - 1)
	{
		if(level[current_option] == 22){
			lcdSendStringRaw(" OFF");
		}else{
			if(level[current_option]!= 0) lcdSendStringRaw(" -");
			else lcdSendStringRaw(" ");
			str[0] = level[current_option] / 10 + '0';
			str[1] = level[current_option] % 10 + '0';
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
		previous_key_pressed = 1;
	else
	{
		if (previous_key_pressed == 1)
		{
			menu_scroll_up();
			menu_print();
			previous_key_pressed = 0;
		}
	}
	if (!gpioRead(TEC_DOWN))
		previous_key_pressed = 2;
	else
	{
		if (previous_key_pressed == 2)
		{
			menu_scroll_down();
			menu_print();
			previous_key_pressed = 0;
		}
	}
	if (!gpioRead(TEC_LEFT))
		previous_key_pressed = 3;
	else
	{
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
		if (previous_key_pressed == 4)
		{
			if (current_option != MENU_SIZE - 1)
			{
				if (level[current_option] != 22)
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

void menu_scroll_up()
{
	if (current_option == 0)
		current_option = MENU_SIZE - 1;
	else
		current_option -= 1;
}
void menu_scroll_down()
{
	if (current_option == MENU_SIZE - 1)
		current_option = 0;
	else
		current_option += 1;
}

float menu_get_level(int band){
	if(band < 0 || band > 3) return 0;
	return db_table[level[band]/2];
}