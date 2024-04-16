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
 * \file        spi_protocol.c
 * \brief       Driver for SPI Protocol
 */

/***********************************************************************
 * Include Header Files
 **********************************************************************/
#include "spi_protocol.h"
#include "esp_log.h"

/***********************************************************************
 * CONSTANTS
 **********************************************************************/
#define SPI_TAG "spi_protocol"

/**********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************/
 
/***********************************************************************
 * PRIVATE FUNCTIONS
 **********************************************************************/

/***********************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************/
esp_err_t ret;
spi_device_handle_t spi;

void vSpiInit(void)
{
    gpio_set_direction(PIN_NUM_CS, GPIO_MODE_OUTPUT);
    
    spi_bus_config_t buscfg={       //Configuring the pins- MOSI, MSIO, SCLK
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=512*8     //**4095 bytes is the max size of data that can be sent because of hardware limitations
    };
    
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=12*1000*1000,           //Clock out at 10 MHz
        .mode=0,                                //SPI mode 0: CPOL:-0 and CPHA:-0
        .spics_io_num=PIN_NUM_CS,               //This field is used to specify the GPIO pin that is to be used as CS
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
    };
    
    //Initialize the SPI bus
    ret=spi_bus_initialize(ESP_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    
    //Attach the Slave device to the SPI bus
    ret=spi_bus_add_device(ESP_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
}
 /**
 * @brief: Initialize SPI
 *
 * @param[in] void
 * @param[out] void
 */

void spi_write_data(uint8_t addr ,uint8_t data)
{      
    spi_transaction_t trans_desc={
        .flags = SPI_TRANS_USE_TXDATA,
        .tx_data = {addr,data},
        .length = 16,
    }; 
    gpio_set_level(PIN_NUM_CS,0);
    ret = spi_device_polling_transmit(spi, &trans_desc);
    if( ret != ESP_OK)
    {
        ESP_LOGE(SPI_TAG, "SPI read operation failed because SPI bus not initialized\n");
        ESP_LOGE(SPI_TAG, "Run \"spi_start 1\" to initialize the spi bus");
    }
    vTaskDelay(1/portTICK_PERIOD_MS);
    gpio_set_level(PIN_NUM_CS,1);
}
 /**
 * @brief: Write SPI
 *
 * @param[in] void
 * @param[out] void
 */

void spi_read_data(uint8_t addr)
{
    uint8_t instruction_to_read_data[2] = {0x80 | addr, 0xFF};
    spi_transaction_t trans_desc={
        .flags = SPI_TRANS_USE_RXDATA,
        .tx_buffer = instruction_to_read_data,
        .rxlength = 16,         //8*4 = 32 bit data transfer (MAX)
        .length = 16
    };
    gpio_set_level(PIN_NUM_CS,0);                                       //line 108 not needed as
    ret = spi_device_polling_transmit(spi, &trans_desc);                //spi_device_polling_transmit automatically lowers/higher the CS line
    if (ret != ESP_OK)
    {
        ESP_LOGE(SPI_TAG, "SPI write operation failed because SPI bus not initialized\n");
        ESP_LOGE(SPI_TAG, "Run \"spi_start 1\" command to initialize the spi bus");
    }  
    printf("Data Read %d- %d\n",addr, trans_desc.rx_data[1]);

    vTaskDelay(1/portTICK_PERIOD_MS);
    gpio_set_level(PIN_NUM_CS,1);
}
 /**
 * @brief: Read SPI
 *
 * @param[in] void
 * @param[out] void
 */

/***********************************************************************
 * END OF FILE
 **********************************************************************/