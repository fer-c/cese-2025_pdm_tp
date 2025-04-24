/*
 * led_matrix_port.c
 *
 *  Created on: Apr 20, 2025
 *      Author: fcoronel
 */

#include "led_matrix_port.h"

led_matrix_port_status_t ledMatrixPortInit(led_matrix_port_t *led_matrix,
                                           spi_t *port)
{
    assert_param(led_matrix != NULL);
    assert_param(port != NULL);

    led_matrix->port = port;

    return LED_MATRIX_PORT_OK;
}

led_matrix_port_status_t ledMatrixPortUpdate(led_matrix_port_t *led_matrix,
                                               uint8_t state)
{
    assert_param(led_matrix != NULL);

    // Enviar el comando para actualizar el LED
    if ( spiTransmit(led_matrix->port, &state, sizeof(state)) == SPI_ERROR)
    {
        return LED_MATRIX_PORT_ERROR;
    }

    return LED_MATRIX_PORT_OK;
}
