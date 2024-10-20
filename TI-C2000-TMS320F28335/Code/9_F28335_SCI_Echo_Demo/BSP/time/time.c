/*
 * time.c
 *
 *  Created on: 2018-1-24
 *      Author: Administrator
 */


#include "time.h"
#include "leds.h"



void TIM0_Init(float Freq, float Period)
{
	EALLOW;
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer 0
	EDIS;

	EALLOW;
	PieVectTable.TINT0 = &TIM0_IRQn;
	EDIS;

	// CPU Timer 0
	// Initialize address pointers to respective timer registers:
	CpuTimer0.RegsAddr = &CpuTimer0Regs;
	// Initialize timer period to maximum:
	CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
	CpuTimer0Regs.TPR.all  = 0;
	CpuTimer0Regs.TPRH.all = 0;
	// Make sure timer is stopped:
	CpuTimer0Regs.TCR.bit.TSS = 1;
	// Reload all counter register with period value:
	CpuTimer0Regs.TCR.bit.TRB = 1;
	// Reset interrupt counters:
	CpuTimer0.InterruptCount = 0;

	ConfigCpuTimer(&CpuTimer0, Freq, Period);

	CpuTimer0Regs.TCR.bit.TSS=0;

	IER |= M_INT1;

	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	EINT;
	ERTM;

}

interrupt void TIM0_IRQn(void)
{
	EALLOW;
	LED1_TOGGLE;
	PieCtrlRegs.PIEACK.bit.ACK1=1;
	EDIS;

	CpuTimer0Regs.TCR.bit.TIF=1;
	CpuTimer0Regs.TCR.bit.TRB=1;


}


void TIM1_Init(float Freq, float Period)
{
	EALLOW;
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 1; // CPU Timer 1
	EDIS;

	EALLOW;
	PieVectTable.XINT13 = &TIM1_IRQn;
	EDIS;

	// Initialize address pointers to respective timer registers:
	CpuTimer1.RegsAddr = &CpuTimer1Regs;
	// Initialize timer period to maximum:
	CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
	CpuTimer1Regs.TPR.all  = 0;
	CpuTimer1Regs.TPRH.all = 0;
	// Make sure timers are stopped:
	CpuTimer1Regs.TCR.bit.TSS = 1;
	// Reload all counter register with period value:
	CpuTimer1Regs.TCR.bit.TRB = 1;
	// Reset interrupt counters:
	CpuTimer1.InterruptCount = 0;

	ConfigCpuTimer(&CpuTimer1, Freq, Period);

	CpuTimer1Regs.TCR.bit.TSS=0;

	IER |= M_INT13;

	EINT;
	ERTM;

}

interrupt void TIM1_IRQn(void)
{
	EALLOW;
	LED3_TOGGLE;
	EDIS;
}



void TIM2_Init(float Freq, float Period)
{
	EALLOW;
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 1; // CPU Timer 2
	EDIS;

	EALLOW;
	PieVectTable.TINT2 = &TIM2_IRQn;
	EDIS;

	// Initialize address pointers to respective timer registers:
	CpuTimer2.RegsAddr = &CpuTimer2Regs;
	// Initialize timer period to maximum:
	CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;
	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
	CpuTimer2Regs.TPR.all  = 0;
	CpuTimer2Regs.TPRH.all = 0;
	// Make sure timers are stopped:
	CpuTimer2Regs.TCR.bit.TSS = 1;
	// Reload all counter register with period value:
	CpuTimer2Regs.TCR.bit.TRB = 1;
	// Reset interrupt counters:
	CpuTimer2.InterruptCount = 0;

	ConfigCpuTimer(&CpuTimer2, Freq, Period);

	CpuTimer2Regs.TCR.bit.TSS=0;

	IER |= M_INT14;

	EINT;
	ERTM;

}

interrupt void TIM2_IRQn(void)
{
	EALLOW;
	LED4_TOGGLE;
	EDIS;

}
