/*
 *      Copyright (c) 2021 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Kanji Viroja
 *      Date & Time: 13-05-2021, 15:00:00
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
 * \file     bms_oled.h
 * \brief
 */

#ifndef _APP_OLED_H_
# define _APP_OLED_H_
/************************************************************************
 * Include Header Files
 ************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "oled_ssd1306.h"
#include "ssd1306.h"
// #include "ssd1306_commands.h"
#include "ssd1306_interface.h"
#include "ssd1306_generic.h"
#include "ssd1306_fonts.h"
#include "ssd1306_1bit.h"
// #include "ssd1306_8bit.h"
#include "lcd_common.h"

/************************************************************************
 * Define Macros
 ************************************************************************/


#define DISPLY_ADD 0x3C
#define PUBLIC extern
#define I2C_MASTER_NUM 0                     /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 10000             /*!< I2C master clock frequency */
#define CHARGER_AVAILABLE_TIME               (15U) 
#define CHARGING_STATUS_DISPLAY_TIME         (10U)
#define SWITCH_DURING_CHARGING               (3U)
#define TIMIOUT_DELAY   pdMS_TO_TICKS(3000)
/************************************************************************
 * Define Enumeration/Structure/Unions
 ************************************************************************/
typedef struct
{
    uint8_t msg;
    uint8_t data;
} oled_queue_msg_t;

typedef enum
{
    METER_MSG =1,
    BLE_MSG,
    OLED_CLEAR,
    FIRM_VER,
    EARTH_FAULT,
    EARTH_DETECT,
    EARTH_CLEAR,
    EMERGENCY_STOP
   // INVALID_CMD_INDEX = 0xFF,
} oled_msg_t;
/************************************************************************
 * Define Private Variables
 ************************************************************************/

/************************************************************************
 * Define Global Variables
 ************************************************************************/
PUBLIC oled_queue_msg_t oled_queue_msg;
PUBLIC QueueHandle_t oled_evt_queue;
PUBLIC TaskHandle_t oled_task_handle;
/************************************************************************
 * Define Private Function Prototypes
 ************************************************************************/

/************************************************************************
 * Define Global Function Prototypes
 ************************************************************************/
 /**
 * @brief: API to display firmware version on board init
 *
 * @param[in] void
 * @param[out] void    
 *  */
void oled_todisplayversion(void);

/**
 * @brief: API to Display Voltage, Current, And SOC on OLED
 *
 * @param[in] void
 * @param[out] void
 */
// PUBLIC void OledPrintData(void);
/**
 * @brief: This Function initialize UI task
 *
 * @param[in] void
 * @param[out] bool     return on success true either false
 */
bool oled_task_init(void);
#endif 
