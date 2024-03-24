#ifndef __LED_H
#define __LED_H

#include "DSP2833x_Device.h" // DSP2833x Í·ÎÄ¼þ
#include "DSP2833x_Examples.h"

#define LED1_OFF                (GpioDataRegs.GPCSET.bit.GPIO68=1)
#define LED1_ON                 (GpioDataRegs.GPCCLEAR.bit.GPIO68=1)
#define LED1_TOGGLE             (GpioDataRegs.GPCTOGGLE.bit.GPIO68=1)
#define LED2_OFF                (GpioDataRegs.GPCSET.bit.GPIO67=1)
#define LED2_ON                 (GpioDataRegs.GPCCLEAR.bit.GPIO67=1)
#define LED2_TOGGLE             (GpioDataRegs.GPCTOGGLE.bit.GPIO67=1)
#define LED3_OFF                (GpioDataRegs.GPCSET.bit.GPIO66=1)
#define LED3_ON                 (GpioDataRegs.GPCCLEAR.bit.GPIO66=1)
#define LED3_TOGGLE             (GpioDataRegs.GPCTOGGLE.bit.GPIO66=1)
#define LED4_OFF                (GpioDataRegs.GPCSET.bit.GPIO65=1)
#define LED4_ON                 (GpioDataRegs.GPCCLEAR.bit.GPIO65=1)
#define LED4_TOGGLE             (GpioDataRegs.GPCTOGGLE.bit.GPIO65=1)
#define LED5_OFF                (GpioDataRegs.GPCSET.bit.GPIO64=1)
#define LED5_ON                 (GpioDataRegs.GPCCLEAR.bit.GPIO64=1)
#define LED5_TOGGLE             (GpioDataRegs.GPCTOGGLE.bit.GPIO64=1)
#define LED6_OFF                (GpioDataRegs.GPASET.bit.GPIO10=1)
#define LED6_ON                 (GpioDataRegs.GPACLEAR.bit.GPIO10=1)
#define LED6_TOGGLE             (GpioDataRegs.GPATOGGLE.bit.GPIO10=1)
#define LED7_OFF                (GpioDataRegs.GPASET.bit.GPIO11=1)
#define LED7_ON                 (GpioDataRegs.GPACLEAR.bit.GPIO11=1)
#define LED7_TOGGLE             (GpioDataRegs.GPATOGGLE.bit.GPIO11=1)

void LED_Init(void);

#endif
