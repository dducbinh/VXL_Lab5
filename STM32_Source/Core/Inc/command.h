/*
 * command.h
 *
 *  Created on: Dec 12, 2024
 *      Author: doand
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_
// 3
#include <string.h>
#include "scheduler.h"
#include "uart.h"

void commandExecute(void);
void commandParser(void);

#endif /* INC_COMMAND_H_ */
