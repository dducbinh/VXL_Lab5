/*
 * uart.h
 *
 *  Created on: Dec 12, 2024
 *      Author: doand
 */

#ifndef INC_UART_H_
#define INC_UART_H_
// 3
#include <stdio.h>
#include "main.h"
#include "command.h"
#include "volt_sensor.h"

#define UART_SIZE 10

extern uint8_t uartChar;
extern uint8_t uartBuffer[UART_SIZE];
extern uint8_t uartIdx;
extern unsigned char uartFlag;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void uartRead(void);
void uartSend(void);

#endif /* INC_UART_H_ */
