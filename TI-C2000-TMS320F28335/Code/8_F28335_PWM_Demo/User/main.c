/*
 * main.c
 *
 *  Created on: 2024Äê3ÔÂ24ÈÕ
 *      Author: SSC
 */

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "led.h"
#include "epwm.h"

int main()
{
    int i = 0;
    unsigned char fx = 0;

    InitSysCtrl();

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    EPWM6_Init(500);

    while(1)
    {
        if(fx==0)
        {
            i++;
            if(i==300)
            {
                fx=1;
            }
        }
        else
        {
            i--;
            if(i==0)
            {
                fx=0;
            }
        }
        EPwm6A_SetCompare(i);
        EPwm6B_SetCompare(300-i);
        DELAY_US(10*1000);
    }
}
