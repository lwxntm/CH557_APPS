// Blink an LED connected to pin 1.7

#include <ch557x.h>
#include <debug.h>

#define LED_PIN 4
#define LED P4_4
void main()
{
    CfgFsys();

    // Configure pin 1.7 as GPIO output
    // P4_DIR_PU &= 0x0C;
    P4_MOD_OC &= ~(1 << LED_PIN);
    P4_DIR_PU |= (1 << LED_PIN);

    while (1)
    {

        LED = 1;
        mDelayuS(10);
        
        LED = 0;
        mDelayuS(10);
        LED = 1;
        mDelayuS(10);
        LED = 0;
        mDelayuS(10);
        LED = 1;
        mDelayuS(10);
        LED = 0;
        mDelayuS(10);
        LED = 1;
        mDelayuS(10);
        LED = 0;
        mDelayuS(10);
        LED = 1;
        mDelayuS(10);
        LED = 0;
        mDelayuS(10);
        LED = 1;
        mDelayuS(10);
        LED = 0;
        mDelayuS(10);
        LED = 1;
        mDelayuS(10);
        LED = 0;
        mDelayuS(10);
    }
}
