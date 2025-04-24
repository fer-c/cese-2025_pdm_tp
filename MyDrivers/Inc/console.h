/*
 * console.h
 *
 *  Created on: Apr 21, 2025
 *      Author: fcoronel
 */

#ifndef INC_CONSOLE_H_
#define INC_CONSOLE_H_

#include "console_port.h"

/**
 * @brief Enumeración de los estados de la consola.
 */
typedef enum
{
    CONSOLE_STATUS_OK,
    CONSOLE_STATUS_ERROR,
    CONSOLE_STATUS_TIMEOUT
} console_status_t;

/**
 * @brief Estructura para la consola.
 */
typedef struct
{
    console_port_t *port; /**< @brief Estructura para el puerto de la consola. */
} console_t;

/**
 * @brief Inicializa el UART para la consola.
 * @param console Puntero a la estructura de la consola.
 * @param uart Puntero a la estructura del UART.
 * @return void
 */
console_status_t consoleInit(console_t *console,
                             console_port_t *port);

/**
 * @brief Limpia la pantalla de la consola.
 * @param console Puntero a la estructura de la consola.
 * @return void
 */
console_status_t consoleClearScreen(console_t *console);

/**
 * @brief Envía la configuración de la consola.
 * @param console Puntero a la estructura de la consola.
 * @return void
 */
console_status_t consoleSendConfiguration(console_t *console);

/**
 * @brief Lee un comando de la consola.
 * @param console Puntero a la estructura de la consola.
 * @param cmd Puntero al comando leído.
 * @return void
 */
console_status_t consoleReadCommand(console_t *console,
                                    uint8_t *cmd);

/**
 * @brief Lee un texto de la consola.
 * @param console Puntero a la estructura de la consola.
 * @param text Puntero al texto leído.
 * @param size Tamaño del texto a leer.
 * @return void
 */
console_status_t consoleRead(console_t *console,
                             uint8_t *text,
                             uint8_t size);
/**
 * @brief Escribe un texto en la consola.
 * @param console Puntero a la estructura de la consola.
 * @param text Puntero al texto a escribir.
 * @param size Tamaño del texto a escribir.
 * @return void
 */
console_status_t consoleWrite(console_t *console,
                              uint8_t *text,
                              uint8_t size);

/**
 * @brief Imprime una línea en la consola.
 * @param console Puntero a la estructura de la consola.
 * @param text Puntero al texto a imprimir.
 * @return void
 */
console_status_t consolePrintLine(console_t *console,
                                  uint8_t *text);

#endif /* INC_CONSOLE_H_ */
