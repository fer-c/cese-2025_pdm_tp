/*
 * app.c
 *
 *  Created on: Apr 18, 2025
 *      Author: fcoronel
 */

#include "app.h"
#include "main.h"

extern UART_HandleTypeDef huart2; /** Estructura para el UART. */
extern SPI_HandleTypeDef hspi1; /** Estructura para el SPI. */
extern I2C_HandleTypeDef hi2c1; /** Estructura para el I2C. */

static led_manager_t led_manager; /**< @brief Estructura para el manager de LEDs. */

void appInit(void)
{
    static uart_t uart; /* Estructura para el UART. */

    static spi_t spi; /* Estructura para el SPI. */
    static led_matrix_port_t led_matrix_port; /* Estructura para el puerto SPI del LED Matrix. */
    static led_matrix_t led_matrix; /* Estructura para la matriz de LEDs. */

    static i2c_t i2c; /* Estructura para el I2C. */
    static lcd_port_t lcd_port; /* Estructura para el puerto I2C del LCD. */
    static lcd_t lcd; /* Estructura para el LCD. */

    static console_port_t console_port; /* Estructura para el puerto de la consola. */
    static console_t console; /* Estructura para el UART. */


    // Inicializa el UART
    uartInit(&uart, &huart2, USART2);

    // Inicializa el SPI
    spiInit(&spi, &hspi1, SPI1, SPI1_CS_GPIO_Port, SPI1_CS_Pin, SPI_DEFAULT_CONFIG);

    // Inicializa el I2C
    i2cInit(&i2c, &hi2c1, I2C1, LCD_I2C_DIR);  // Dirección del dispositivo I2C

    // Inicializa el Led Matrix
    ledMatrixPortInit(&led_matrix_port, &spi);  // Inicializa el puerto SPI del LED Matrix
    ledMatrixInit(&led_matrix, &led_matrix_port, LED_ROWS);  // Inicializa la matriz de LEDs

    // Inicializa el LCD
    lcdPortInit(&lcd_port, &i2c);  // Inicializa el puerto I2C del LCD
    lcdInit(&lcd, &lcd_port, LCD_ROWS);  // Inicializa el LCD con 2 filas

    // Inicializa la consola UART
    consolePortInit(&console_port, &uart);  // Inicializa el puerto UART
    consoleInit(&console, &console_port);  // Inicializa el UART para la consola

    // Apagamos el LED interno
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);  // Apaga el LED de depuración

    // Inicializa el manager de LEDs
    ledManagerInit(&led_manager, &led_matrix, &lcd, &console);  // Inicializa el manager de LEDs
}

void appLoop(void)
{
    ledManagerUpdate(&led_manager);  // Actualiza el manager de LEDs
}

