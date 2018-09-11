#ifndef _CLOCK_H_
#define _CLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IGNORE_HH 24
#define IGNORE_MM 60
#define IGNORE_SS 60

void clock_tick(void);
void clock_get_time_as_str(char []);
void clock_set_time(char,char,char);

#ifdef __cplusplus
}
#endif

#endif 
