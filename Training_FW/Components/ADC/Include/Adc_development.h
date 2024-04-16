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
#ifndef ADC_DEVELOPMENT_H
#define ADC_DEVELOPMENT_H

/***********************************************************************
 * Include Header Files
 **********************************************************************/

/***********************************************************************
 * CONSTANTS
 **********************************************************************/
 #define ADC_WIDTH  ADC_WIDTH_BIT_12
 #define AVG_SIZE  10
 #define MIN_VOLTAGE 0.8f
 #define MAX_VOLTAGE 3.155f
 /**********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************/
 
/***********************************************************************
 * PRIVATE FUNCTIONS
 **********************************************************************/
  void vAdcInit(void);
  float scalevoltage(float input_voltage, float vin_min, float vin_max);
  void adc_read(float VIN_MIN,float VIN_MAX);
/***********************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************/

/***********************************************************************
 * END OF FILE
 **********************************************************************/
#endif	/* ADC_DEVELOPMENT_H */