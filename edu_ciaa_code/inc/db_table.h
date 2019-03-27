#ifndef _MY_LCD_H_
#define _MY_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TABLE_SIZE 12
const float db_table[TABLE_SIZE] = {
    1,          // 0dB
    0.7943,     // -2dB
    0.6310,     // -4dB
    0.5012,     // -6dB
    0.3981,     // -8dB
    0.3162,     // -10dB
    0.2512,     // -12dB
    0.1995,     // -14dB
    0.1585,     // -16dB
    0.1259,     // -18dB
    0.1000,     // -20dB
    0           // -∞ dB
};

#ifdef __cplusplus
}
#endif

#endif