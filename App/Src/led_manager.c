/*
 * led_manager.c
 *
 *  Created on: Apr 21, 2025
 *      Author: fcoronel
 */

#include "led_manager.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief  Inicializa el manager de LEDs, imprimiendo en el LCD y UART la configuración inicial.
 * @param  manager: Estructura del manager de LEDs.
 * @return None
 */
static void ledManagerInitialize(led_manager_t *manager);

void ledManagerInit(led_manager_t *manager, led_matrix_t *led_matrix,
		lcd_t *lcd, console_t *console) {
	assert_param(manager != NULL);
	assert_param(led_matrix != NULL);
	assert_param(lcd != NULL);
	assert_param(console != NULL);

	manager->led_matrix = led_matrix;  // Inicializa la matriz de LEDs
	manager->lcd = lcd;  // Inicializa el LCD
	manager->console = console;  // Inicializa el UART
	manager->state = MANAGER_STATE_INIT;  // Inicializa el estado del manager
	manager->duration = T_100MS;

	lcdInitialize(manager->lcd);  // Inicializa el LCD

	ledManagerInitialize(manager);
}

void ledManagerUpdate(led_manager_t *manager) {
	static uint8_t cmd = 0;
	static uint8_t last_cmd = 0;

	assert_param(manager != NULL);

	console_status_t status = consoleReadCommand(manager->console, &cmd); // Lee el comando del UART

	if (status == CONSOLE_STATUS_OK && cmd != NO_CMD) {
		last_cmd = cmd;  // Guarda el último comando
		cmd = NO_CMD;  // Limpiar el comando
	}

	if (delayRead(&manager->delay)) {
		processCommand(manager, last_cmd); // Procesa el último comando
		last_cmd = NO_CMD;  // Limpiar el comando
		switch (manager->state) {
		case MANAGER_STATE_INIT:
		case MANAGER_STATE_SUP_COLOR_INF_COLOR:
			break;
		case MANAGER_STATE_SUP_AUTO_INF_AUTO:
			ledMatrixSetPixel(manager->led_matrix, LED_LINEA_SUP,
					PIXEL_AUTO);
			ledMatrixSetPixel(manager->led_matrix, LED_LINEA_INF,
					PIXEL_AUTO);
			break;
		case MANAGER_STATE_SUP_COLOR_INF_AUTO:
			ledMatrixSetPixel(manager->led_matrix, LED_LINEA_INF,
					PIXEL_AUTO);
			break;
		case MANAGER_STATE_SUP_AUTO_INF_COLOR:
			ledMatrixSetPixel(manager->led_matrix, LED_LINEA_SUP,
					PIXEL_AUTO);
			break;
		default:
			ledManagerInitialize(manager);
			break;
		}

		ledMatrixToggle(manager->led_matrix);
		delayWrite(&manager->delay, manager->duration); // Cambia la duración del delay
	}
}

// Funciones auxiliares


void processCommand(led_manager_t *manager, uint8_t cmd) {
	switch (cmd) {
	case 'h':
	case 'H':
		consoleClearScreen(manager->console);  // Borra la pantalla
		consoleSendConfiguration(manager->console); // Envía la configuración del UART
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		ledManagerUpdateDelayCmd(manager, (cmd - '0') * T_100MS); // Actualiza el delay
		break;
	case '0':
		ledManagerUpdateDelayCmd(manager, T_1S);  // Actualiza el delay
		break;
	case 'A':
		letManagerUpdateStateAutoCmd(manager, MANAGER_STATE_SUP_AUTO_VALUE);
		ledManagerShowState(manager, false, "AUTO", PIXEL_AUTO);

		break;
	case 'a':
		letManagerUpdateStateAutoCmd(manager, MANAGER_STATE_INF_AUTO_VALUE);
		ledManagerShowState(manager, true, "AUTO", PIXEL_AUTO);

		break;
	case 'R':
		letManagerUpdateStateColorCmd(manager, false);
		ledManagerShowState(manager, false, "ROJO", PIXEL_RED);

		break;
	case 'r':
		letManagerUpdateStateColorCmd(manager, true);
		ledManagerShowState(manager, true, "ROJO", PIXEL_RED);

		break;
	case 'G':
		letManagerUpdateStateColorCmd(manager, false);
		ledManagerShowState(manager, false, "VERDE", PIXEL_GREEN);

		break;
	case 'g':
		letManagerUpdateStateColorCmd(manager, true);
		ledManagerShowState(manager, true, "VERDE", PIXEL_GREEN);

		break;
	case 'B':
		letManagerUpdateStateColorCmd(manager, false);
		ledManagerShowState(manager, false, "AZUL", PIXEL_BLUE);

		break;
	case 'b':
		letManagerUpdateStateColorCmd(manager, true);
		ledManagerShowState(manager, true, "AZUL", PIXEL_BLUE);

		break;
	case 'Y':
		letManagerUpdateStateColorCmd(manager, false);
		ledManagerShowState(manager, false, "AMARILLO", PIXEL_YELLOW);

		break;
	case 'y':
		letManagerUpdateStateColorCmd(manager, true);
		ledManagerShowState(manager, true, "AMARILLO", PIXEL_YELLOW);

		break;
	case 'M':
		letManagerUpdateStateColorCmd(manager, false);
		ledManagerShowState(manager, false, "MAGENTA", PIXEL_MAGENTA);

		break;
	case 'm':
		letManagerUpdateStateColorCmd(manager, true);
		ledManagerShowState(manager, true, "MAGENTA", PIXEL_MAGENTA);

		break;
	case 'C':
		letManagerUpdateStateColorCmd(manager, false);
		ledManagerShowState(manager, false, "CYAN", PIXEL_CYAN);

		break;
	case 'c':
		letManagerUpdateStateColorCmd(manager, true);
		ledManagerShowState(manager, true, "CYAN", PIXEL_CYAN);

		break;
	case 'W':
		letManagerUpdateStateColorCmd(manager, false);
		ledManagerShowState(manager, false, "BLANCO", PIXEL_WHITE);

		break;
	case 'w':
		letManagerUpdateStateColorCmd(manager, true);
		ledManagerShowState(manager, true, "BLANCO", PIXEL_WHITE);

		break;
	case 'O':
		letManagerUpdateStateColorCmd(manager, false);
		ledManagerShowState(manager, false, "APAGADO", PIXEL_OFF);

		break;
	case 'o':
		letManagerUpdateStateColorCmd(manager, true);
		ledManagerShowState(manager, true, "APAGADO", PIXEL_OFF);

		break;

	default:
		cmd = NO_CMD;  // Comando no reconocido
	}
	if (cmd != NO_CMD) {
		lcdSetCursorOff(manager->lcd);
		lcdSetPosition(manager->lcd, LCD_LINEA_INFO, 9);
		lcdPrintValue(manager->lcd, cmd);
	}
}

void ledManagerUpdateDelayCmd(led_manager_t *manager, tick_t delay) {
	static char text[50];
	assert_param(manager != NULL);
	assert_param(delay > 0);

	manager->duration = delay;  // Actualiza la duración del delay
	if (delay > T_1S) {
		sprintf(text, "Delay: %lu s", delay / T_1S);
	} else {
		sprintf(text, "Delay: %lu ms", delay);
	}
	lcdPrintLine(manager->lcd, LCD_LINEA_DELAY, (uint8_t*) text);
	consolePrintLine(manager->console, (uint8_t*) text);
}

void letManagerUpdateStateAutoCmd(led_manager_t *manager, uint8_t state) {
	assert_param(manager != NULL);
	uint8_t base = (manager->state & MANAGER_STATE_INIT_RESET);
	manager->state = base | state;  // Actualiza el estado del manager
}

void letManagerUpdateStateColorCmd(led_manager_t *manager, bool_t inf) {
	assert_param(manager != NULL);

	uint8_t state;
	if (inf) {
		state = MANAGER_STATE_INF_AUTO_RESET;
	} else {
		state = MANAGER_STATE_SUP_AUTO_RESET;
	}

	uint8_t base = (manager->state & MANAGER_STATE_INIT_RESET);
	manager->state = base & state;  // Actualiza el estado del manager
}


void ledManagerShowState(led_manager_t *manager, bool_t inf, char *color_text,
		pixel_t pixel) {
	static char text[50];
	uint8_t lcd_linea;
	uint8_t led_linea;
	if (inf) {
		sprintf((char*) text, "Inferior: %s", color_text);
		lcd_linea = LCD_LINEA_COLOR_INF;
		led_linea = LED_LINEA_INF;
	} else {
		sprintf((char*) text, "Superior: %s", color_text);
		lcd_linea = LCD_LINEA_COLOR_SUP;
		led_linea = LED_LINEA_SUP;
	}
	lcdPrintLine(manager->lcd, lcd_linea, (uint8_t*) text);
	consolePrintLine(manager->console, (uint8_t*) text);
	ledMatrixSetPixel(manager->led_matrix, led_linea, pixel);

}

static void ledManagerInitialize(led_manager_t *manager) {
	delayInit(&manager->delay, manager->duration);
	ledMatrixInitialize(manager->led_matrix);
	lcdPrintLine(manager->lcd, LCD_LINEA_DELAY, (uint8_t*) "Delay: 100 ms");
	lcdPrintLine(manager->lcd, LCD_LINEA_COLOR_SUP,
			(uint8_t*) "Superior: APAGADO");
	lcdPrintLine(manager->lcd, LCD_LINEA_COLOR_INF,
			(uint8_t*) "Inferior: APAGADO");
	lcdPrintLine(manager->lcd, LCD_LINEA_INFO, (uint8_t*) "Comando: ");
	lcdSetPosition(manager->lcd, LCD_LINEA_INFO, 9);
	lcdSetCursorOn(manager->lcd);
	manager->pixel_sup = PIXEL_OFF;
	manager->pixel_inf = PIXEL_OFF;
}
