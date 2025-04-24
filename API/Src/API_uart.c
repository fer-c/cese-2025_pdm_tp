/*
 * API_uart.c
 *
 *  Created on: Apr 3, 2025
 *      Author: fcoronel
 */

#include "API_uart.h"

#include "stm32f4xx_hal.h"
#include <string.h>

static uint8_t *UART_BAUD_RATE = (uint8_t*) "baud rate: 115200\r\n";
static uint8_t *UART_PARITY = (uint8_t*) "parity: NONE\r\n";
static uint8_t *UART_STOP_BITS = (uint8_t*) "stop bits: 1\r\n";
static uint8_t *UART_WORD_LEN = (uint8_t*) "word len: 8bits\r\n";

const uint32_t UART_Timeout_Escritura = 1000; /**< Timeout para la excritura de datos por UART. */
const uint32_t UART_Timeout_Lectura = 1; /**< Timeout para la lectura de datos por UART. */

bool_t uartInit(uart_t *uart, UART_HandleTypeDef *huart,
		USART_TypeDef *instance) {
	assert_param(huart != NULL);
	assert_param(huart != NULL);
	assert_param(uart != NULL);

	uart->huart = huart; // Se asigna la estructura de configuracion del UART

	uart->huart->Instance = instance;
	uart->huart->Init.BaudRate = 115200;
	uart->huart->Init.WordLength = UART_WORDLENGTH_8B;
	uart->huart->Init.StopBits = UART_STOPBITS_1;
	uart->huart->Init.Parity = UART_PARITY_NONE;
	uart->huart->Init.Mode = UART_MODE_TX_RX;
	uart->huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart->huart->Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(uart->huart) == HAL_OK) {
		uartSendConfiguration(uart);
		return true;
	} else {
		return false;
	}

}

void uartSendClearScreen(uart_t *uart) {
	uint8_t clearScreen[] = "\x1b[2J\x1b[H"; // Borrar pantalla y mover el cursor al inicio
	uartSendString(uart, clearScreen);
}

void uartSendConfiguration(uart_t *uart) {
	uartSendString(uart, UART_BAUD_RATE);
	uartSendString(uart, UART_WORD_LEN);
	uartSendString(uart, UART_STOP_BITS);
	uartSendString(uart, UART_PARITY);
}

void uartSendString(uart_t *uart, uint8_t *pstring) {
	assert_param(pstring != NULL);
	uint16_t len = strlen((char*) pstring);
	HAL_UART_Transmit(uart->huart, pstring, len, UART_Timeout_Escritura);
}

void uartSendStringSize(uart_t *uart, uint8_t *pstring, uint16_t size) {
	assert_param(pstring != NULL);
	HAL_UART_Transmit(uart->huart, pstring, size, UART_Timeout_Escritura);
}

void uartReceiveStringSize(uart_t *uart, uint8_t *pstring, uint16_t size) {
	assert_param(pstring != NULL);
	assert_param(size > 0);
	HAL_UART_Receive(uart->huart, pstring, size, UART_Timeout_Lectura);
}
