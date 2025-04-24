/*
 * console_port.h
 *
 *  Created on: Apr 22, 2025
 *      Author: fcoronel
 */

#ifndef INC_CONSOLE_PORT_H_
#define INC_CONSOLE_PORT_H_

#include "API_uart.h"

/**
 * @brief Estructura para el puerto de la consola.
 */
typedef struct
{
    uart_t *uart; /* Estructura para el UART. */
} console_port_t;

/**
 * @brief Inicializa el puerto de la consola.
 * @param port Puntero a la estructura del puerto de la consola.
 * @param uart Puntero a la estructura del UART.
 * @return void
 */
void consolePortInit(console_port_t *port,
                     uart_t *uart);

/**
 * @brief Envía un comando para limpiar la pantalla de la consola.
 * @param port Puntero a la estructura del puerto de la consola.
 * @param text Puntero al comando a enviar.
 * @return void
 */
void consolePortClearScreen(console_port_t *port);

/**
 * @brief Envía la configuración de la consola.
 * @param console Puntero a la estructura de la consola.
 * @return void
 */
void consolePortSendConfiguration(console_port_t *port);

/**
 * @brief Lee un comando de la consola.
 * @param console Puntero a la estructura de la consola.
 * @param cmd Puntero al comando leído.
 * @return void
 */
void consolePortReadCommand(console_port_t *port,
                            uint8_t *cmd);

/**
 * @brief Lee un comando de la consola.
 * @param console Puntero a la estructura de la consola.
 * @param text Puntero al comando leído.
 * @param size Tamaño del comando a leer.
 * @return void
 */
void consolePortReceiveStringSize(console_port_t *port,
                                  uint8_t *text,
                                  uint8_t size);

/**
 * @brief Envía un comando a la consola.
 * @param console Puntero a la estructura de la consola.
 * @param text Puntero al comando a enviar.
 * @param size Tamaño del comando a enviar.
 * @return void
 */
void consolePortSendStringSize(console_port_t *port,
                               uint8_t *text,
                               uint8_t size);

/**
 * @brief Envía un comando a la consola.
 * @param console Puntero a la estructura de la consola.
 * @param text Puntero al comando a enviar.
 * @return void
 */
void consolePortSendString(console_port_t *port,
                           uint8_t *text);

#endif /* INC_CONSOLE_PORT_H_ */
