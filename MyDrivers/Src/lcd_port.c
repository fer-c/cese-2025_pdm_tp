/*
 * lcd_port.c
 *
 *  Created on: Apr 19, 2025
 *      Author: fcoronel
 */

#include "lcd_port.h"

extern void Error_Handler(void);

void lcdPortInit(lcd_port_t *port,
                 i2c_t *i2c)
{
    assert_param(port != NULL);
    port->i2c = i2c;
}

bool_t lcdPortWriteByte(lcd_port_t *port,
                        uint8_t valor)
{
    bool_t result = true;
    i2c_status_t transmit_result = i2cTransmit(port->i2c, &valor, sizeof(valor));
    if (transmit_result != I2C_STATUS_OK)
    {
        Error_Handler();
        result = false;
    }
    return result;
}
