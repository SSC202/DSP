/*
 * main.c
 *
 *  Created on: 2024Äê3ÔÂ24ÈÕ
 *      Author: SSC
 */

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "led.h"
#include "key.h"
#include "smg.h"
#include "adc.h"

int main()
{
    float adc_vol;
    static int i = 0;

    InitSysCtrl();

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    LED_Init();
    SMG_Init();
    ADC_Init();

    while(1)
    {
        i++;
        adc_vol = (float)Read_ADCValue() * 3.0 / 4095;
        SMG_DisplayFloat(adc_vol, 2);
        if(i == 1000)
        {
            i = 0;
            LED1_TOGGLE;
        }
        DELAY_US(1000);
    }
}
