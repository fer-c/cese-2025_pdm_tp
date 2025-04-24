/*
 * API_debounce.h
 *
 *  Created on: Mar 28, 2025
 *      Author: fcoronel
 */

#ifndef INC_API_DEBOUNCE_H_
#define INC_API_DEBOUNCE_H_

#include "API_delay.h"
#include "API_delay_time_matrix.h"

/**
 * @brief Enumeración de estados para la FSM de debounce.
 */
typedef enum {
	BUTTON_UP, /**< Estado inicial, botón liberado. */
	BUTTON_FALLING, /**< Estado de caída. */
	BUTTON_DOWN,  /**< Estado de presión, botón presionado. */
	BUTTON_RAISING, /**< Estado de subida, botón liberado. */
} debounceState_t;

typedef void (*callback_t)(void*);

/**
 * @brief Estructura que representa la máquina de estados para el debounce.
 *
 * Esta estructura contiene el estado actual de la máquina de estados,
 * un delay para el debounce y una variable que indica si el botón fue presionado.
 *
 * @note Se debe inicializar la máquina de estados con la función debounceFSM_init.
 */
typedef struct {
	debounceState_t state; /**< Estado actual de la FSM. */
	delay_t debounce_delay; /**< Delay para el debounce. */
	bool_t btn_pressed; /**< Variable que indica si el botón fue presionado. */
	callback_t buttonPressed; /**< Callback para el evento de botón presionado. */
	callback_t buttonReleased; /**< Callback para el evento de botón liberado. */
	void *callback_data; /**< Datos para el callback. */
} debounce_t;

/**
 * @brief  Inicializa el estado de la FSM
 * @param  fsm Puntero a la máquina de estados a inicializar
 * @return None
 */
void debounceFSM_init(debounce_t *fsm);

/**
 * @brief  Configura los callbacks para los eventos de botón presionado y liberado.
 * @param  fsm Puntero a la máquina de estados
 * @param  buttonPressed Callback para el evento de botón presionado
 * @param  buttonReleased Callback para el evento de botón liberado
 * @param  callback_data Datos para el callback
 * @return None
 */
void debounceFSM_setButtonCallbacks(debounce_t *fsm, callback_t buttonPressed,
		callback_t buttonReleased, void *callback_data);

/**
 * @brief  Actualiza el estado de la FSM
 * @param  fsm Puntero a la máquina de estados a actualizar
 * @return None
 */
void debounceFSM_update(debounce_t *fsm);

/**
 * @brief  Devuelve true si el botón fue presionado desde la última vez
 * 	   que se llamó a la función
 * @param  fsm Puntero a la máquina de estados
 * @return true si el botón fue presionado, false en caso contrario
 */
bool_t readKey(debounce_t *fsm);

/**
 * @brief  Callback que se ejecuta cuando el FSM pasa al estado BUTTON_DOWN.
 * 	Esto se ejecuta en el flanco de transición.
 * @param  fsm Puntero a la máquina de estados
 * @return None
 */
void buttonPressed(debounce_t *fsm);

/**
 * @brief  Callback que se ejecuta cuando el FSM pasa al estado BUTTON_UP.
 *  Esto se ejecuta en el flanco de transición
 * @param  fsm Puntero a la máquina de estados
 * @return None
 */
void buttonReleased(debounce_t *fsm);

#endif /* INC_API_DEBOUNCE_H_ */
