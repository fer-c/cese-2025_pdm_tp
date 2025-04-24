/*
 * API_delay_matrix.h
 *
 *  Created on: Mar 21, 2025
 *      Author: fcoronel
 */

#ifndef INC_API_DELAY_TIME_MATRIX_H_
#define INC_API_DELAY_TIME_MATRIX_H_

#include "API_delay.h"

/**
 * @brief Tipo de dato para representar un indice en el array.
 */
typedef uint8_t index_t;

/**
 * @brief Estructura que representa los tiempos de duración de un delay.
 *
 * Esta estructura se utiliza para gestionar duraciones de ejecución
 * de un delay en base a una array de duraciones.
 *
 * @note Se debe inicializar la matriz con la función delayMatrixInit.
 *
 */
typedef struct {
	index_t num_durations; /**< Número de duraciones. */
	tick_t *durations; /**< Array de duraciones. */
	index_t current_idx; /**< Índice en el array de duraciones que indica la duración actual. */
} delay_time_matrix_t;

/**
 * @brief Inicializa una matriz de duraciones con un array de repeticiones para cada duración.
 *
 * @param num_durations Número total de duraciones.
 * @param durations Array de duraciones.
 *
 * @return void
 *
 */
void delayTimeMatrixInit(delay_time_matrix_t *matrix, index_t num_durations,
		tick_t durations[]);

/**
 * @brief Devuelve la duración actual de la matriz.
 *
 * @param matrix Puntero a la matriz de duraciones.
 *
 * @return Duración actual.
 */
tick_t delayTimeMatrixRead(delay_time_matrix_t *matrix);

/**
 * @brief Avanza la duración matriz y devuelve la nueva duración.
 *
 * @param matrix Puntero a la matriz de duraciones.
 *
 * @return la nueva duración indicada por la matriz.
 */
tick_t delayTimeMatrixNext(delay_time_matrix_t *matrix);

#endif /* INC_API_DELAY_TIME_MATRIX_H_ */
