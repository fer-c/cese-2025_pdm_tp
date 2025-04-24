/*
 * API_spi.c
 *
 *  Created on: Apr 15, 2025
 *      Author: fcoronel
 */

#include "API_spi.h"

extern void Error_Handler(void);  // Global Error_Handler

void spiInit(spi_t *spi,
             SPI_HandleTypeDef *hspi,
             SPI_TypeDef *instance,
             GPIO_TypeDef *cs_port,
             uint16_t cs_pin,
             spi_config_t *config)
{
    spi->hspi = hspi;
    spi->cs_port = cs_port;
    spi->cs_pin = cs_pin;
    spi->config = config;

    spi->hspi->Instance = instance;
    spi->hspi->Init.Mode = config->mode;
    spi->hspi->Init.Direction = SPI_DIRECTION_2LINES;
    spi->hspi->Init.DataSize = SPI_DATASIZE_8BIT;
    spi->hspi->Init.CLKPolarity = config->polarity;
    spi->hspi->Init.CLKPhase = config->phase;
    spi->hspi->Init.NSS = SPI_NSS_SOFT;
    spi->hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    spi->hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi->hspi->Init.TIMode = SPI_TIMODE_DISABLE;
    spi->hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi->hspi->Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(spi->hspi) != HAL_OK)
    {
        Error_Handler();
    }
    spiPortChipSelectStop(spi);
}

void spiPortChipSelectStart(spi_t *spi)
{
    HAL_GPIO_WritePin(spi->cs_port, spi->cs_pin, GPIO_PIN_RESET);  // Set NSS low
}

void spiPortChipSelectStop(spi_t *spi)
{
    HAL_GPIO_WritePin(spi->cs_port, spi->cs_pin, GPIO_PIN_SET);  // Set NSS high
}

spi_status_t spiTransmit(spi_t *spi,
                         uint8_t *data,
                         uint16_t size)
{

    spiPortChipSelectStart(spi);

    HAL_StatusTypeDef result = HAL_SPI_Transmit(spi->hspi, data, size, HAL_MAX_DELAY);

    spiPortChipSelectStop(spi);

    return (result == HAL_OK) ? SPI_OK : SPI_ERROR;
}

spi_status_t spiReceive(spi_t *spi,
                        uint8_t *data,
                        uint16_t size)
{

    spiPortChipSelectStart(spi);

    HAL_StatusTypeDef result = HAL_SPI_Receive(spi->hspi, data, size, HAL_MAX_DELAY);

    spiPortChipSelectStop(spi);

    return (result == HAL_OK) ? SPI_OK : SPI_ERROR;
}

spi_status_t spiTransmitReceive(spi_t *spi,
                                uint8_t *txData,
                                uint8_t *rxData,
                                uint16_t size)
{
    spiPortChipSelectStart(spi);

    HAL_StatusTypeDef result = HAL_SPI_TransmitReceive(spi->hspi, txData, rxData, size,
    HAL_MAX_DELAY);

    spiPortChipSelectStop(spi);

    return (result == HAL_OK) ? SPI_OK : SPI_ERROR;
}

