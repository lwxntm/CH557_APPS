//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：WCH-CH557
//0.9寸TFT_ST7735液晶
//********************************************************************************
#include <stdio.h>
#include <string.h>
#include "CH557X.H"
#include "../Inc/ST7735s.h"
#include "../Inc/TYPEDEF.h"
#include "../Inc/st7735s_gui.h"

/*
  160*80 4像素一格 总共 40*20 , 800个坐标
*/

enum DIR
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

typedef struct
{
  uint8_t xloc;
  uint8_t yloc;
} vector2;

typedef struct
{
  vector2 body[50];
  uint8_t direction;
};

void GameInit()
{
  LCD_Init();
  LCD_Fill(0, 0, 159, 79, BLACK);
  LCD_Fill(0, 0, 159, 3, LGRAY);
  LCD_Fill(0, 0, 3, 79, LGRAY);
  LCD_Fill(0, 75, 159, 79, LGRAY);
  LCD_Fill(155, 0, 159, 79, LGRAY);

  LCD_Fill(32, 16, 64, 20, RED);
  //  lcd_initial();
  //   dsp_single_colour(0xffff);
  //  Display_Desc();
}

void GameOp()
{
}