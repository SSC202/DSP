#ifndef __SMG_H
#define __SMG_H

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

//数码管位选信号线管脚定义
#define SEG1_SETH (GpioDataRegs.GPCSET.bit.GPIO70=1)
#define SEG1_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO70=1)
#define SEG2_SETH (GpioDataRegs.GPCSET.bit.GPIO71=1)
#define SEG2_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO71=1)
#define SEG3_SETH (GpioDataRegs.GPCSET.bit.GPIO72=1)
#define SEG3_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO72=1)
#define SEG4_SETH (GpioDataRegs.GPCSET.bit.GPIO73=1)
#define SEG4_SETL (GpioDataRegs.GPCCLEAR.bit.GPIO73=1)

//74HC164 时钟管脚定义
#define SPICLKA_SETH (GpioDataRegs.GPBSET.bit.GPIO56=1)
#define SPICLKA_SETL (GpioDataRegs.GPBCLEAR.bit.GPIO56=1)

//74HC164 数据管脚定义
#define SPISIMOA_SETH (GpioDataRegs.GPBSET.bit.GPIO54=1)
#define SPISIMOA_SETL (GpioDataRegs.GPBCLEAR.bit.GPIO54=1)

void SMG_Init(void);
void SMG_DisplayInt(Uint16 num);
void SMG_DisplayFloat(float num,unsigned char dotnum);

#endif
