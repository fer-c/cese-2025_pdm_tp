/*
 * led_matrix.c
 *
 *  Created on: Apr 20, 2025
 *      Author: fcoronel
 */

#include "led_matrix.h"
#include <stdlib.h>

static led_matrix_status_t _ledMatrixUpdate(led_matrix_t *led_matrix,
                                            uint8_t state);

led_matrix_status_t ledMatrixInit(led_matrix_t *led_matrix,
                                  led_matrix_port_t *port,
                                  uint8_t rows)
{
    assert_param(led_matrix != NULL);
    assert_param(port != NULL);
    assert_param(rows > 0);

    led_matrix->port = port;
    led_matrix->rows = rows;

    return LED_MATRIX_OK;
}

led_matrix_status_t ledMatrixInitialize(led_matrix_t *led_matrix)
{
    assert_param(led_matrix != NULL);

    led_matrix->state = PIXEL_OFF;  // Inicializa el estado de la matriz a apagado
    led_matrix->is_on = false;  // Inicializa el estado de encendido a apagado

    return _ledMatrixUpdate(led_matrix, led_matrix->state);  // Actualiza la matriz de LEDs
}

led_matrix_status_t ledMatrixSetPixel(led_matrix_t *led_matrix,
                                      uint8_t row,
                                      pixel_t pixel)
{
    assert_param(led_matrix != NULL);
    assert_param(row < led_matrix->rows);

    /*
     * El valor del pixel se en envia en 3 bits, donde:
     * - Row 0; Shift 1
     * - Row 1; Shift 4
     */
    uint8_t rows[2] = {
            ((led_matrix->state & 0b00001111) >> 1),
            ((led_matrix->state & 0b11110000) >> 4)
    };

    if (pixel == PIXEL_AUTO)
    {
        pixel = (rand() & 0b111);  // Genera un valor aleatorio entre 0 y 7
    }

    rows[row] = pixel;  // Actualiza el valor del pixel en la fila correspondiente

    led_matrix->state = (rows[1] << 4) | (rows[0] << 1);  // Actualiza el estado de la matriz

    return _ledMatrixUpdate(led_matrix, led_matrix->state);  // Actualiza la matriz de LEDs
}

led_matrix_status_t ledMatrixCyclePixels(led_matrix_t *led_matrix)
{
    uint8_t state = (led_matrix->state & 0b01111110) >> 1;  // Lee el estado del LED
    state = ((state + 1) << 1) & 0b01111110;  // Incrementa el estado del LED
    led_matrix->state = state;  // Actualiza el estado del LED
    return _ledMatrixUpdate(led_matrix, led_matrix->state);  // Actualiza la matriz de LEDs
}

led_matrix_status_t ledMatrixOff(led_matrix_t *led_matrix)
{
    assert_param(led_matrix != NULL);
    led_matrix->is_on = false;  // Inicializa el estado de encendido a apagado

    return _ledMatrixUpdate(led_matrix, PIXEL_OFF);  // Actualiza la matriz de LEDs
}

led_matrix_status_t ledMatrixOn(led_matrix_t *led_matrix)
{
    assert_param(led_matrix != NULL);
    led_matrix->is_on = true;  // Inicializa el estado de encendido a apagado
    return _ledMatrixUpdate(led_matrix, led_matrix->state);  // Actualiza la matriz de LEDs
}

led_matrix_status_t ledMatrixToggle(led_matrix_t *led_matrix)
{
    assert_param(led_matrix != NULL);

    led_matrix->is_on = !led_matrix->is_on;  // Cambia el estado de encendido

    if (led_matrix->is_on)
    {
        return ledMatrixOn(led_matrix);  // Actualiza la matriz de LEDs
    } else
    {
        return ledMatrixOff(led_matrix);  // Apaga la matriz de LEDs
    }
}

// Funciones Auxiliares

/**
 * @brief  _ledMatrixUpdate Función que actualiza el estado de la matriz de LEDs
 * @param  led_matrix Puntero a la estructura led_matrix_t
 * @return led_matrix_OK o led_matrix_ERROR
 */
static led_matrix_status_t _ledMatrixUpdate(led_matrix_t *led_matrix,
                                            uint8_t state)
{

    if (ledMatrixPortUpdate(led_matrix->port, state) == LED_MATRIX_PORT_ERROR)
    {
        return LED_MATRIX_ERROR;
    }

    return LED_MATRIX_OK;
}

