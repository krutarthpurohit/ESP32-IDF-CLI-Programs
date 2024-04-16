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

#ifndef I2C_DEVELOPMENT_H__
#define I2C_DEVELOPMENT_H__

/***********************************************************************
 * Include Header Files
 **********************************************************************/

/***********************************************************************
 * CONSTANTS
 **********************************************************************/

 #include <stdio.h>
//  #include <string.h>
//  #include <stdlib.h>
 #include "esp_log.h"
 #include "ssd1306_commands.h"
//  #include "freertos/FreeRTOS.h"
//  #include "freertos/task.h"
 #include "driver/i2c.h"
 #include "ssd1306.h"
 #include "app_oled.h"
 #include "oled_sh1106.h"
 #include "ssd1306_i2c.h"
 #include "ssd1306_hal/io.h"

 #define GPIO_PULLUP_ENABLE 0x1
 #define I2C_MODE_MASTER 0x01
//  #define I2C_MASTER_NUM              GPIO_NUM_0
//  #define I2C_MASTER_FREQ_HZ          10000=
//  #define I2C_MASTER_TIMEOUT_MS       1000
//  #define I2C_HW_ADDR                 0X3C
//  #define OLED_WIDTH                  128
//  #define OLED_HEIGHT                 64
 #define OLED_RESET_PIN              -1
//  uint8_t s_ssd1306_invertByte = 0x00000000;
//  SFixedFontInfo s_fixedFont = {};

/***********************************************************************
* TYPES
***********************************************************************/

/***********************************************************************
* PUBLIC FUNCTION PROTOTYPES
***********************************************************************/
void vI2cInit(void);
void i2c_write_data(const char *ch);

/***********************************************************************
* END OF FILE
***********************************************************************/


#endif 