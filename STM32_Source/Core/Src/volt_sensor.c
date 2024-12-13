/*
 * volt_sensor.c
 *
 *  Created on: Dec 13, 2024
 *      Author: doand
 */


#include "volt_sensor.h"

uint32_t sensorValue = 0;

void sensorInput() {
	sensorValue = HAL_ADC_GetValue(&hadc1);
}
