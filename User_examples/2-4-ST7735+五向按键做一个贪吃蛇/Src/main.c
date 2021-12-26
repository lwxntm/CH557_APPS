#include "CH557X.H"
#include "../Inc/TYPEDEF.h"
#include "debug.h"
#include "../Inc/Gluttonous_Snake.h"
#define USE_LANDSCAPE
void main()
{
    CfgFsys();
    GameInit();

    while (1)
    {
        GameOp();
        mDelaymS(100);
    }
}