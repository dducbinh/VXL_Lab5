/*
 * scheduler.c
 *
 *  Created on: Dec 12, 2024
 *      Author: doand
 */


#include "scheduler.h"

SCH_Task task[SCH_TASK_NUM];

void SCH_Init(void) {
	for (uint8_t i = 0; i < SCH_TASK_NUM; i++) {
		task[i].funcPointer = 0;
		task[i].id = SCH_TASK_NUM - 1;
		task[i].delay = 0;
		task[i].period = 0;
		task[i].flag = 0;
	}
}

void SCH_Update(void) {
	if (task[0].funcPointer == 0) return;
	if (task[0].delay > 0) {
		if (task[0].delay > SCH_TIMER_TICK) {
			task[0].delay -= SCH_TIMER_TICK;
		} else {
			task[0].delay = 0;
		}
	}

	if (task[0].id = 0) {
		task[0].flag = 1;
	}
}

void SCH_Dispatch(void) {
	if (task[0].flag == 1) return;
	(*task[0].funcPointer)();
	if (task[0].period > 0) {
		SCH_RefreshTask();
	}
	else {
		SCH_DeleteTask(task[0].id);
	}
}

uint8_t SCH_AddTask(void (*funcPointer)(void), uint32_t delay, uint32_t period) {
    if (task[SCH_TASK_NUM - 1].funcPointer != 0) return 0;
    uint8_t curID = task[SCH_TASK_NUM - 1].id;
    uint32_t curDelay = 0;
    for (uint8_t i = 0; i < SCH_TASK_NUM; i ++) {
        curDelay += task[i].delay;
        if (curDelay > delay || task[i].funcPointer == 0) {
            for (uint8_t j = SCH_TASK_NUM - 1; j > i; j --) {
                task[j] = task[j - 1];
            }
            task[i].funcPointer = funcPointer;
            task[i].id = curID;
            task[i].period = period;
            task[i].flag = 0;
            if (curDelay > delay) {
                int newDelay = curDelay - delay;
                task[i].delay = task[i + 1].delay - newDelay;
                if (task[i].delay == 0) {
                    task[i].flag = 1;
                }
                task[i + 1].delay = newDelay;
                if (task[i + 1].delay == 0) {
                    task[i + 1].flag = 1;
                }
            }
            else {
                task[i].delay = delay - curDelay;
                if (task[i].delay == 0) {
                    task[i].flag = 1;
                }
            }
            return task[i].id;
        }
    }
    return 0;
}

unsigned char SCH_DeleteTask(uint8_t id) {
    for (uint8_t i = 0; i < SCH_TASK_NUM; i ++) {
    	if (task[i].funcPointer == 0) return 0;
        if (task[i].id == id) {
            uint8_t curID = task[i].id;
            if (task[i + 1].funcPointer != 0) {
                task[i + 1].delay += task[i].delay;
            }
            for (uint8_t j = i; j < SCH_TASK_NUM - 1; j ++) {
                task[j] = task[j + 1];
            }
            task[SCH_TASK_NUM - 1].funcPointer = 0;
            task[SCH_TASK_NUM - 1].id = curID;
            task[SCH_TASK_NUM - 1].delay = 0;
            task[SCH_TASK_NUM - 1].period = 0;
            task[SCH_TASK_NUM - 1].flag = 0;
            return task[SCH_TASK_NUM - 1].funcPointer == 0;
        }
    }
    return 0;
}

unsigned char SCH_RefreshTask(void) {
    if (task[0].funcPointer == 0) return 0;
    SCH_Task curTask = task[0];
    uint32_t curDelay = 0;
    for (uint8_t i = 0; i < SCH_TASK_NUM; i ++) {
        if (i + 1 == SCH_TASK_NUM || task[i + 1].funcPointer == NULL) {
            task[i].funcPointer = curTask.funcPointer;
            task[i].id = curTask.id;
            task[i].period = curTask.period;
            task[i].flag = 0;
            task[i].delay = curTask.period - curDelay;
            if (task[i].delay == 0) {
                task[i].flag = 1;
            }
            return 1;
        }
        curDelay += task[i + 1].delay;
        if (curDelay > curTask.period) {
            task[i].funcPointer = curTask.funcPointer;
            task[i].id = curTask.id;
            task[i].period = curTask.period;
            task[i].flag = 0;
            int newDelay = curDelay - curTask.period;
            task[i].delay = task[i + 1].delay - newDelay;
            if (task[i].delay == 0) {
                task[i].flag = 1;
            }
            task[i + 1].delay -= task[i].delay;
            if (task[i + 1].delay == 0) {
                task[i + 1].flag = 1;
            }
            return 1;
        }
        else {
            task[i] = task[i + 1];
        }
    }
    return 0;
}
