/*
 * lcd_port.h
 *
 *  Created on: Apr 19, 2025
 *      Author: fcoronel
 */

#ifndef INC_LCD_PORT_H_
#define INC_LCD_PORT_H_

#include "API_i2c.h"
#include "API_stdtypes.h"

/**
 * @brief Estructura Port de LCD.
 */
typedef struct _lcd_port_t {
    i2c_t *i2c; /**< Puntero al manejador I2C */
} lcd_port_t;

/**
 * @brief Inicializa la estructura del puerto I2C para el LCD.
 * @param port Puntero a la estructura LCD_Port_t.
 * @param i2c Puntero al manejador I2C.
 * @param address Dirección del dispositivo I2C.
 */
void lcdPortInit(lcd_port_t *port, i2c_t *i2c);

/**
 * @brief Envía un byte al LCD a través del puerto I2C.
 * @param port Puntero a la estructura LCD_Port_t.
 * @param valor Byte a enviar al LCD.
 * @return true si la transmisión fue exitosa, false en caso contrario.
 */
bool_t lcdPortWriteByte(lcd_port_t *port, uint8_t valor);


#endif /* INC_LCD_PORT_H_ */
