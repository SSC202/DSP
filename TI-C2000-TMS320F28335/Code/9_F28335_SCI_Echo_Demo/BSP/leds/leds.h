/*
 * led.h
 *
 *  Created on: 2018-1-20
 *      Author: Administrator
 */

#ifndef _LEDS_H_
#define _LEDS_H_

#include "DSP2833x_Device.h"     // DSP2833x 头文件
#include "DSP2833x_Examples.h"   // DSP2833x 例子相关头文件


#define LED1_ON			(GpioDataRegs.GPCSET.bit.GPIO68=1)
#define LED1_OFF		(GpioDataRegs.GPCCLEAR.bit.GPIO68=1)
#define LED1_TOGGLE		(GpioDataRegs.GPCTOGGLE.bit.GPIO68=1)

#define LED2_ON			(GpioDataRegs.GPCSET.bit.GPIO67=1)
#define LED2_OFF		(GpioDataRegs.GPCCLEAR.bit.GPIO67=1)
#define LED2_TOGGLE		(GpioDataRegs.GPCTOGGLE.bit.GPIO67=1)

#define LED3_ON			(GpioDataRegs.GPCSET.bit.GPIO66=1)
#define LED3_OFF		(GpioDataRegs.GPCCLEAR.bit.GPIO66=1)
#define LED3_TOGGLE		(GpioDataRegs.GPCTOGGLE.bit.GPIO66=1)

#define LED4_ON			(GpioDataRegs.GPCSET.bit.GPIO65=1)
#define LED4_OFF		(GpioDataRegs.GPCCLEAR.bit.GPIO65=1)
#define LED4_TOGGLE		(GpioDataRegs.GPCTOGGLE.bit.GPIO65=1)

#define LED5_ON			(GpioDataRegs.GPCSET.bit.GPIO64=1)
#define LED5_OFF		(GpioDataRegs.GPCCLEAR.bit.GPIO64=1)
#define LED5_TOGGLE		(GpioDataRegs.GPCTOGGLE.bit.GPIO64=1)

#define LED6_ON			(GpioDataRegs.GPASET.bit.GPIO10=1)
#define LED6_OFF		(GpioDataRegs.GPACLEAR.bit.GPIO10=1)
#define LED6_TOGGLE		(GpioDataRegs.GPATOGGLE.bit.GPIO10=1)

#define LED7_ON			(GpioDataRegs.GPASET.bit.GPIO11=1)
#define LED7_OFF		(GpioDataRegs.GPACLEAR.bit.GPIO11=1)
#define LED7_TOGGLE		(GpioDataRegs.GPATOGGLE.bit.GPIO11=1)


void LED_Init(void);


#endif /* LED_H_ */
