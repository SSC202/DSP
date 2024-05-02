#ifndef __ADC_H_
#define __ADC_H_

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#define ADC_MODCLK  3
#define ADC_CKPS    0x1                 // ADC module clock = HSPCLK/2*ADC_CKPS = 25.0MHz/(1*2) = 12.5MHz
#define ADC_SHCLK   0xf                 // S/H width in ADC module periods = 16 ADC clocks

void ADC_Init(void);
Uint16 Read_ADCValue(void);

#endif
