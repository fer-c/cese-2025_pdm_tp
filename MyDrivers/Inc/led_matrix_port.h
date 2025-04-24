/*
 * led_matrix_port_port.h
 *
 *  Created on: Apr 20, 2025
 *      Author: fcoronel
 */

#ifndef INC_LED_MATRIX_PORT_H_
#define INC_LED_MATRIX_PORT_H_

#include "stm32f4xx_hal.h"

#include "API_spi.h"
#include "API_stdtypes.h"

typedef enum
{
    LED_MATRIX_PORT_OK = 0x00U,
    LED_MATRIX_PORT_ERROR = 0x01U,
} led_matrix_port_status_t;

typedef struct
{
    spi_t *port; /**< Puntero al puerto SPI del LED Matrix */
} led_matrix_port_t;

/**
 * @brief Inicializa la estructura del LED Matrix.
 * @param led_matrix Puntero a la estructura led_matrix_port_t.
 * @param port Puntero al puerto SPI del LED Matrix.
 * @param rows Número de filas del LED Matrix.
 * @param cols Número de columnas del LED Matrix.
 * @return void
 */
led_matrix_port_status_t ledMatrixPortInit(led_matrix_port_t *led_matrix,
                                           spi_t *port);

/**
 * @brief Actualiza un LED en la matriz.
 * @param led_matrix Puntero a la estructura led_matrix_port_t.
 * @param rbg_pixel Estado del LED en 3 bits (GRB)
 * @return led_matrix_port_OK o led_matrix_port_ERROR
 */
led_matrix_port_status_t ledMatrixPortUpdate(led_matrix_port_t *led_matrix,
                                               uint8_t rbg_pixel);

#endif /* INC_LED_MATRIX_PORT_H_ */
