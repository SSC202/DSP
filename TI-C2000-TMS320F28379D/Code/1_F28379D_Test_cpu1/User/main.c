#include "F28x_Project.h"

void main(void)
{
    uint32_t delay = 0;
    InitSysCtrl();

    // Set pin direction
    GPIO_SetupPinOptions(35, GPIO_OUTPUT, GPIO_PUSHPULL);
    while(1)
    {
        delay++;
        if (delay > 2000000)
            delay = 0;
        if (delay > 1000000)
            GPIO_WritePin(35, 1);
        if (delay < 1000000)
            GPIO_WritePin(35, 0);
    }
}
