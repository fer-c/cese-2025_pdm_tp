/*
 * lcd.c
 *
 *  Created on: Apr 19, 2025
 *      Author: fcoronel
 */

#include "lcd.h"

//Bits de ENABLE y BACK LIGHT
#define EN (1<<2)
#define BL (1<<3)

//SEÑALES DE CONTROL
#define CLR_LCD 1
#define RETURN_HOME (1<<1)
#define ENTRY_MODE (1<<2)
#define DISPLAY_CONTROL (1<<3)
#define CURSOR_DISPLAY_SHIFT (1<<4)
#define FUNTION_SET (1<<5)
#define SET_CGRAM (1<<6)
#define SET_DDRAM (1<<7)
/************************************/
#define DISPLAY_ON (1<<2)
#define CURSOR_ON (1<<1)
#define CURSOR_BLINK 1
#define AUTOINCREMENT (1<<1)
#define _4BIT_MODE 0x28

//DEMORAS NECESARIAS

#define DELAY20ms 20
#define DELAY10ms 10
#define DELAY2ms  2
#define DELAY1ms  1
#define DelayTime 1

//MANEJO DE NIBBLES
#define HIGH_NIBBLE 0xf0
#define LOW_NIBBLE 4

//LINEAS DEL LCD

#define MAX_ROWS 4
#define MAX_COLS 20
#define ADDR_CMD 0x80
#define LINEA1 0x00
#define LINEA2 0x40
#define LINEA3 0x14
#define LINEA4 0x54

static uint8_t ROW_IDX[] = { LINEA1, LINEA2, LINEA3, LINEA4 };
static uint8_t EMPTY_LINE[MAX_COLS] = "                    ";

//COMANDOS DE INICIALIZACIÓN
#define COMANDO_INI1 0x30
#define COMANDO_INI2 0x20

/**
 * @brief tipos de señales que se envían al controlador i2c del LSC.
 */
typedef enum _tipo_transmission_t
{
    DATOS = 1, /**< Transmisión de datos */
    CONTROL = 0 /**< Transmisión de control */
} tipo_transmission_t;

static void _lcdDelay(lcd_t *lcd,
                      uint32_t demora);
static void _lcdTransmit8bits(lcd_t *lcd,
                              uint8_t valor,
                              tipo_transmission_t tipo);
static void _lcdTransmit4bits(lcd_t *lcd,
                              uint8_t valor,
                              tipo_transmission_t tipo);

static const uint8_t LCD_INIT_CMD[] = {
        _4BIT_MODE,  // Seteamos el modo de 4 bits
        DISPLAY_CONTROL,  // Seteamos el modo de display
        RETURN_HOME,  // Regresamos a la posición inicial
        ENTRY_MODE + AUTOINCREMENT,  // Seteamos el modo de entrada auto incrementable
        DISPLAY_CONTROL + DISPLAY_ON,  // Seteamos el modo de display encendido
        CLR_LCD };  // Seteamos el modo de limpiar el display

void lcdInit(lcd_t *lcd,
             lcd_port_t *port,
             uint8_t rows)
{
    assert_param(lcd != NULL);
    assert_param(port != NULL);
    assert_param(rows <= MAX_ROWS);

    lcd->port = port;
    lcd->rows = rows;
}

lcd_status_t lcdInitialize(lcd_t *lcd)
{
    _lcdDelay(lcd, DELAY20ms);
    _lcdTransmit4bits(lcd, COMANDO_INI1, CONTROL);
    _lcdDelay(lcd, DELAY10ms);
    _lcdTransmit4bits(lcd, COMANDO_INI1, CONTROL);
    _lcdDelay(lcd, DELAY1ms);
    _lcdTransmit4bits(lcd, COMANDO_INI1, CONTROL);
    _lcdTransmit4bits(lcd, COMANDO_INI2, CONTROL);
    for (uint8_t i = 0; i < sizeof(LCD_INIT_CMD); i++)
    {
        _lcdTransmit8bits(lcd, LCD_INIT_CMD[i], CONTROL);
    }
    _lcdDelay(lcd, DELAY2ms);
    return LCD_OK;
}

void lcdPrintValue(lcd_t *lcd,
                   uint8_t dato)
{
    _lcdTransmit8bits(lcd, dato, DATOS);
}

void lcdPrintAscii(lcd_t *lcd,
                   uint8_t dato)
{
    _lcdTransmit8bits(lcd, dato + '0', DATOS);
}

void lcdPrintValueBCD(lcd_t *lcd,
                      uint8_t dato)
{
    uint8_t decena = ((dato) & 0xf0) >> 4;
    uint8_t unidad = (dato) & 0x0f;
    lcdPrintAscii(lcd, decena);
    lcdPrintAscii(lcd, unidad);

}

void lcdPrintString(lcd_t *lcd,
                    uint8_t *texto)
{
    while (*texto)
    {
        lcdPrintValue(lcd, *texto++);
    }
}

void lcdPrintLine(lcd_t *lcd,
                  uint8_t row,
                  uint8_t *texto)
{
    assert_param(lcd != NULL);
    assert_param(row < lcd->rows);

    lcdClrLine(lcd, row);
    lcdSetPosition(lcd, row, 0);
    lcdPrintString(lcd, texto);
}

void lcdClr(lcd_t *lcd)
{
    _lcdTransmit8bits(lcd, CLR_LCD, CONTROL);  //  Display Clear.
    _lcdDelay(lcd, DELAY2ms);

}

void lcdClrLine(lcd_t *lcd,
                    uint8_t row)
{
    assert_param(lcd != NULL);
    assert_param(row < lcd->rows);

    lcdSetPosition(lcd, row, 0);
    lcdPrintString(lcd, EMPTY_LINE);
}

void lcdSetPosition(lcd_t *lcd,
                    uint8_t row,
                    uint8_t col)
{
    assert_param(lcd != NULL);
    assert_param(row < lcd->rows);

    uint8_t pos = ROW_IDX[row] + col;

    _lcdTransmit8bits(lcd, ADDR_CMD | pos, CONTROL);
}

void lcdSetCursorOff(lcd_t *lcd)
{
    _lcdTransmit8bits(lcd, DISPLAY_CONTROL + DISPLAY_ON, CONTROL);
}

void lcdSetCursorOn(lcd_t *lcd)
{
    _lcdTransmit8bits(lcd, DISPLAY_CONTROL + CURSOR_ON + DISPLAY_ON + CURSOR_BLINK, CONTROL);
}

// Private functions

/**
 * @brief  _lcdTransmit8bits Función que parte el envio de 1 byte en nible alto y bajo para el trabajo en 4 bits
 * @param  uint8_t valor a enviar
 * @param uint8_t tipo CONTROL o DATOS
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
void _lcdTransmit8bits(lcd_t *lcd,
                       uint8_t valor,
                       tipo_transmission_t tipo)
{
    _lcdTransmit4bits(lcd, valor & HIGH_NIBBLE, tipo);  //me con quedo y envio los 4 bits más significaticos.
    _lcdTransmit4bits(lcd, valor << LOW_NIBBLE, tipo);  //me quedo y envio los 4 bits menos significativos.
}

/**
 * @brief  _lcdTransmit4bits Función que parte el envio de 4 bits
 * @param  uint8_t valor a enviar
 * @param uint8_t tipo CONTROL o DATOS
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
static void _lcdTransmit4bits(lcd_t *lcd,
                              uint8_t valor,
                              tipo_transmission_t tipo)
{
    lcdPortWriteByte(lcd->port, valor + tipo + EN + BL);
    _lcdDelay(lcd, DelayTime);
    lcdPortWriteByte(lcd->port, valor + tipo + BL);
    _lcdDelay(lcd, DelayTime);
}

/**
 * @brief  _lcdDelay demora bloqueante para el uso del LCD
 * @param  valor de la demora a realizar en ms
 * @return void
 * @author Ing. Pavelek Israel
 * @version 1.0
 * @date 16/4/2023
 */
static void _lcdDelay(lcd_t *lcd,
                      uint32_t demora)
{
    HAL_Delay(demora);
}
