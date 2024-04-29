/*
 * main.c
 *
 *  Created on: 2024��3��24��
 *      Author: SSC
 */

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "led.h"
#include "key.h"

/**
 * @brief   �жϷ�����
 */
interrupt void EXTI1_IRQn(void)
{
    Uint32 i;
    for(i=0;i<10000;i++); //����������
    while(!KEY_H1);
    LED2_TOGGLE;

    // ����PIEACK�Ĵ���
    PieCtrlRegs.PIEACK.bit.ACK1=1;
}

interrupt void EXTI2_IRQn(void)
{
    Uint32 i;
    for(i=0;i<10000;i++);    //����������
    while(!KEY_H2);
    LED3_TOGGLE;
    PieCtrlRegs.PIEACK.bit.ACK1=1;
}


/**
 * @brief    ���ż��жϳ�ʼ������
 */
void EXTI1_Init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1; // GPIO input clock
    EDIS;

    //KEY �˿�����
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO12=0;
    GpioCtrlRegs.GPADIR.bit.GPIO12=0;
    GpioCtrlRegs.GPAPUD.bit.GPIO12=0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 0; // �ⲿ�ж� 1 ��ϵͳʱ�� SYSCLKOUT ͬ��

    GpioCtrlRegs.GPBMUX2.bit.GPIO48=0;
    GpioCtrlRegs.GPBDIR.bit.GPIO48=1;
    GpioCtrlRegs.GPBPUD.bit.GPIO48=0;
    GpioDataRegs.GPBCLEAR.bit.GPIO48=1;
    EDIS;

    // �ⲿ�ж�������
    EALLOW;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 12; // XINT1 �� GPIO12
    EDIS;

    // �ж�����������
    EALLOW;
    PieVectTable.XINT1 = &EXTI1_IRQn;
    EDIS;

    // ʹ��PIE���ж�
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1; // ʹ��PIE��1��INT4

    // ʹ�������ж�
    XIntruptRegs.XINT1CR.bit.POLARITY = 0;  // �½��ش����ж�
    XIntruptRegs.XINT1CR.bit.ENABLE= 1;     // ʹ�� XINT1

    // ʹ��CPU�ж�
    IER |= M_INT1;                          // ʹ��CPU�ж�1
    EINT;                                   // ��ȫ���ж�
    ERTM;
}

void EXTI2_Init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;    // GPIO input clock
    EDIS;

    EALLOW;
    //KEY�˿�����
    GpioCtrlRegs.GPAMUX1.bit.GPIO13=0;
    GpioCtrlRegs.GPADIR.bit.GPIO13=0;
    GpioCtrlRegs.GPAPUD.bit.GPIO13=0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 2;        // �ⲿ�ж�2��XINT2�������޶�6����������
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1 = 0xFF;   // ÿ���������ڵ�����Ϊ510*SYSCLKOUT

    GpioCtrlRegs.GPBMUX2.bit.GPIO48=0;
    GpioCtrlRegs.GPBDIR.bit.GPIO48=1;
    GpioCtrlRegs.GPBPUD.bit.GPIO48=0;
    GpioDataRegs.GPBCLEAR.bit.GPIO48=1;
    EDIS;

    EALLOW;
    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 13;   // XINT2��GPIO13
    EDIS;

    EALLOW; // �޸ı������ļĴ������޸�ǰӦ���EALLOW���
    PieVectTable.XINT2 = &EXTI2_IRQn;
    EDIS;   // EDIS����˼�ǲ������޸ı������ļĴ���

    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // ʹ��PIE��1��INT5

    XIntruptRegs.XINT2CR.bit.POLARITY = 0;      // �½��ش����ж�
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // ʹ��XINT2

    IER |= M_INT1;                              // ʹ��CPU�ж�1��INT1��
    EINT;                                       // ��ȫ���ж�
    ERTM;
}

int main()
{
    InitSysCtrl();

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    LED_Init();
    EXTI1_Init();

    int i = 0;

    while(1)
    {
        i++;
        if(i%2000==0)
        {
        LED1_TOGGLE;
        }
        DELAY_US(100);
    }
}
