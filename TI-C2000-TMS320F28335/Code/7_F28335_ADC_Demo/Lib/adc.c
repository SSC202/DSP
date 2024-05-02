#include "adc.h"

/**
 * @brief   ADC 读取数据函数
 */
Uint16 Read_ADCValue(void)
{
    while (AdcRegs.ADCST.bit.INT_SEQ1== 0);
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    return AdcRegs.ADCRESULT0>>4;
}

/**
 * @brief   ADC 初始化函数
 */
void ADC_Init(void)
{
    // Specific clock setting for this example:
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;               // ADC clock init
    EDIS;
    // Specific clock setting for this example:
    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;                // HSPCLK = SYSCLKOUT/(2*ADC_MODCLK)
    EDIS;
    InitAdc();                                         // For this example, init the ADC
    // Specific ADC setup for this example:
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;                   // 1 Cascaded mode
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
    AdcRegs.ADCTRL1.bit.CONT_RUN = 1;                   // Setup continuous run
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;
    // Start SEQ1
    AdcRegs.ADCTRL2.all = 0x2000;
}
