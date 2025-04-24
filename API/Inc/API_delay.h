/*
 * API.delay.h
 *
 *  Created on: Mar 20, 2025
 *      Author: fcoronel
 */

#ifndef INC_API_DELAY_H_
#define INC_API_DELAY_H_

#include "API_stdtypes.h"

/**
 * @brief Tipo de dato para representar un tick.
 */
typedef uint32_t tick_t;

/**
 * @brief Tipo de dato para representar un índice.
 */
typedef uint8_t idx_t;

/**
 * @brief Tipo de dato para representar un número de veces.
 */
typedef struct {
	tick_t startTime; /**< Tiempo de inicio del delay. */
	tick_t duration; /**< Duración del delay. */
	bool_t running; /**< Indica si el delay está corriendo. */
} delay_t;

/**
 * @brief Inicializa un delay.
 * @param delay Puntero al delay a inicializar.
 * @param duration Duración del delay.
 * @return void
 */
void delayInit(delay_t *delay, tick_t duration);

/**
 * @brief Actualiza el estado de un delay.
 * @param delay Puntero al delay a actualizar.
 * @return void
 */
bool_t delayRead(delay_t *delay);

/**
 * @brief Inicia un delay.
 * @param delay Puntero al delay a iniciar.
 * @param duration Duración del delay.
 * @return void
 */
void delayWrite(delay_t *delay, tick_t duration);

/**
 * @brief Verifica si el delay esta con estado `running == true`.
 * @param delay Puntero al delay.
 * @return `true` si el delay esta corriendo, `false` en caso contrario.
 */
bool_t delayIsRunning(delay_t *delay);

#endif /* INC_API_DELAY_H_ */
