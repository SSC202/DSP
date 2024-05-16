#include "epwm.h"

/**
 * @brief   EPWM6 初始化函数
 */
void EPWM6_Init(Uint16 tbprd)
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;          // Disable TBCLK within the ePWM
    SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;         // ePWM6
    EDIS;

    InitEPwm6Gpio();
    // Setup Sync
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE; // Pass through

    // Allow each timer to be sync'ed
    EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm6Regs.TBPHS.half.TBPHS = 0;
    EPwm6Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm6Regs.TBPRD = tbprd;
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;      // Count up
    EPwm6Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm6Regs.CMPA.half.CMPA = 0;                   // Set compare A value
    EPwm6Regs.CMPB = 0;                             // Set Compare B value

    // Set actions
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_CLEAR;            // Set PWM1A on Zero
    EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;              // Clear PWM1A on event A, up count
    EPwm6Regs.AQCTLB.bit.ZRO = AQ_CLEAR;            // Set PWM1B on Zero
    EPwm6Regs.AQCTLB.bit.CBU = AQ_SET;              // Clear PWM1B on event B, up count
    EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // Select INT on Zero event
    EPwm6Regs.ETSEL.bit.INTEN = 1;                  // Enable INT
    EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;             // Generate INT on  1st event

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;          // Start all the timers synced
    EDIS;
}

void EPwm6A_SetCompare(Uint16 val)
{
    EPwm6Regs.CMPA.half.CMPA = val;  //设置占空比
}
void EPwm6B_SetCompare(Uint16 val)
{
    EPwm6Regs.CMPB = val;  //设置占空比
}

