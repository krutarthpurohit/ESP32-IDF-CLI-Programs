/*
 *      Copyright (c) 2024 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Yash Suvariya
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
 * \file pwm.h
 * \brief header file for the pwm led operation
 */
 
#ifndef PWM_H
#define PWM_H
 
/***********************************************************************
 * Include Header Files
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver/ledc.h"
#include "esp_err.h"


/***********************************************************************
 * CONSTANTS
 ***********************************************************************/
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (5) /* Define the output GPIO */
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT /*Set duty resolution to 13 bits*/

#define MINIMUM_FREQUENCY       1   /* Minimum frequency in Hz*/
#define MAXIMUM_FREQUENCY       5000 /* Maximum frequency in Hz */
#define MAXIMUM_DUTY_CYCLE      100  /* maximum duty cycle in percentage */
#define MINIMUM_DUTY_CYCLE      0    /* minimum duty cycle in percentage */
extern uint32_t frequency;

    
/***********************************************************************
* TYPES
***********************************************************************/

/***********************************************************************
* PUBLIC FUNCTION PROTOTYPES
***********************************************************************/
void vPwmInit(void);
void initialize_ledc(uint32_t frequency);
int setting_pwm_duty_cycle(int argc, char **argv);
int setting_pwm_frequency(int argc, char **argv);
int pwm_controling(int argc, char **argv);
/***********************************************************************
* END OF FILE
***********************************************************************/
#endif  /*PWM_H*/ 

