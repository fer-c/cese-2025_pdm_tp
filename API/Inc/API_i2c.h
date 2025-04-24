/*
 * API_i2c.h
 *
 *  Created on: Apr 16, 2025
 *      Author: fcoronel
 */

#ifndef INC_API_I2C_H_
#define INC_API_I2C_H_

#include "stm32f4xx_hal.h"
#include "API_stdtypes.h"

/**
 * @brief I2C status:
 * - I2C_OK: Operation completed successfully
 * - I2C_ERROR: Operation failed
 */
typedef enum _i2c_status_t
{
    I2C_STATUS_OK = 0,
    I2C_STATUS_ERROR = 1,
} i2c_status_t;

/**
 * @brief Periferico I2C
 * - hi2c: Puntero al manejador I2C
 * - address: Dirección del dispositivo I2C
 */
typedef struct _i2c_t
{
    I2C_HandleTypeDef *hi2c;
    uint8_t address;
} i2c_t;

/**
 * @brief Inicialización de periferico I2C
 * @param i2c Puntero a la estructura I2C
 * @param hi2c Puntero al manejador I2C
 * @param address Dirección del dispositivo I2C
 * @param config Puntero a la estructura de configuración I2C
 * @return None
 */
void i2cInit(i2c_t *i2c,
             I2C_HandleTypeDef *hi2c,
             I2C_TypeDef *i2c_instance,
             uint8_t address);

/**
 * @brief Transmisión a I2C
 * @param i2c Puntero a la estructura I2C
 * @data data Datos a transmitir
 * @size Size Tamaño de los datos a transmitir
 * @return I2C_OK o I2C_ERROR
 */
i2c_status_t i2cTransmit(i2c_t *i2c,
                         uint8_t *data,
                         uint16_t size);

#endif /* INC_API_I2C_H_ */
