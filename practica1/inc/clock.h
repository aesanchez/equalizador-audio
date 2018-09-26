#ifndef _CLOCK_H_
#define _CLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

void clock_tick_sec(void);
void clock_tick_dsec(void);
void clock_get_time_as_str(char []);

#ifdef __cplusplus
}
#endif

#endif 
