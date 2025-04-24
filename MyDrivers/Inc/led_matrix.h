/*
 * led_matrix.h
 *
 *  Created on: Apr 20, 2025
 *      Author: fcoronel
 */

#ifndef INC_LED_MATRIX_H_
#define INC_LED_MATRIX_H_

#include "led_matrix_port.h"

#define PIXEL_AUTO  0xF0U  /**< Color aleatorio */
#define PIXEL_OFF   0b000U /**< Apagado */
#define PIXEL_BLUE  0b001U /**< Azul */
#define PIXEL_RED   0b010U /**< Rojo */
#define PIXEL_GREEN 0b100U /**< Verde */
#define PIXEL_YELLOW (PIXEL_RED | PIXEL_GREEN) /**< Amarillo */
#define PIXEL_CYAN  (PIXEL_BLUE | PIXEL_GREEN) /**< Cyan */
#define PIXEL_MAGENTA (PIXEL_RED | PIXEL_BLUE) /**< Magenta */
#define PIXEL_WHITE (PIXEL_RED | PIXEL_GREEN | PIXEL_BLUE) /**< Blanco */

#define LED_LINEA_SUP 1 /**< Fila superior del LED Matrix */
#define LED_LINEA_INF 0 /**< Fila inferior del LED Matrix */

typedef uint8_t pixel_t; /**< Tipo de dato para el pixel 3 bits GRB {green, red, blue}*/

typedef enum
{
    LED_MATRIX_OK = 0x00U,
    LED_MATRIX_ERROR = 0x01U,
} led_matrix_status_t;

typedef struct
{
    led_matrix_port_t *port; /**< Puntero al puerto SPI del LED Matrix */
    uint8_t rows; /**< Número de filas del LED Matrix */
    uint8_t state; /**< Estado del LED Matrix */
    bool_t is_on; /**< Estado de encendido del LED Matrix */
} led_matrix_t;

/**
 * @brief Inicializa la estructura del LED Matrix.
 * @param led_matrix Puntero a la estructura led_matrix_t.
 * @param port Puntero al puerto SPI del LED Matrix.
 * @param rows Número de filas del LED Matrix.
 * @return void
 */
led_matrix_status_t ledMatrixInit(led_matrix_t *led_matrix,
                                  led_matrix_port_t *port,
                                  uint8_t rows);

/**
 * @brief Inicializa el LED Matrix, apagando todos los LEDs.
 * @param led_matrix Puntero a la estructura led_matrix_t.
 * @return led_matrix_OK o led_matrix_ERROR
 */
led_matrix_status_t ledMatrixInitialize(led_matrix_t *led_matrix);

/**
 * @brief Actualiza un LED en la matriz.
 * @param led_matrix Puntero a la estructura led_matrix_t.
 * @param row Fila del LED.
 * @param rbg_pixel Estado del LED en 3 bits (GRB)
 * @return led_matrix_OK o led_matrix_ERROR
 */
led_matrix_status_t ledMatrixSetPixel(led_matrix_t *led_matrix,
                                      uint8_t row,
                                      pixel_t pixel);

/**
 * @brief Actualiza los leds de la matrix moviendo un valor
 * @param led_matrix Puntero a la estructura led_matrix_t.
 * @return led_matrix_OK o led_matrix_ERROR
 */
led_matrix_status_t ledMatrixCyclePixels(led_matrix_t *led_matrix);

/**
 * @brief Apaga todos los LEDs de la matriz.
 * @param led_matrix Puntero a la estructura led_matrix_t.
 * @return led_matrix_OK o led_matrix_ERROR
 */
led_matrix_status_t ledMatrixOff(led_matrix_t *led_matrix);

/**
 * @brief Enciende todos los LEDs de la matriz.
 * @param led_matrix Puntero a la estructura led_matrix_t.
 * @return led_matrix_OK o led_matrix_ERROR
 */
led_matrix_status_t ledMatrixOn(led_matrix_t *led_matrix);

/**
 * @brief Cambia el estado de encendido de la matriz.
 * @param led_matrix Puntero a la estructura led_matrix_t.
 * @return led_matrix_OK o led_matrix_ERROR
 */
led_matrix_status_t ledMatrixToggle(led_matrix_t *led_matrix);

#endif /* INC_LED_MATRIX_H_ */
