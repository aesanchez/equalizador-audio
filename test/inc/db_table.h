#ifndef _MY_LCD_H_
#define _MY_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TABLE_SIZE 11
const float db_table[TABLE_SIZE] = {
    1,
    0.7943,
    0.6310,
    0.5012,
    0.3981,
    0.3162,
    0.2512,
    0.1995,
    0.1585,
    0.1259,
    0.1000
};

#ifdef __cplusplus
}
#endif

#endif