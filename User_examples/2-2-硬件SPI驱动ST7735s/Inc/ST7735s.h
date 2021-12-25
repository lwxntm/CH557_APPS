#ifndef __ST7735S_H__
#define __ST7735S_H__

void lcd_initial();
void dsp_single_colour(unsigned int color);
void Display_Desc();

//定义常用颜色
#define RED 0xf800
#define GREEN 0x07e0
#define BLUE 0x001f
#define WHITE 0xffff
#define BLACK 0x0000
#define YELLOW 0xFFE0
#define GRAY0 0xEF7D
#define GRAY1 0x8410
#define GRAY2 0x4208

#endif