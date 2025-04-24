/*
 * API_i2c.c
 *
 *  Created on: Apr 16, 2025
 *      Author: fcoronel
 */

#include "API_i2c.h"

#include "stm32f4xx_hal.h"

extern void Error_Handler(void);

void i2cInit(i2c_t *i2c,
             I2C_HandleTypeDef *hi2c,
             I2C_TypeDef *i2c_instance,
             uint8_t address)
{
    assert_param(i2c != NULL);
    assert_param(hi2c != NULL);
    assert_param(i2c_instance != NULL);

    i2c->hi2c = hi2c;
    i2c->address = address;

    i2c->hi2c->Instance = i2c_instance;
    i2c->hi2c->Init.ClockSpeed = 100000;
    i2c->hi2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
    i2c->hi2c->Init.OwnAddress1 = 0;
    i2c->hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2c->hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2c->hi2c->Init.OwnAddress2 = 0;
    i2c->hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c->hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(i2c->hi2c) != HAL_OK)
    {
        Error_Handler();
    }

}

i2c_status_t i2cTransmit(i2c_t *i2c,
                         uint8_t *data,
                         uint16_t size)
{
    assert_param(i2c != NULL);
    assert_param(data != NULL);

    HAL_StatusTypeDef transmit_result = HAL_I2C_Master_Transmit(i2c->hi2c,
                                                                i2c->address << 1,
                                                                data,
                                                                size,
                                                                HAL_MAX_DELAY);
    if (transmit_result != HAL_OK)
    {
        return I2C_STATUS_ERROR;
    }
    return I2C_STATUS_OK;
}

