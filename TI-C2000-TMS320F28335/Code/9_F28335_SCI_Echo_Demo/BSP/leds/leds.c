/*
 * led.c
 *
 *  Created on: 2018-1-20
 *      Author: Administrator
 */
#include "leds.h"

/*******************************************************************************
* 函 数 名         : LED_Init
* 函数功能		   : LED初始化函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void LED_Init(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;// 开启GPIO时钟

	//LED1端口配置
	GpioCtrlRegs.GPCMUX1.bit.GPIO68=0;
	GpioCtrlRegs.GPCDIR.bit.GPIO68=1;
	GpioCtrlRegs.GPCPUD.bit.GPIO68=0;

	//LED2端口配置
	GpioCtrlRegs.GPCMUX1.bit.GPIO67=0;
	GpioCtrlRegs.GPCDIR.bit.GPIO67=1;
	GpioCtrlRegs.GPCPUD.bit.GPIO67=0;

	//LED3端口配置
	GpioCtrlRegs.GPCMUX1.bit.GPIO66=0;
	GpioCtrlRegs.GPCDIR.bit.GPIO66=1;
	GpioCtrlRegs.GPCPUD.bit.GPIO66=0;

	//LED4端口配置
	GpioCtrlRegs.GPCMUX1.bit.GPIO65=0;
	GpioCtrlRegs.GPCDIR.bit.GPIO65=1;
	GpioCtrlRegs.GPCPUD.bit.GPIO65=0;

	//LED5端口配置
	GpioCtrlRegs.GPCMUX1.bit.GPIO64=0;
	GpioCtrlRegs.GPCDIR.bit.GPIO64=1;
	GpioCtrlRegs.GPCPUD.bit.GPIO64=0;

	//LED6端口配置
	GpioCtrlRegs.GPAMUX1.bit.GPIO10=0;
	GpioCtrlRegs.GPADIR.bit.GPIO10=1;
	GpioCtrlRegs.GPAPUD.bit.GPIO10=0;

	//LED7端口配置
	GpioCtrlRegs.GPAMUX1.bit.GPIO11=0;
	GpioCtrlRegs.GPADIR.bit.GPIO11=1;
	GpioCtrlRegs.GPAPUD.bit.GPIO11=0;



	GpioDataRegs.GPCSET.bit.GPIO68=1;
	GpioDataRegs.GPCSET.bit.GPIO67=1;
	GpioDataRegs.GPCSET.bit.GPIO66=1;
	GpioDataRegs.GPCSET.bit.GPIO65=1;
	GpioDataRegs.GPCSET.bit.GPIO64=1;
	GpioDataRegs.GPASET.bit.GPIO10=1;
	GpioDataRegs.GPASET.bit.GPIO11=1;

	EDIS;
}
