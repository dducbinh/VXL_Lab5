/*
 * command.c
 *
 *  Created on: Dec 12, 2024
 *      Author: doand
 */


#include "command.h"

static uint8_t commandTask = 0;
char commandString[UART_SIZE];

void commandExecute(void) {
	if (strcmp(commandString, "!RST#") == 0) {
		SCH_AddTask(commandString, 0, 0);
		commandTask = SCH_DeleteTask(commandTask);
		commandTask = SCH_AddTask(uartSend, 100, 300);
		return;
	}

	if (strcmp(commandString, "!OK#") == 0) {
		commandTask = SCH_DeleteTask(commandTask);
		return;
	}
}

void commandParser(void) {
	if (uartIdx == 0) {
		if (uartBuffer[uartIdx] == '!') {
			uartIdx++;
		}
	}
	else {
		if (uartBuffer[uartIdx] == '#') {
			sprintf(commandString, "%s", uartBuffer);
			SCH_AddTask(commandExecute, 0, 0);
			memset(uartBuffer, 0, UART_SIZE);
			uartIdx = 0;
		}
		else {
			if (uartIdx < UART_SIZE - 1) {
				uartIdx++;
			}
		}
	}
}
