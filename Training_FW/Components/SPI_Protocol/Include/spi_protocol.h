/*
 *      Copyright (c) 2024 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Krutarth Purohit
 *      Date & Time: 17/02/2024 & 9:30pm
 *
 *
 *                      CONFIDENTIAL INFORMATION
 *                      ------------------------
 *      This Document contains Confidential Information or Trade Secrets,
 *      or both, which are the property of Bacancy System LLP.
 *      This document may not be copied, reproduced, reduced to any
 *      electronic medium or machine readable form or otherwise
 *      duplicated and the information herein may not be used,
 *      disseminated or otherwise disclosed, except with the prior
 *      written consent of Bacancy System LLP.
 *
 */
 /*!
 * \file
 * \brief
 */
 
#ifndef SPI_MASTER_H__
#define SPI_MASTER_H__

/***********************************************************************
 * Include Header Files
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
 
/***********************************************************************
 * CONSTANTS
 **********************************************************************/
#define ESP_HOST    VSPI_HOST           // Host is ESP32
#define PIN_NUM_MISO GPIO_NUM_32
#define PIN_NUM_MOSI GPIO_NUM_23
#define PIN_NUM_CLK  GPIO_NUM_18
#define PIN_NUM_CS   GPIO_NUM_5

/***********************************************************************
* TYPES
***********************************************************************/

/***********************************************************************
* PUBLIC FUNCTION PROTOTYPES
***********************************************************************/
void vSpiInit(void);
void spi_read_data(uint8_t addr);
void spi_write_data(uint8_t addr, uint8_t data);
/***********************************************************************
* END OF FILE
***********************************************************************/
#endif //SPI_MASTER_H__