/*
 *      Copyright (c) 2021 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Ruchita Shekhada
 *      
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
 * \file    app_oled.c
 * \brief
 */
/************************************************************************
 * Include Header Files
 ************************************************************************/
#include "app_oled.h"
#include "ssd1306.h"
#include "ssd1306.h"
#include "ssd1306_commands.h"
#include "ssd1306_interface.h"
#include "ssd1306_generic.h"
#include "ssd1306_fonts.h"
#include "ssd1306_1bit.h"
// #include "ssd1306_8bit.h"
#include "lcd_common.h"
#include "driver/gpio.h"

/************************************************************************
 * Define Macros
 ************************************************************************/
#define TAG "oled"
#define OLED_Q_LEN (10U)
#define OLED_Q_ITEM_SIZE (sizeof(oled_queue_msg_t))
#define OLED_TASK_NAME "oled_task"
#define OLED_TASK_STACK_SIZE (8 * 1024) ///< Define Task Stack Size
#define DEFAULT_OLED_BITMASK (0x00000000U)
#define OLED_TASK_PRIORITY 4U
#define GPIO_SCL         GPIO_NUM_12
/************************************************************************
 * Define Enumeration/Structure/Unions
 ************************************************************************/




/************************************************************************
 * Define Private Function Prototypes
 ************************************************************************/

/************************************************************************
 * Define Private Variables
 ************************************************************************/

/************************************************************************
 * Define Global Variables
 ************************************************************************/

TaskHandle_t oled_task_handle = NULL;
oled_queue_msg_t oled_queue_msg;
QueueHandle_t oled_evt_queue;
uint8_t Voltage[8U];
uint8_t e_fault_flag;
const PROGMEM uint8_t epd_bitmap_bluetooth [] = {
     0x10,0x20,0x40,0xff,0x86,0x8C,0x98,0x70 ,/*DOWN*/
     0x08,0x04,0x02,0xff,0x61,0x31,0x19,0x0E 
	   
 };


/************************************************************************
 * Define Global Function Prototypes
 ************************************************************************/
void oled_task(void* arg);

 /**
 * @brief: API to display firmware version on board init
 *
 * @param[in] void
 * @param[out] void    
 *  */
void oled_todisplayversion(void)
{
    ssd1306_clearScreen();
	// ssd1306_Happy_Face();
	// ssd1306_traingle(); 
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(40, 0, "HELLO", STYLE_BOLD);
	ssd1306_printFixed(45, 18, "OLED", STYLE_BOLD);
    // ssd1306_drawLine(0, 17, 128, 17);
    // ssd1306_printFixed(0, 45, (char *)"FIRM_VER:", STYLE_NORMAL);//32
    // ssd1306_printFixed(80, 45,(char *)fw_version, STYLE_NORMAL);

}
   /**
  * @brief      Initializes oled task.
  *
  * @param      void
  * @return     bool
  */
 /**
 * @brief: Initializes oled task.
 *
 * @param[in] data     void     
 *
 * @param[out] bool    return true or false
 */
bool oled_task_init(void)
{
    bool ret = true;
    oled_evt_queue = xQueueCreate(10, sizeof(uint32_t));
	if (oled_evt_queue == NULL)
	{
		ESP_LOGE(TAG, "Failed to create uiMsgQueue queue \n");
		vQueueDelete(oled_evt_queue);
		ret = false;
	}
	else
	{
		ESP_LOGI(TAG, "OLEDMsgQueue queue created successfully \n");
		if (xTaskCreate(oled_task,
						OLED_TASK_NAME,
						OLED_TASK_STACK_SIZE,
						NULL,
						OLED_TASK_PRIORITY,
						&oled_task_handle) != pdTRUE)
		{
			ESP_LOGE(TAG, "Failed to initialize OLED task \n");
			vTaskDelete(oled_task_handle);
			oled_task_handle = NULL;
			ret = false;
		}
    }
  		ESP_LOGE(TAG, "ret : %d ",ret);
	return ret;

}




   