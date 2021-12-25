#include "CH557X.H"
#include "../Inc/TYPEDEF.h"
#include "stdio.h"
#include "debug.h"
#include "../Inc/ST7735s.h"
void main()
{
    CfgFsys();
    lcd_initial();
    while (1)
    {
        dsp_single_colour(YELLOW);
        dsp_single_colour(RED);   //红色
        dsp_single_colour(GREEN); //绿色
        dsp_single_colour(BLUE);  //蓝色
        dsp_single_colour(WHITE); //白色
        Display_Desc();           //版本
        mDelaymS(5000);
    }
}