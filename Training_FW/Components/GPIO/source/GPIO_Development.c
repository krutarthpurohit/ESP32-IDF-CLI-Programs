/*
 *      Copyright (c) 2024 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author:
 *      Date & Time:
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
#include "GPIO_Development.h"
#include <string.h>
#include "esp_console.h"    /*Include for CLI module*/
#include "esp_log.h"
#include "linenoise/linenoise.h"
#include <stdlib.h>
/***********************************************************************
 * CONSTANTS
**********************************************************************/
#define TAG "GPIO_Development"
#define GPIO_OUTPUT_IO_0    2U
#define GPIO_OUTPUT_IO_1    4U
#define GPIO_INPUT_IO_0     14U
#define GPIO_INPUT_IO_1     27U

#define HIGH 1
#define LOW 0
/***********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************/

/***********************************************************************
 * PRIVATE FUNCTIONS
**********************************************************************/
/**
* @brief: main function.
*/
void vGpioInit(void)
{
    gpio_config_t io_conf = 
    {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
        .pull_up_en = 0,
        .pull_down_en = 0,
    };
    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.pull_up_en = 1;
    io_conf.pull_down_en = 0;
    gpio_config(&io_conf);

    /*Change GPIO interrupt type for one pin*/
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);
}

/*Function to set a GPIO pin to level high or low*/
esp_err_t customised_gpio_set_level(uint8_t pin_num ,uint8_t u8leval)
{
    gpio_set_level(pin_num, u8leval);
    
    if (u8leval == HIGH) 
    {
        ESP_LOGI(TAG, "GPIO pin %d set to HIGH", pin_num);
    } 
    else 
    {
        ESP_LOGI(TAG, "GPIO pin %d set to LOW", pin_num);
    }
    return ESP_OK;
}

/*Function to print information about GPIO interrupts*/
esp_err_t show_gpio_interrupt_info(void) 
{
    ESP_LOGI(TAG, "Interrupts enabled on GPIO pins: %d, %d", GPIO_INPUT_IO_0, GPIO_INPUT_IO_1);
    return ESP_OK;
}

/*Function to set a GPIO pin high for a specified duration*/
esp_err_t gpio_set_high_duration(uint8_t u8GpioNum, uint16_t u16DuraMs) 
{
    gpio_set_level(u8GpioNum, 1);
    ESP_LOGI(TAG, "GPIO pin %d set to HIGH for %d ms", u8GpioNum, u16DuraMs);
    vTaskDelay(pdMS_TO_TICKS(u16DuraMs));
    gpio_set_level(u8GpioNum, 0);
    return ESP_OK;
}
/***********************************************************************
 * PUBLIC FUNCTIONS
**********************************************************************/

/***********************************************************************
 * END OF FILE
**********************************************************************/