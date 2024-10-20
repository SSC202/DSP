/*
 * uart.h
 *
 *  Created on: 2018-1-31
 *      Author: Administrator
 */

#ifndef UART_H_
#define UART_H_

#include "DSP2833x_Device.h"     // DSP2833x ͷ�ļ�
#include "DSP2833x_Examples.h"   // DSP2833x �������ͷ�ļ�


void UARTa_Init(Uint32 baud);
void UARTa_SendByte(int a);
void UARTa_SendString(char * msg);

#endif /* UART_H_ */
