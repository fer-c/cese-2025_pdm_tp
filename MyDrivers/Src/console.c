/*
 * console.c
 *
 *  Created on: Apr 21, 2025
 *      Author: fcoronel
 */

#include "console.h"

console_status_t consoleInit(console_t *console,
                             console_port_t *port)
{
    assert_param(console != NULL);
    assert_param(port != NULL);

    console->port = port;  // Inicializa el UART

    return CONSOLE_STATUS_OK;  // Devuelve el estado OK
}

console_status_t consoleClearScreen(console_t *console)
{
    consolePortClearScreen(console->port);  // Borra la pantalla
    return CONSOLE_STATUS_OK;  // Devuelve el estado OK
}

console_status_t consoleSendConfiguration(console_t *console)
{
    consolePortSendConfiguration(console->port);  // Envía la configuración del UART
    return CONSOLE_STATUS_OK;  // Devuelve el estado OK
}

console_status_t consoleReadCommand(console_t *console,
                                    uint8_t *cmd)
{
    return consoleRead(console, cmd, 1);  // Lee un comando del UART
}

console_status_t consoleRead(console_t *console,
                             uint8_t *text,
                             uint8_t size)
{
    consolePortReceiveStringSize(console->port, text, size);  // Recibe el comando por UART
    return CONSOLE_STATUS_OK;  // Devuelve el estado OK
}

console_status_t consoleWrite(console_t *console,
                              uint8_t *text,
                              uint8_t size)
{
    consolePortSendStringSize(console->port, text, size);  // Envía el comando por UART
    return CONSOLE_STATUS_OK;  // Devuelve el estado OK
}

console_status_t consolePrintLine(console_t *console,
                                  uint8_t *text)
{
    consolePortSendString(console->port, text);  // Envía el comando por UART
    consolePortSendString(console->port, (uint8_t*) "\r\n");  // Envía un salto de línea
    return CONSOLE_STATUS_OK;  // Devuelve el estado OK
}
