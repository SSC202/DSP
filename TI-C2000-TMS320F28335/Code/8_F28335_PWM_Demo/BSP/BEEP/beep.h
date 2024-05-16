#ifndef __BEEP_H
#define __BEEP_H

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#define BEEP_ON (GpioDataRegs.GPASET.bit.GPIO6=1)
#define BEEP_OFF (GpioDataRegs.GPACLEAR.bit.GPIO6=1)
#define BEEP_TOGGLE (GpioDataRegs.GPATOGGLE.bit.GPIO6=1)

void BEEP_Init(void);

#endif
