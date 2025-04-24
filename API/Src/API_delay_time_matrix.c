/*
 * API_delay_matrix.c
 *
 *  Created on: Mar 21, 2025
 *      Author: fcoronel
 */
#include "API_delay_time_matrix.h"

#include "stm32f4xx_hal.h"

void delayTimeMatrixInit(delay_time_matrix_t *matrix, index_t num_durations,
		tick_t durations[]) {
	assert_param(matrix != NULL);
	assert_param(durations != NULL);

	matrix->num_durations = num_durations;
	matrix->current_idx = 0;
	matrix->durations = durations;
}

tick_t delayTimeMatrixRead(delay_time_matrix_t *matrix) {
	assert_param(matrix != NULL);

	return matrix->durations[matrix->current_idx];
}

tick_t delayTimeMatrixNext(delay_time_matrix_t *matrix) {
	assert_param(matrix != NULL);

	matrix->current_idx = (matrix->current_idx + 1) % matrix->num_durations;

	return delayTimeMatrixRead(matrix);
}

