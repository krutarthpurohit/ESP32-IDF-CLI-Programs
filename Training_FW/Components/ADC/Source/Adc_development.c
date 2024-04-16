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
#include "Adc_development.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "esp_adc_cal.h"

/***********************************************************************
 * CONSTANTS
 **********************************************************************/

 /**********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************/
 
/***********************************************************************
 * PRIVATE FUNCTIONS
 **********************************************************************/
 /**
 * @brief: main function.
 */
static const char *TAG = "ADC_READING"; 
static esp_adc_cal_characteristics_t adc1_chars;
float scalevoltage(float input_voltage, float vin_min, float vin_max) {
float scaled_voltage = vin_min + ((input_voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * (vin_max - vin_min);
    return scaled_voltage;
}
void adc_read(float VIN_MIN,float VIN_MAX){
    int adc_values[AVG_SIZE],sum = 0,avg_adc_value,i,mvol;
    float scaled_voltage;
    float voltage;
    
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH, 0, &adc1_chars);   
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH)); 
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11));

    for (i = 0; i < AVG_SIZE; i++) {
            adc_values[i] = adc1_get_raw(ADC1_CHANNEL_0);
            sum += adc_values[i];
        }
    avg_adc_value = sum / AVG_SIZE;
    mvol = esp_adc_cal_raw_to_voltage(avg_adc_value, &adc1_chars);
    voltage = (float)mvol/1000;
    ESP_LOGI(TAG, "ADC Value: %d\t voltage: %.3f ", avg_adc_value, voltage);

    scaled_voltage = scalevoltage(voltage,VIN_MIN,VIN_MAX);
    ESP_LOGI(TAG, "Scaled voltage: %.3f V", scaled_voltage);

 }
 
void vAdcInit(){
}

/***********************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************/
 
/***********************************************************************
 * END OF FILE
 **********************************************************************/