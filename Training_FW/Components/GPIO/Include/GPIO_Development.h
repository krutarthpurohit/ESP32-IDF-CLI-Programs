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
#ifndef GPIO_DEVELOPMENT_H
#define GPIO_DEVELOPMENT_H

#include "esp_console.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"
#include "stdlib.h"
/***********************************************************************
 * CONSTANTS
**********************************************************************/
#define GPIO_OUTPUT_PIN_SEL ((1ULL << GPIO_OUTPUT_IO_0) | (1ULL << GPIO_OUTPUT_IO_1))
#define GPIO_INPUT_PIN_SEL ((1ULL << GPIO_INPUT_IO_0) | (1ULL << GPIO_INPUT_IO_1 ))
/***********************************************************************
 * TYPES
***********************************************************************/

/***********************************************************************
 * PUBLIC FUNCTION PROTOTYPES
***********************************************************************/

void vGpioInit(void);
esp_err_t customised_gpio_set_level(uint8_t pin_num ,uint8_t u8leval);
esp_err_t show_gpio_interrupt_info(void);
esp_err_t gpio_set_high_duration(uint8_t u8GpioNum, uint16_t u16DuraMs);

/*Register GPIO commands with the CLI module*/
void register_gpio_commands(void);

/*Declaration of CLI command task*/
void cli_command_task(void *pvParameters);
/***********************************************************************
 * END OF FILE
***********************************************************************/
#endif  // GPIO_DEVELOPMENT_H
