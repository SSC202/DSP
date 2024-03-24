/*
 * main.c
 *
 *  Created on: 2024Äê3ÔÂ24ÈÕ
 *      Author: SSC
 */

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

void delay(void)
{
    Uint16 i;
    Uint32 j;
    for(i=0;i<32;i++)
        for (j=0;j<100000;j++);
}

void LED_Init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;

    //LED Init
    GpioCtrlRegs.GPCMUX1.bit.GPIO66=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO66=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO66=0;
    GpioDataRegs.GPCSET.bit.GPIO66=1;
    EDIS;
}

int main()
{
    InitSysCtrl();

    LED_Init();

    while(1)
    {
        GpioDataRegs.GPCTOGGLE.bit.GPIO66=1;
        delay();
    }
}
