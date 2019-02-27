#ifndef _MENU_H_
#define _MENU_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TEC_UP GPIO8
#define TEC_RIGHT GPIO7
#define TEC_OK GPIO5
#define TEC_DOWN GPIO3
#define TEC_LEFT GPIO1

void menu_init(void);
void menu_loop(void);
float menu_get_level(void);

#ifdef __cplusplus
}
#endif

#endif 
