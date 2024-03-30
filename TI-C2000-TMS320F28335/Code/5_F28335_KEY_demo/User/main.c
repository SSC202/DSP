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
#include "key.h"

int main()
{
    InitSysCtrl();

    LED_Init();
    BEEP_Init();
    KEY_Init();

    int key = 0;
    int i = 0;

    while(1)
    {
        key = KEY_Scan(0);
        switch(key)
        {
            case KEY1_PRESS: LED2_TOGGLE;break;
            case KEY2_PRESS: LED3_TOGGLE;break;
            case KEY3_PRESS: LED4_TOGGLE;break;
            case KEY4_PRESS: LED5_TOGGLE;break;
            case KEY5_PRESS: LED6_TOGGLE;break;
            case KEY6_PRESS: LED7_TOGGLE;break;
            default:break;
        }
        i++;
        if(i%2000==0)
        {
            BEEP_TOGGLE;
        }
        DELAY_US(100);
    }
}
