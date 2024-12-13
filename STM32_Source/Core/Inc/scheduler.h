/*
 * scheduler.h
 *
 *  Created on: Dec 12, 2024
 *      Author: doand
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
// 1
#include <stdio.h>
#include <stdint.h>
#include "main.h"

#define SCH_TASK_NUM	20
#define SCH_TIMER_TICK	10

typedef struct {
	void (*funcPointer) (void);
	uint8_t	id;
	uint32_t delay;
	uint32_t period;
	unsigned char flag;
} SCH_Task;

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch(void);

uint8_t SCH_AddTask(void (*funcPointer)(void), uint32_t delay, uint32_t period);
unsigned char SCH_DeleteTask(uint8_t id);
unsigned char SCH_RefreshTask(void);

#endif /* INC_SCHEDULER_H_ */
