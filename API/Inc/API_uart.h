/*
 * API_uart.h
 *
 *  Created on: Apr 3, 2025
 *      Author: fcoronel
 */

#ifndef INC_API_UART_H_
#define INC_API_UART_H_

#include "stm32f4xx_hal.h"
#include "API_delay.h"

typedef struct {
	UART_HandleTypeDef *huart; /**< Puntero a la estructura de configuración del UART. */
} uart_t;

/**
 * @brief inicializa el UART, en particular el UART2
 */
bool_t uartInit(uart_t *uart, UART_HandleTypeDef *huart,
		USART_TypeDef *instance);

/**
 * @brief Envia un comando para limpiar la pantalla por el UART
 * @param none
 * @return: none
 */
void uartSendClearScreen(uart_t *uart);

/**
 * @brief Envia la configuracion del UART por el UART
 * @param none
 * @return: none
 */
void uartSendConfiguration(uart_t *uart);

/**
 * @brief Envia un byte por el UART
 * @param byte: byte a enviar
 * @return: none
 */
void uartSendString(uart_t *uart, uint8_t *pstring);

/**
 * @brief Recibe un byte por el UART
 * @param byte: puntero a la variable donde se guardara el byte recibido
 * @return: none
 */
void uartSendStringSize(uart_t *uart, uint8_t *pstring, uint16_t size);

/**
 * @brief Recibe un byte por el UART
 * @param byte: puntero a la variable donde se guardara el byte recibido
 * @return: none
 */
void uartReceiveStringSize(uart_t *uart, uint8_t *pstring, uint16_t size);

#endif /* INC_API_UART_H_ */
