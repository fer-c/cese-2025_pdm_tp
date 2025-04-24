/*
 * led_manager.h
 *
 *  Created on: Apr 21, 2025
 *      Author: fcoronel
 */

#ifndef INC_LED_MANAGER_H_
#define INC_LED_MANAGER_H_

#include "led_matrix.h"
#include "lcd.h"
#include "console.h"
#include "API_delay.h"
#include "API_stdtypes.h"

#define T_100MS 100 /**< @brief Duración de 100 ms. */
#define T_200MS 200 /**< @brief Duración de 200 ms. */
#define T_500MS 500 /**< @brief Duración de 500 ms. */
#define T_1S 1000 /**< @brief Duración de 1 segundo. */

#define CMD_SIZE 10 /**< @brief Tamaño del comando. */

#define NO_CMD 0 /**< @brief Comando no reconocido. */

#define LCD_LINEA_DELAY 0 /**< @brief Línea superior del LCD. */
#define LCD_LINEA_COLOR_SUP 1 /**< @brief Línea del medio alta del LCD. */
#define LCD_LINEA_COLOR_INF 2 /**< @brief Línea del medio baja del LCD. */
#define LCD_LINEA_INFO 3 /**< @brief Línea inferior del LCD. */


#define MANAGER_STATE_COLOR_VALUE    0b0000 /**< @brief Indica que ambos leds estan con color */

#define MANAGER_STATE_SUP_AUTO_VALUE 0b1100 /**< @brief Mascara de valor auto para los leds superiores. */
#define MANAGER_STATE_SUP_AUTO_RESET 0b0011 /**< @brief Mascara de reset auto para los leds superiores. */

#define MANAGER_STATE_INF_AUTO_VALUE 0b0011 /**< @brief Mascara de valor auto para los leds inferiores. */
#define MANAGER_STATE_INF_AUTO_RESET 0b1100 /**< @brief Mascara de reset auto para los leds inferiores. */

#define MANAGER_STATE_INIT_VALUE     0xF0       /**< @brief Mascara de reset para el estado inicial manager. */
#define MANAGER_STATE_INIT_RESET     0x0F       /**< @brief Mascara de reset para el estado inicial manager. */


/**
 * @brief Estructura estados para el manager de LEDs.
 */
typedef enum
{
    MANAGER_STATE_INIT 					= MANAGER_STATE_INIT_VALUE, /**< @brief Estado inicial del manager. */
    MANAGER_STATE_SUP_COLOR_INF_COLOR 	= MANAGER_STATE_COLOR_VALUE, /**< @brief Estado de color en ambos . */
    MANAGER_STATE_SUP_AUTO_INF_COLOR 	= MANAGER_STATE_SUP_AUTO_VALUE, /**< @brief Estado de auto superior y color inferior. */
    MANAGER_STATE_SUP_COLOR_INF_AUTO 	= MANAGER_STATE_INF_AUTO_VALUE, /**< @brief Estado de color superior y auto inferior. */
    MANAGER_STATE_SUP_AUTO_INF_AUTO 	= MANAGER_STATE_SUP_AUTO_VALUE | MANAGER_STATE_INF_AUTO_VALUE /**< @brief Estado de auto superior y auto inferior. */
} manager_state_t;

/**
 * @brief  Estructura para el manager de LEDs.
 */
typedef struct
{
    manager_state_t state; /* Estado del manager. */
    tick_t duration; /* Duración del delay. */
    led_matrix_t *led_matrix; /* Estructura para la matriz de LEDs. */
    lcd_t *lcd; /* Estructura para el LCD. */
    delay_t delay; /* Delay para el LED. */
    console_t *console; /* Estructura para el UART. */
    pixel_t pixel_sup; /* Pixel para el LED Sup. */
    pixel_t pixel_inf; /* Pixel para el LED Inf. */
} led_manager_t;

/**
 * @brief  Inicializa el manager de LEDs.
 * @param  manager Puntero a la estructura led_manager_t.
 * @param  led_matrix Puntero a la estructura led_matrix_t.
 * @param  lcd Puntero a la estructura lcd_t.
 * @param  console Puntero a la estructura console_t.
 * @retval None
 */
void ledManagerInit(led_manager_t *manager,
                    led_matrix_t *led_matrix,
                    lcd_t *lcd,
                    console_t *console);

/**
 * @brief  Actualiza el manager de LEDs.
 * @param  manager Puntero a la estructura led_manager_t.
 * @retval None
 */
void ledManagerUpdate(led_manager_t *manager);

/**
 * @brief  Procesa el comando recibido por la consola UART.
 * @param  manager: Estructura del manager de LEDs.
 * @param  cmd: Comando recibido.
 *
 * @return None
 */
void processCommand(led_manager_t *manager, uint8_t cmd);

/**
 * @brief  Actualiza el delay del manager de LEDs.
 * @param  manager: Estructura del manager de LEDs.
 * @param  delay: Nuevo delay a establecer.
 * @return None
 */
void ledManagerUpdateDelayCmd(led_manager_t *manager, tick_t delay);

/**
 * @brief  Actualiza el estado del manager de LEDs en modo automatico.
 * @param  manager: Estructura del manager de LEDs.
 * @return None
 */
void letManagerUpdateStateAutoCmd(led_manager_t *manager, uint8_t state);

/**
 * @brief  Actualiza el estado del manager de LEDs en modo automatico.
 * @param  manager: Estructura del manager de LEDs.
 * @return None
 */
void letManagerUpdateStateColorCmd(led_manager_t *manager, bool_t inf);

/**
 * @brief  Muestra el estado del manager de LEDs en el LCD y UART.
 * @param  manager: Estructura del manager de LEDs.
 * @param  inf: Indica si es el LED inferior o superior.
 * @param  color_text: Texto del color.
 * @param  pixel: Pixel a mostrar.
 * @return None
 */
void ledManagerShowState(led_manager_t *manager, bool_t inf, char *color_text,
		pixel_t pixel);


#endif /* INC_LED_MANAGER_H_ */
