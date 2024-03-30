/*
 * main.c
 *
 *  Created on: 2024Äê3ÔÂ24ÈÕ
 *      Author: SSC
 */

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "led.h"
#include "beep.h"

int main()
{
    InitSysCtrl();

    LED_Init();
    BEEP_Init();

    int i = 0;

    while(1)
    {
        i++;
        BEEP_TOGGLE;
        if(i%1000==0)
        {
            LED1_TOGGLE;
        }
        DELAY_US(100);
    }
}
