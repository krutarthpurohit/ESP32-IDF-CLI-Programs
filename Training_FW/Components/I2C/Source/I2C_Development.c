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
#include "Include/I2C_Development.h"
// #include "ssd1306.h"
// #include "driver/i2c.h"
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
void vI2cInit(void)
{
    ssd1306_i2cInit();
    sh1106_128x64_init();
}

/// @brief 
/// @param ch 
void i2c_write_data(const char *ch)
{
    ssd1306_clearScreen();
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_printFixed(5, 31, ch, STYLE_NORMAL);
}





