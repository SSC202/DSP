/*
 * main.c
 *
 *  Created on: 2018-3-21
 *      Author: Administrator
 */


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "leds.h"
#include "time.h"
#include "uart.h"



/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void main()
{
	int i=0;
	char *msg;
	Uint16 ReceivedChar=0;

	InitSysCtrl();
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	LED_Init();
	TIM0_Init(150,200000);//200ms
	UARTa_Init(4800);

	msg = "Hello World!\r\n";
	UARTa_SendString(msg);
	msg = "You will enter a character, and the DSP will echo it back!\r\n";
	UARTa_SendString(msg);

	while(1)
	{
		msg = "\r\nEnter a character: ";
		UARTa_SendString(msg);

		// Wait for inc character
		while(SciaRegs.SCIFFRX.bit.RXFFST !=1);// wait for XRDY =1 for empty state
		// Get character
		ReceivedChar = SciaRegs.SCIRXBUF.all;

		// Echo character back
		msg = "  You sent: ";
		UARTa_SendString(msg);
		UARTa_SendByte(ReceivedChar);

		DELAY_US(1000);
	}
}

