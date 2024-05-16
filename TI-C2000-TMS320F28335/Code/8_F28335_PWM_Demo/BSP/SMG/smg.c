#include "smg.h"

unsigned char smgduan[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  //0~F 数码管段选数据

/**
 * @brief   数码管初始化函数
 */
void SMG_Init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;// 开启 GPIO 时钟
    //SMG 数据控制端口配置
    GpioCtrlRegs.GPBMUX2.bit.GPIO56=0;
    GpioCtrlRegs.GPBDIR.bit.GPIO56=1;
    GpioCtrlRegs.GPBPUD.bit.GPIO56=0;
    GpioCtrlRegs.GPBMUX2.bit.GPIO54=0;
    GpioCtrlRegs.GPBDIR.bit.GPIO54=1;
    GpioCtrlRegs.GPBPUD.bit.GPIO54=0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO70=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO70=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO70=0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO71=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO71=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO71=0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO72=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO72=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO72=0;
    GpioCtrlRegs.GPCMUX1.bit.GPIO73=0;
    GpioCtrlRegs.GPCDIR.bit.GPIO73=1;
    GpioCtrlRegs.GPCPUD.bit.GPIO73=0;
    EDIS;
    GpioDataRegs.GPCCLEAR.bit.GPIO70=1;
    GpioDataRegs.GPCCLEAR.bit.GPIO71=1;
    GpioDataRegs.GPCCLEAR.bit.GPIO72=1;
    GpioDataRegs.GPCCLEAR.bit.GPIO73=1;
}

/**
 * @brief   74HC164发送函数
 * @param   dat 显示的整数
 */
static void HC164SendData(unsigned char dat)
{
    char i=0;

    for(i=0;i<8;i++)
    {
        SPICLKA_SETL;
        if(dat&0x80)
            SPISIMOA_SETH;
        else
            SPISIMOA_SETL;
        SPICLKA_SETH;
        dat<<=1;
    }
}

/**
 * @brief   数码管显示整数函数
 * @param   num 显示的整数
 */
void SMG_DisplayInt(Uint16 num)
{
    unsigned char buf[4];
    unsigned char i=0;

    buf[0]=smgduan[num/1000];
    buf[1]=smgduan[num%1000/100];
    buf[2]=smgduan[num%1000%100/10];
    buf[3]=smgduan[num%1000%100%10];

    for(i=0;i<4;i++)
    {
        HC164SendData(buf[i]);
        switch(i)
        {
            case 0: SEG1_SETH;SEG2_SETL;SEG3_SETL;SEG4_SETL;break;
            case 1: SEG1_SETL;SEG2_SETH;SEG3_SETL;SEG4_SETL;break;
            case 2: SEG1_SETL;SEG2_SETL;SEG3_SETH;SEG4_SETL;break;
            case 3: SEG1_SETL;SEG2_SETL;SEG3_SETL;SEG4_SETH;break;
        }
        DELAY_US(5000);
    }
}

/**
 * @brief   数码管显示整数函数
 * @param   num     显示的小数
 * @param   dotnum  小数有效位数
 */
void SMG_DisplayFloat(float num,unsigned char dotnum)
{
    unsigned char buf[4];
    unsigned char i;
    Uint16 value=0;

    if(dotnum==1)
    {
        value=num*10;
        buf[0]=smgduan[value/1000];
        buf[1]=smgduan[value%1000/100];
        buf[2]=smgduan[value%1000%100/10]|0x80;
        buf[3]=smgduan[value%1000%100%10];
    }
    else if(dotnum==2)
    {
        value=num*100;
        buf[0]=smgduan[value/1000];
        buf[1]=smgduan[value%1000/100]|0x80;
        buf[2]=smgduan[value%1000%100/10];
        buf[3]=smgduan[value%1000%100%10];
    }
    else if(dotnum==3)
    {
        value=num*1000;
        buf[0]=smgduan[value/1000]|0x80;
        buf[1]=smgduan[value%1000/100];
        buf[2]=smgduan[value%1000%100/10];
        buf[3]=smgduan[value%1000%100%10];
    }

    for(i=0;i<4;i++)
    {
        HC164SendData(buf[i]);
        switch(i)
        {
            case 0: SEG1_SETH;SEG2_SETL;SEG3_SETL;SEG4_SETL;break;
            case 1: SEG1_SETL;SEG2_SETH;SEG3_SETL;SEG4_SETL;break;
            case 2: SEG1_SETL;SEG2_SETL;SEG3_SETH;SEG4_SETL;break;
            case 3: SEG1_SETL;SEG2_SETL;SEG3_SETL;SEG4_SETH;break;
        }
        DELAY_US(5000);
    }
}


