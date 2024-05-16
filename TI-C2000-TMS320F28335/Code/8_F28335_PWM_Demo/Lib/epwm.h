#ifndef __EPWM_H
#define __EPWM_H

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

void EPWM6_Init(Uint16 tbprd);
void EPwm6A_SetCompare(Uint16 val);
void EPwm6B_SetCompare(Uint16 val);

#endif
