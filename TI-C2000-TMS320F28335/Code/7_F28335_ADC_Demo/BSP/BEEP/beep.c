#include "beep.h"

void BEEP_Init(void)
{
    EALLOW;

    //BEEP ∂Àø⁄≈‰÷√
    GpioCtrlRegs.GPAMUX1.bit.GPIO6=0;
    GpioCtrlRegs.GPADIR.bit.GPIO6=1;
    GpioCtrlRegs.GPAPUD.bit.GPIO6=0;

    EDIS;

    GpioDataRegs.GPACLEAR.bit.GPIO6=1;
}
