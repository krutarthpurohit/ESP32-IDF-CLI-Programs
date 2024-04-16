/*
 *      Copyright (c) 2024 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Ragini Yadav
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
#include "stdio.h"
#include "sdkconfig.h"
#include "esp_console.h"
#include "common.h"
#include "spi_protocol.h"
#include "pwm.h"
#include "Adc_development.h"
#include "Cli_development.h"
#include "Include\I2C_Development.h"
#include "Cli_development.h"
#include "GPIO_Development.h"
#include "freertos/FreeRTOS.h"  // Include FreeRTOS header
#include "freertos/task.h"
#include "esp_console.h"    // Include for CLI module
#include "esp_err.h"        // Include for ESP error codes
#include "linenoise/linenoise.h"  // Include for linenoise command
#include "esp_log.h"  // Include for ESP logging functions
#include <string.h>

 /**********************************************************************
 * CONSTANTS
 **********************************************************************/
#define CONFIG_GPIO_OUTPUT_0    2   // Change this value based on your configuration
#define CONFIG_GPIO_OUTPUT_1    4   // Change this value based on your configuration
#define CONFIG_GPIO_INPUT_0     14  // Change this value based on your configuration
#define CONFIG_GPIO_INPUT_1     27  // Change this value based on your configuration
 /**********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************/

/***********************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************/

/***********************************************************************
 * PRIVATE FUNCTIONS
 **********************************************************************/
void app_main(void)
{
    printf("Bacancy Training Program !\n");
   
   #if(CLI_ENABLE)
        vCliInit();
    #endif

    #if(UART_ENABLE)
        vUartInit();
    #endif

    #if(GPIO_ENABLE)
        vGpioInit();
    #endif
    
    #if(SPI_ENABLE )
        vSpiInit();
    #endif
    
    #if(ADC_ENABLE )
        vAdcInit();
    #endif
    
    #if(I2C_ENABLE )
        vI2cInit();
    #endif
    
    #if(PWM_ENABLE )
       vPwmInit();
    #endif
}
/***********************************************************************
 * END OF FILE
 **********************************************************************/