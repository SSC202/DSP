/*
 * main.c
 *
 *  Created on: 2024Äê3ÔÂ24ÈÕ
 *      Author: SSC
 */

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "led.h"

void delay(void)
{
    Uint16 i;
    Uint32 j;
    for(i=0;i<32;i++)
        for (j=0;j<100000;j++);
}

int main()
{
    InitSysCtrl();

    LED_Init();

    while(1)
    {
        LED1_TOGGLE;
        delay();
    }
}
