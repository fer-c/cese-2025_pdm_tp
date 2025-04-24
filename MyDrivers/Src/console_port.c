/*
 * console_port.c
 *
 *  Created on: Apr 22, 2025
 *      Author: fcoronel
 */


#include "console_port.h"

void consolePortInit(console_port_t *port,
                        uart_t *uart)
{
    assert_param(port != NULL);
    assert_param(uart != NULL);

    port->uart = uart;  // Inicializa el UART
}

void consolePortClearScreen(console_port_t *port)
{
    assert_param(port != NULL);

    uartSendClearScreen(port->uart);  // Borra la pantalla
}

void consolePortSendConfiguration(console_port_t *port)
{
    assert_param(port != NULL);

    uartSendConfiguration(port->uart);  // Envía la configuración del UART
}

void consolePortReceiveStringSize(console_port_t *port,
                        uint8_t *text,
                        uint8_t size)
{
    assert_param(port != NULL);
    assert_param(text != NULL);
    assert_param(size > 0);

    uartReceiveStringSize(port->uart, text, size);  // Recibe el comando por UART
}


void consolePortSendStringSize(console_port_t *port,
                        uint8_t *text,
                        uint8_t size)
{
    assert_param(port != NULL);
    assert_param(text != NULL);
    assert_param(size > 0);

    uartSendStringSize(port->uart, text, size);  // Envía el comando por UART
}

void consolePortSendString(console_port_t *port,
                        uint8_t *text)
{
    assert_param(port != NULL);
    assert_param(text != NULL);

    uartSendString(port->uart, text);  // Envía el comando por UART
}

