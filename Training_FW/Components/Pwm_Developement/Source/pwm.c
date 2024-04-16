/*
 *      Copyright (c) 2024 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author:Yash Suvariya
 *      Date & Time:07/02/2024
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
 * \brief void fuction for the pwm developement
 */


/***********************************************************************
 * Include Header Files
 **********************************************************************/
#include "pwm.h"

/***********************************************************************
 * CONSTANTS
 **********************************************************************/
uint32_t frequency;
 /**********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************/
/***********************************************************************
 * PRIVATE FUNCTIONS
 **********************************************************************/
/*@brief: main function.*/
void vPwmInit(void)
{
   /*do nothing*/
}

void initialize_ledc(uint32_t frequency) 
{
    /*Prepare and then apply the LEDC PWM timer configuration*/
    ledc_timer_config_t ledc_timer = 
    {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = frequency,  /* Set output frequency*/
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    /*Prepare and then apply the LEDC PWM channel configuration*/
    ledc_channel_config_t ledc_channel = 
    {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, /* Initial duty cycle*/
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

int setting_pwm_duty_cycle(int argc, char **argv)
{
    int duty_cycle = atoi(argv[1]);
    if (duty_cycle < 0 || duty_cycle > 100) 
    {
        printf("Invalid duty cycle. Please enter a value between 0 and 100.\n");
        return ESP_ERR_INVALID_ARG;
    }
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, (duty_cycle * ((1 << LEDC_DUTY_RES) - 1)) / 100));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    printf("Duty cycle set to %d%%\n", duty_cycle);
    return ESP_OK;
}

int setting_pwm_frequency(int argc, char **argv)
{
    int frequency = atoi(argv[1]);
    if (frequency < MINIMUM_FREQUENCY || frequency > MAXIMUM_FREQUENCY)
    {
        printf("Invalid frequency. Please enter a value between %d and %d.\n", MINIMUM_FREQUENCY, MAXIMUM_FREQUENCY);
        return ESP_ERR_INVALID_ARG;
    }
    initialize_ledc(frequency);
    printf("Frequency set to %d Hz\n", frequency);
    return ESP_OK;
}


int pwm_controling(int argc, char **argv) 
{
    if (argc != 2) 
    {
        printf("Usage: pwm_controling <on|off>\n");
        return ESP_ERR_INVALID_ARG;
    }
    
    if (strcmp(argv[1], "on") == 0) 
    {
        /* Code to turn on the LED*/
        printf("pwm turned on\n");
    } 
    else if (strcmp(argv[1], "off") == 0) 
    {
        /* Code to turn off the LED */
        printf("pwm turned off\n");
    } 
    else 
    {
        printf("Invalid argument. Usage: pwm_controling <on|off>\n");
        return ESP_ERR_INVALID_ARG;
    }
    
    return ESP_OK;
}
/***********************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************/ 
/***********************************************************************
 * END OF FILE
 **********************************************************************/