/*
 * API_delay.c
 *
 *  Created on: Mar 20, 2025
 *      Author: fcoronel
 */

#include "API_delay.h"

#include "stm32f4xx_hal.h"

void delayInit(delay_t *delay, tick_t duration) {
	assert_param(delay != NULL);
	delay->startTime = 0;
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead(delay_t *delay) {
	assert_param(delay != NULL);
	bool_t result = false;
	if (!delay->running) {
		delay->startTime = HAL_GetTick();
		delay->running = true;
	} else {
		tick_t now = HAL_GetTick();
		tick_t runningTime = now - delay->startTime;
		if (runningTime > delay->duration) {
			result = true;
			delay->running = false;
		}
	}
	return result;
}

void delayWrite(delay_t *delay, tick_t duration) {
	assert_param(delay != NULL);

	if (!delayIsRunning(delay)) { // Solo se puede modificar la duración si el delay no está corriendo.
		delay->duration = duration;
	}
}

bool_t delayIsRunning(delay_t *delay) {
	assert_param(delay != NULL);
	return delay->running;
}
