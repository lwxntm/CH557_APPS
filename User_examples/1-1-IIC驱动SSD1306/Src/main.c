#include "CH557X.H"
#include "../Inc/SSD1306.h"
#include "stdio.h"
#include "debug.h"
void main()
{
    CfgFsys();
    uint8_t buf[5];
    uint16_t i = 0;
    OLED_Init();
    OLED_ShowString(2, 1, "Hello, CH557+++");
    while (1)
    {
        mDelaymS(1000);
        sprintf(buf, "%d", i++);
        OLED_ShowString(3, 1, buf);
    }
}