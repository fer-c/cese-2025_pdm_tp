/*
 * API_spi.h
 *
 *  Created on: Apr 15, 2025
 *      Author: fcoronel
 */

#ifndef INC_API_SPI_H_
#define INC_API_SPI_H_

#include "stm32f4xx_hal.h"
#include "API_stdtypes.h"

/**
 * @brief SPI status:
 * - SPI_OK: Operation completed successfully
 * - SPI_ERROR: Operation failed
 */
typedef enum
{
    SPI_OK = 0,
    SPI_ERROR = 1,
} spi_status_t;

/**
 * @brief SPI port structure
 * - hspi: Pointer to the SPI handle
 * - nss_port: GPIO port for the NSS pin
 * - nss_pin: GPIO pin number for the NSS pin
 */
typedef enum
{
    SPI_LOW = SPI_POLARITY_LOW,
    SPI_HIGH = SPI_POLARITY_HIGH,
} spi_polarity_t;

/**
 * @brief SPI clock polarity:
 * - SPI_LOW: Clock idle state is low
 * - SPI_HIGH: Clock idle state is high
 */
typedef enum
{
    SPI_CPHA_1EDGE = SPI_PHASE_1EDGE,
    SPI_CPHASE_2EDGE = SPI_PHASE_2EDGE,
} spi_phase_t;

/**
 * @brief SPI bit order:
 *  - MSB_FIRST: Most Significant Bit first
 *  - LSB_FIRST: Least Significant Bit first
 */
typedef enum
{
    SPI_MSB_FIRST = SPI_FIRSTBIT_MSB,
    SPI_LSB_FIRST = SPI_FIRSTBIT_LSB,
} spi_bit_order_t;

/**
 * @brief SPI modes:
 * - SPI_MODE_MASTER: Master mode
 * - SPI_MODE_SLAVE: Slave mode
 */
typedef enum
{
    SPI_MASTER = SPI_MODE_MASTER,
    SPI_SLAVE = SPI_MODE_SLAVE,
} spi_mode_t;

/**
 * @brief SPI configuration structure
 * - baud_rate: Baud rate for SPI communication
 * - mode: SPI mode (0, 1, 2, or 3)
 * - bit_order: Bit order (MSB_FIRST or LSB_FIRST)
 */
typedef struct _spi_config_t
{
    uint32_t baud_rate;
    spi_polarity_t polarity;
    spi_phase_t phase;
    spi_mode_t mode;
    spi_bit_order_t bit_order;
} spi_config_t;

/**
 * @brief Default SPI configuration
 * - baud_rate: 10 MHz
 * - mode: SPI_MASTER
 * - transmit_mode: SPI_MODE_0 (CPOL=0, CPHA=0)
 * - bit_order: SPI_MSB_FIRST
 */
static const spi_config_t _SPI_DEFAULT_CONFIG = { .baud_rate = 10000000,  // 10 MHz
        .mode = SPI_MASTER,  // Master mode
        .bit_order = SPI_MSB_FIRST,  // MSB first
        .polarity = SPI_LOW,  // CPOL=0
        .phase = SPI_CPHA_1EDGE,  // CPHA=0
        };

#define SPI_DEFAULT_CONFIG ((spi_config_t*)&_SPI_DEFAULT_CONFIG)

/**
 * @brief SPI structure
 * - hspi: Pointer to the SPI handle
 * - cs_port: GPIO port for the Chip Select (CS) pin
 * - cs_pin: GPIO pin number for the Chip Select (CS) pin
 * - config: Pointer to the SPI configuration structure
 */
typedef struct _spi_t
{
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
    spi_config_t *config;
} spi_t;

/**
 * @brief SPI initialization
 * - spi: Pointer to the SPI structure
 * - spi_port: Pointer to the SPI port structure
 * - config: Pointer to the SPI configuration structure
 */
void spiInit(spi_t *spi,
             SPI_HandleTypeDef *hspi,
             SPI_TypeDef *instance,
             GPIO_TypeDef *cs_port,
             uint16_t cs_pin,
             spi_config_t *config);

/**
 * @brief Set the NSS pin to low (enable)
 * - spi_port: Pointer to the SPI port structure
 */
void spiPortChipSelectStart(spi_t *spi);

/**
 * @brief Set the NSS pin to high (disable)
 * - spi_port: Pointer to the SPI port structure
 */
void spiPortChipSelectStop(spi_t *spi);

/**
 * @brief SPI transmit function
 * - spi: Pointer to the SPI structure
 * - data: Pointer to the data buffer to be transmitted
 * - size: Size of the data buffer in bytes
 * @return SPI status (SPI_OK or SPI_ERROR)
 */
spi_status_t spiTransmit(spi_t *spi,
                         uint8_t *data,
                         uint16_t size);

/**
 * @brief SPI receive function
 * - spi: Pointer to the SPI structure
 * - data: Pointer to the buffer where received data will be stored
 * - size: Size of the data buffer in bytes
 * @return SPI status (SPI_OK or SPI_ERROR)
 */
spi_status_t spiReceive(spi_t *spi,
                        uint8_t *data,
                        uint16_t size);

#endif /* INC_API_SPI_H_ */
