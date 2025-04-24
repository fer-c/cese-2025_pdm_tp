/*
 * lcd.h
 *
 *  Created on: Apr 19, 2025
 *      Author: fcoronel
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "lcd_port.h"
#include "API_stdtypes.h"

/**
 * @brief Enumerado de respuestas de los comandos.
 * - LCD_OK: Operación completada con éxito
 * - LCD_ERROR: Operación fallida
 */
typedef enum
{
    LCD_OK = 0x00U,
    LCD_ERROR = 0x01U,
} lcd_status_t;

/**
 * @brief Estructura de LCD.
 */
typedef struct
{
    lcd_port_t *port; /**< Puntero al puerto I2C del LCD */
    uint8_t rows; /**< Número de filas del LCD */
} lcd_t;

/**
 * @brief Inicializa la estructura del LCD.
 * @param lcd Puntero a la estructura lcd_t.
 * @param port Puntero al puerto I2C del LCD.
 * @param rows Número de filas del LCD.
 */
void lcdInit(lcd_t *lcd,
             lcd_port_t *port,
             uint8_t rows);

/**
 * @brief Inicializa el LCD.
 * @param lcd Puntero a la estructura lcd_t.
 * @return LCD_OK o LCD_ERROR
 */
lcd_status_t lcdInitialize(lcd_t *lcd);

/**
 * @brief  lcdPrintString Funcion que envia un texto al LCD
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @param  texto puntero a un string a enviar
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void lcdPrintString(lcd_t *lcd,
                    uint8_t *texto);

/**
 * @brief lcdPrintLine imprime una linea en el LCD
 * @param lcd_t *lcd puntero a la estructura lcd_t
 * @param row uint8_t fila a imprimir
 * @param texto puntero a un string a enviar
 * @return void
 */
void lcdPrintLine(lcd_t *lcd,
                  uint8_t row,
                  uint8_t *texto);

/**
 * @brief  lcdPrintAscii envia una palabra de DATOS al lcd
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @param  value uint8_t valor de datos a enviar previo a su conversion en ASCII
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void lcdPrintAscii(lcd_t *lcd,
                   uint8_t value);

/**
 * @brief  lcdPrintValue envia una palabra de DATOS al lcd
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @param  value uint8_t valor de datos a enviar
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void lcdPrintValue(lcd_t *lcd,
                   uint8_t value);

/**
 * @brief  lcdPrintValueBCD envia una palabra de DATOS al lcd
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @param  value uint8_t valor de datos a enviar previo a su conversion en BCD
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void lcdPrintValueBCD(lcd_t *lcd,
                      uint8_t value);

/**
 * @brief  lcdClr Funcion que borra el LCD
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void lcdClr(lcd_t *lcd);

/**
 * @brief  lcdClrLine Funcion que borra una linea del LCD
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @param  row uint8_t fila a borrar
 * @return void
 * @version 1.0
 * @date 21/4/2025
 * @author Ing. Fernando Coronel
 */
void lcdClrLine(lcd_t *lcd,
           uint8_t row);

/**
 * @brief  lcdSetCursorOff Funcion que apaga el cursor del LCD
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void lcdSetCursorOff(lcd_t *lcd);

/**
 * @brief  lcdSetCursorOn Funcion que prende el cursor del LCD
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void lcdSetCursorOn(lcd_t *lcd);

/**
 * @brief  lcdSetPosition Función que posiciona el cursor del LCD.
 * @param  lcd_t *lcd puntero a la estructura lcd_t
 * @param  row uint8_t un valor de 0 a lo alto de la pantalla
 * @param  col uint8_t un valor de 0 a la longitud de la pantalla
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void lcdSetPosition(lcd_t *lcd,
                    uint8_t row,
                    uint8_t col);

#endif /* INC_LCD_H_ */
