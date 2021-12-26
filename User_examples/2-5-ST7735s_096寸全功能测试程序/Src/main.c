#include "CH557X.H"
#include "../Inc/TYPEDEF.h"
#include "stdio.h"
#include "debug.h"
#include "../Inc/ST7735s.h"
#include "../Inc/ST7735s_test.h"
#include "../Inc/st7735s_gui.h"
//#include "../Inc/Gluttonous_Snake.h"
#define USE_LANDSCAPE
void main()
{
    CfgFsys();
    // GameInit();
    LCD_Init();
    while (1)
    {
        LCD_Fill(0,0,159,79,YELLOW);
        mDelaymS(1000);
        LCD_Fill(0,0,159,79,RED);
        mDelaymS(1000);
        // LCD_Clear(YELLOW);
        //  mDelaymS(1000);
        //LCD_Clear(RED);
        // mDelaymS(1000);


       // Test_FillRec();      //GUI矩形绘图测试
    }
}