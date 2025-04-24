/*
 * app.h
 *
 *  Created on: Apr 18, 2025
 *      Author: fcoronel
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "led_manager.h"
#include "API_delay.h"
#include "API_i2c.h"
#include "API_spi.h"
#include "API_stdtypes.h"
#include "API_uart.h"

/**
 * @brief  Dirección del dispositivo I2C del LCD.
 */
#define LCD_I2C_DIR 0x27

/**
 * @brief  Número de filas del LCD
 */
#define LCD_ROWS 4

/**
 * @brief  Número de filas del LED Matrix
 */
#define LED_ROWS 2

/**
 * @brief  Inicializa la aplicación.
 */
void appInit(void);

/**
 * @brief  Loop principal de la aplicación.
 */
void appLoop(void);

#endif /* INC_APP_H_ */
