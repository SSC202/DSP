#include "led.h"

/**
 * @brief   LED初始化函数
 */
void LED_Init(void)
{
    EALLOW;

    //LED1 端口配置
    GpioCtrlRegs.GPCMUX1.bit.GPIO68=0;  // 设置为GPIO输出功能
    GpioCtrlRegs.GPCDIR.bit.GPIO68=1;   // 设置为输出方向
    GpioCtrlRegs.GPCPUD.bit.GPIO68=0;   // 允许上拉

    //LED2 端口配置
    GpioCtrlRegs.GPCMUX1.bit.GPIO67=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO67=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO67=0;

    //LED3 端口配置
    GpioCtrlRegs.GPCMUX1.bit.GPIO66=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO66=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO66=0;

    //LED4 端口配置
    GpioCtrlRegs.GPCMUX1.bit.GPIO65=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO65=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO65=0;

    //LED5 端口配置
    GpioCtrlRegs.GPCMUX1.bit.GPIO64=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO64=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO64=0;

    //LED6 端口配置
    GpioCtrlRegs.GPAMUX1.bit.GPIO10=0;
    GpioCtrlRegs.GPADIR.bit.GPIO10=1;
    GpioCtrlRegs.GPAPUD.bit.GPIO10=0;

    //LED7 端口配置
    GpioCtrlRegs.GPAMUX1.bit.GPIO11=0;
    GpioCtrlRegs.GPADIR.bit.GPIO11=1;
    GpioCtrlRegs.GPAPUD.bit.GPIO11=0;
    GpioDataRegs.GPCSET.bit.GPIO68=1;

    //设置为低电平
    GpioDataRegs.GPCSET.bit.GPIO67=1;
    GpioDataRegs.GPCSET.bit.GPIO66=1;
    GpioDataRegs.GPCSET.bit.GPIO65=1;
    GpioDataRegs.GPCSET.bit.GPIO64=1;
    GpioDataRegs.GPASET.bit.GPIO10=1;
    GpioDataRegs.GPASET.bit.GPIO11=1;

    EDIS;

}
