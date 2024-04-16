/*
 *      Copyright (c) 2024 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Amisha Sakhare
 *      Date & Time: 16/01/2024 & 11:00 AM
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
 
#ifndef UART_DEVELOPMENT_H
#define UART_DEVELOPMENT_H

/***********************************************************************
 * Include Header Files
 **********************************************************************/
 #include <stddef.h>
/***********************************************************************
 * CONSTANTS
 **********************************************************************/
#define TX 17
#define RX 16
#define TXD_PIN (TX)     //connect to RX
#define RXD_PIN (RX)     //connect to TX
#define RTS_PIN (14)    //connect to CTS to control hardware flow
#define CTS_PIN (15)    //connect to RTS

#define UART_PORT_NUM (2U)
#define UART_BAUD_RATE (115200U)
#define STACK_SIZE (2048U)
#define BUF_SIZE (256U)
/***********************************************************************
* TYPES
***********************************************************************/

/***********************************************************************
* PUBLIC FUNCTION PROTOTYPES
***********************************************************************/

void vUartInit(void);
void vUartTransmitTask(const char *data, size_t len);
void vUartReceiveTask(void *arg);

/***********************************************************************
* END OF FILE
***********************************************************************/
#endif	/* UART_DEVELOPMENT_H */