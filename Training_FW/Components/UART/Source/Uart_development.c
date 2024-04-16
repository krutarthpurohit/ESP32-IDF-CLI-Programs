/*
 *      Copyright (c) 2024 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Amisha Sakhare
 *      Date & Time: 16/01/2024 & 11:00 AM
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

/***********************************************************************
 * Include Header Files
 **********************************************************************/
#include "Uart_development.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include <stddef.h>
#include <string.h>
/***********************************************************************
 * CONSTANTS
 **********************************************************************/
static const char *TAG = "UART";
static char buffer[BUF_SIZE];
static int buffer_index = 0;
static bool flag = true;
 /**********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************/
 
/***********************************************************************
 * PRIVATE FUNCTIONS
 **********************************************************************/


void vClearTerminal(void) 
{
    // ANSI escape code for clearing the screen
    const char *clear_screen = "\033[2J \033[H";
    uart_write_bytes(UART_PORT_NUM, clear_screen, strlen(clear_screen));
}

void vUartTransmitTask(const char *data, size_t length) 
{
    vClearTerminal();
    uart_write_bytes(UART_PORT_NUM, data, length);
    ESP_LOGI(TAG, "Transmitted: %.*s", length, data);
}

void vUartReceiveTask(void *arg)
{
    vClearTerminal();
    while (flag)
    {
        uint8_t rx_char;
        int receive_len = uart_read_bytes(UART_PORT_NUM, &rx_char, 1, portMAX_DELAY);
        uart_write_bytes(UART_PORT_NUM, &rx_char, receive_len);
        if (receive_len > 0)
        {
            buffer[buffer_index++] = rx_char;
            if (buffer_index >= BUF_SIZE) {
                ESP_LOGW(TAG, "Buffer overflow detected!");
                buffer_index = 0;
            }
            if (rx_char == '\r') 
            {
                ESP_LOGI(TAG, "Received string: %s", buffer);
                buffer_index = 0; 
                flag = false;
            }
        }
    }
    flag = true;
}

void vUartInit(void)
{
    /* called function uart_config and pass uart_config_t structure having all the parameters */
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    }; 
    int intr_alloc_flags = 0;
    #if CONFIG_UART_ISR_IN_IRAM
        intr_alloc_flags = ESP_INTR_FLAG_IRAM;
    #endif

    ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM, BUF_SIZE*2, 0,0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM, TXD_PIN, RXD_PIN, RTS_PIN, CTS_PIN));
}
/***********************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************/
 
/***********************************************************************
 * END OF FILE
 **********************************************************************/