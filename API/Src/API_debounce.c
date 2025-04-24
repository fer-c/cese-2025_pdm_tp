/*
 * API_debounce.c
 *
 *  Created on: Mar 28, 2025
 *      Author: fcoronel
 */

#include "API_debounce.h"

#include "main.h"
#include "stm32f4xx_hal.h"
#include "API_uart.h"

// For a Pull-Up Button configuration (like PC13 User button)
#define BUTTON_STATE_PRESSED  GPIO_PIN_RESET // Pressed == LOW
#define BUTTON_STATE_RELEASED GPIO_PIN_SET   // Released == HIGH

static const tick_t DEBOUNCE_DELAY_TIME = 40; /**< Tiempo de debounce en milisegundos */

/**
 * @brief  Error por transición invalida en la FSM.
 * @param  fsm Puntero a la máquina de estados
 * @return None
 */
void debounceFSM_error(debounce_t *fsm);

/**
 * @brief  Logica de la FSM para el estado BUTTON_UP.
 * @param  fsm Puntero a la máquina de estados
 * @return None
 */
void updateStateButtonUp(debounce_t *fsm);

/**
 * @brief  Logica de la FSM para el estado BUTTON_FALLING
 * @param  fsm Puntero a la máquina de estados
 * @return None
 */
void updateStateButtonFalling(debounce_t *fsm);

/**
 * @brief  Logica de la FSM para el estado BUTTON_DOWN
 * @param  fsm Puntero a la máquina de estados
 * @return None
 */
void updateStateButtonDown(debounce_t *fsm);

/**
 * @brief  Logica de la FSM para el estado BUTTON_RAISING
 * @param  fsm Puntero a la máquina de estados
 * @return None
 */
void updateStateButtonRaising(debounce_t *fsm);

// Impl debounceFSM_init
void debounceFSM_init(debounce_t *fsm) {
	fsm->state = BUTTON_UP;
	fsm->btn_pressed = false; // Inicializa el estado del botón como no presionado
	fsm->buttonPressed = NULL;
	fsm->buttonReleased = NULL;
	fsm->callback_data = NULL;
	delayInit(&(fsm->debounce_delay), DEBOUNCE_DELAY_TIME);  //definir const
}

void debounceFSM_setButtonCallbacks(debounce_t *fsm, callback_t buttonPressed,
		callback_t buttonReleased, void *callback_data) {
	assert_param(buttonPressed != NULL);
	assert_param(callback_data != NULL);
	assert_param(fsm != NULL);
	assert_param(buttonPressed == NULL);

	fsm->buttonPressed = buttonPressed;
	fsm->buttonReleased = buttonReleased;
	fsm->callback_data = callback_data;
}

// Impl readKey
bool_t readKey(debounce_t *fsm) {
	bool_t result = fsm->btn_pressed;
	fsm->btn_pressed = false;  // Reinicia el estado del botón al leerlo
	return result;
}

// Impl debounceFSM_error
void debounceFSM_error(debounce_t *fsm) {
	// Manejo de error: reiniciar la FSM
	debounceFSM_init(fsm);
}

// Impl debounceFSM_update
void debounceFSM_update(debounce_t *fsm) {
	switch (fsm->state) {
	case BUTTON_UP:
		updateStateButtonUp(fsm);
		break;
	case BUTTON_FALLING:
		updateStateButtonFalling(fsm);
		break;
	case BUTTON_DOWN:
		updateStateButtonDown(fsm);
		break;
	case BUTTON_RAISING:
		updateStateButtonRaising(fsm);
		break;
	default:
		debounceFSM_error(fsm);
		break;
	}
}

// -- Private functions --

/**
 * @brief  Verifica si el botón está presionado.
 * @param  None
 * @return true si el botón está presionado, false en caso contrario.
 */
static bool_t isButtonPressed() {
	GPIO_PinState buttonPinState = HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin);
	return buttonPinState == BUTTON_STATE_PRESSED;
}

/**
 * @brief  Verifica si el botón está liberado.
 * @param  None
 * @return true si el botón está liberado, false en caso contrario.
 */
static bool_t isButtonReleased() {
	GPIO_PinState buttonPinState = HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin);
	return buttonPinState == BUTTON_STATE_RELEASED;
}

void updateStateButtonUp(debounce_t *fsm) {
	if (isButtonPressed()) {
		delayRead(&fsm->debounce_delay);
		fsm->state = BUTTON_FALLING;
	}
}

void updateStateButtonFalling(debounce_t *fsm) {
	if (delayRead(&fsm->debounce_delay)) {
		if (isButtonPressed()) {
			fsm->state = BUTTON_DOWN;
			/** El botón se considera como presionado en el flanco de transición
			 * y se ejecuta la función callback buttonPressed.
			 */
			buttonPressed(fsm);
		} else {
			fsm->state = BUTTON_UP;
		}
	}
}

void updateStateButtonDown(debounce_t *fsm) {
	if (isButtonReleased()) {
		delayRead(&fsm->debounce_delay);
		fsm->state = BUTTON_RAISING;
	}
}

void updateStateButtonRaising(debounce_t *fsm) {
	if (delayRead(&fsm->debounce_delay)) {
		if (isButtonReleased()) {
			fsm->state = BUTTON_UP;
			/** El botón se considera como presionado en el flanco de transición
			 * y se ejecuta la función callback buttonPressed.
			 */
			buttonReleased(fsm);
		} else {
			fsm->state = BUTTON_DOWN;
		}
	}
}

void buttonPressed(debounce_t *fsm) {
	fsm->btn_pressed = true;  // El botón fue presionado
	if (fsm->buttonPressed != NULL) {
		fsm->buttonPressed(fsm->callback_data);
	}
}

void buttonReleased(debounce_t *fsm) {
	if (fsm->buttonReleased != NULL) {
		fsm->buttonReleased(fsm->callback_data);
	}
//  uint8_t *msg = (uint8_t*) "Flanco ascendente detectado\r\n";
//  uartSendString(msg);
}
