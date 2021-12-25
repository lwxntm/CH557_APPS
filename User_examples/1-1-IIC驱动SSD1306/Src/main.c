#include "CH557X.H"
#include "../Inc/SSD1306.h"
#include "stdio.h"
void main()
{
    uint8_t buf[5];
    uint8_t i = 0;
    OLED_Init();
    OLED_ShowString(2, 1, "Hello, CH557+++");
    while (1)
    {
        sprintf(buf, "%d", i++);
        if (i == 0xff)
            i = 100;
        OLED_ShowString(3, 1, buf);
    }
}