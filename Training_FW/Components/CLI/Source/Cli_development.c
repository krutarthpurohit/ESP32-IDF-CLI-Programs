/*
 *      Copyright (c) 2024 Bacancy System LLP.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Amisha Sakhare
 *      Date & Time: 09/02/2024 & 10:00 AM
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
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"
#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "Cli_development.h"
#include "Uart_development.h"
#include "Include/I2C_Development.h"

#include "Adc_development.h"
#include "pwm.h"

#include "GPIO_Development.h"
#include "spi_protocol.h"

/***********************************************************************
 * CONSTANTS
 **********************************************************************/
#define TRUE 1
#define FALSE 0
#define MICRO_DELAY 1000
#define PROMPT_STR "PROTOCOLS"
static const char *TAG = "Protocol Example";
static bool exit_loop = false;
/**********************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 **********************************************************************/
 
/***********************************************************************
 * PRIVATE FUNCTIONS
 **********************************************************************/

static void vInitNVS(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}

static void vInitConsole(void)
{
    /* Drain stdout before reconfiguring it */
    fflush(stdout);
    fsync(fileno(stdout));

    /* Disable buffering on stdin */
    setvbuf(stdin, NULL, _IONBF, 0);

    /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
    esp_vfs_dev_uart_port_set_rx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CR);
    /* Move the caret to the beginning of the next line on '\n' */
    esp_vfs_dev_uart_port_set_tx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CRLF);

    /* Configure UART. Note that REF_TICK is used so that the baud rate remains
     * correct while APB frequency is changing in light sleep mode.
     */
    const uart_config_t uart_config = {
        .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
    };
    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK(uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM, 256, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM, &uart_config));

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

    /* Initialize the console */
    esp_console_config_t console_config = {
        .max_cmdline_args = 16,
        .max_cmdline_length = 1024,
    };
    ESP_ERROR_CHECK(esp_console_init(&console_config));

    /* Configure linenoise line completion library */
    /* Enable multiline editing. If not set, long commands will scroll within
     * single line.
     */
    linenoiseSetMultiLine(1);

    /* Tell linenoise where to get command completions and hints */
    linenoiseSetCompletionCallback(&esp_console_get_completion);
    linenoiseSetHintsCallback((linenoiseHintsCallback *)&esp_console_get_hint);

    /* Set command history size */
    linenoiseHistorySetMaxLen(100);

    /* Set command maximum length */
    linenoiseSetMaxLineLen(console_config.max_cmdline_length);

    /* Don't return empty lines */
    linenoiseAllowEmpty(false);
}
/***********************************************************************
 * COMMAND FUNCTIONS
 **********************************************************************/
static int cmd_uart_transmit(int argc, char **argv) 
{
    int UartInput;
    size_t LengthOfUartData = 0;
    if (argc < 2) 
    {
        printf("Usage: uart_transmit <message>\n");
        return TRUE;
    }
    for (UartInput = 1; UartInput < argc; UartInput++) 
    {
        LengthOfUartData += strlen(argv[UartInput]);
    }

    vUartTransmitTask(argv[1], LengthOfUartData);
    return FALSE;
}

static int cmd_uart_recieve(int argc, char **argv)
{
    vTaskDelay(pdMS_TO_TICKS(MICRO_DELAY));
    vUartReceiveTask(NULL);
    return FALSE;
}

static int cmd_exit(int argc, char **argv)
{
    exit_loop = true;
    return FALSE;
}

static int cmd_spi_start(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: spi_init\n");
        return TRUE;
    }
    vSpiInit();
    printf("Spi initialized. Now, you can execuite spi_read and spi_write commands.\n");
    return FALSE;
}

static int cmd_spi_read_data(int argc, char **argv)
{
    printf("Reading operation started\n");
    if (argc < 2)
    {
        printf("Usage: spi_read <size> <address>\n");
        return TRUE;
    }
    int size=atoi(argv[1]);
    int address=atoi(argv[2]);
    for (int i = 0; i < size; i++)
    {
        spi_read_data(address+i);
    }
    printf("Reading operation completed\n");
    
    return FALSE;
}

static int cmd_spi_write_data(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: spi_write <size> <address> <data>\n");
        return TRUE;
    }
    int size=atoi(argv[1]);
    int address=atoi(argv[2]);
    printf("Writing operation started\n");
    for (int i = 0; i < size; i++)
    {
        spi_write_data(address+i, atoi(argv[3+i]));
    }
    printf("Writing operation completed\n");
        
    return FALSE;
}

static int cmd_scale(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: adc_data <vin_min> <vin_max>");
        return TRUE;
    }
    adc_read(atof(argv[1]),atof(argv[2]));
    return FALSE;
}

static int set_pwm_duty_cycle(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: set_duty <duty_cycle>");
        return TRUE;
    }
    printf("Duty cycle = %d\n", atoi(argv[1]));
    setting_pwm_duty_cycle(argc, argv);
    return FALSE;
}

static int set_pwm_frequency(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: set_frequency <frequency>");
        return TRUE;
    }
    printf("Frequency = %d\n", atoi(argv[1]));
    setting_pwm_frequency(argc, argv);
    return FALSE;
}

static int pwm_control(int argc, char **argv)
{
    if (argc < 2)
    {
            int pwm_controling(int argc, char **argv);

        printf("Usage: pwm_control <on|off>");
        return TRUE;
    }
    printf("Control = %s\n", argv[1]);
    pwm_controling(argc,argv);
    return FALSE;
}

int custom_gpio_set_level(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: gpio_set_high <pin_num> <level>");
        return TRUE;
    }
    printf("Pin is %d\n", atoi(argv[1]));
    customised_gpio_set_level(atoi(argv[1]), atoi(argv[2]));
    return FALSE;
}

static int gpio_interrupt_info(int argc, char **argv)
{
    printf("Print information\n");
    show_gpio_interrupt_info();
    return FALSE;
}

int gpio_set_duration(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: gpio_set_high_duration <pin_num> <duration_ms>");
        return TRUE;
    }
    printf("Pin is %d\n", atoi(argv[1]));
    printf("Duration is %d\n", atoi(argv[2]));
    gpio_set_high_duration(atoi(argv[1]), atoi(argv[2]));
    return FALSE;
}

static int cmd_i2c_write_data(int argc, char **argv)
{
    size_t I2cDataLength = 0;
    if (argc < 2)
    {
        printf("Usage: i2c_write <user_define_string>");
        return TRUE;
    }
    for (int I2cInput = 1; I2cInput < argc; I2cInput++) 
    {
        I2cDataLength += strlen(argv[I2cInput]);
    }
    i2c_write_data(argv[1]);
    printf("User string is %s\n", argv[1]);
    return FALSE;
}
/***********************************************************************
 * PUBLIC FUNCTIONS
 **********************************************************************/
void vCliInit(void)
{
    vInitNVS();
    vInitConsole();
    vUartInit();
    vI2cInit();

    /* Register commands */
    esp_console_register_help_command();

    /***********************************************************************
     * STRUCTURES FOR COMMANDS
     **********************************************************************/
    /*exit from the CLI*/
    const esp_console_cmd_t cmd_exit_struct = {
        .command = "exit",
        .help = "Close the console",
        .hint = NULL,
        .func = &cmd_exit,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_exit_struct));

    /*UART*/
    const esp_console_cmd_t cmd_uart_transmit_struct = {
        .command = "uart_transmit",
        .help = "Transmit data over UART",
        .hint = "<message>",
        .func = &cmd_uart_transmit,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_uart_transmit_struct));

    const esp_console_cmd_t cmd_uart_receive_struct = {
        .command = "uart_receive",
        .help = "Receive data over UART",
        .hint = NULL,
        .func = &cmd_uart_recieve,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_uart_receive_struct));

    /*SPI*/
        const esp_console_cmd_t cmd_spi_initialize_struct = {
        .command = "spi_start",
        .help = "To initialize spi bus",
        .hint = "<1>",
        .func = &cmd_spi_start,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_spi_initialize_struct));

    const esp_console_cmd_t cmd_spi_read_struct = {
        .command = "spi_read",
        .help = "To read the value of a register (enter values in decimal)",
        .hint = "<size> <address>",
        .func = &cmd_spi_read_data,    
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_spi_read_struct));

    const esp_console_cmd_t cmd_spi_write_struct = {
        .command = "spi_write",
        .help = "To perform write operation at a given address (enter values in decimal)",
        .hint = "<size> <address> <data> (enter data number of times you have entered size, seperated by space.)",
        .func = &cmd_spi_write_data,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_spi_write_struct));

    /*I2C*/
    const esp_console_cmd_t cmd_i2c_write_struct = {
        .command = "i2c_write",
        .help = "Write a string to the slave device",
        .hint = "<user_define_string>",
        .func = &cmd_i2c_write_data,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_i2c_write_struct));

    /*ADC*/
    const esp_console_cmd_t cmd_adc_scale_struct = {
        .command = "adc_data",
        .help = "Scale voltage to the entered range",
        .hint = "<vin_min> <vin_max>",
        .func = &cmd_scale,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_adc_scale_struct));

    /*GPIO Intrupt*/
    const esp_console_cmd_t cmd_gpio_high_struct = {
        .command = "custom_gpio_set_level",
        .help = "Set a GPIO pin level",
        .hint = "<pin_num> <level>",
        .func = &custom_gpio_set_level,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_gpio_high_struct));

    const esp_console_cmd_t cmd_gpio_interrupt_struct = {
        .command = "gpio_interrupt_info",
        .help = "Print information about GPIO interrupts",
        .hint = NULL,
        .func = &gpio_interrupt_info,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_gpio_interrupt_struct));

    const esp_console_cmd_t cmd_gpio_high_duration_struct = {
        .command = "gpio_set_high_duration",
        .help = "Set a GPIO pin high for a specified duration",
        .hint = "<u8GpioNum> <u16DuraMs>",
        .func = &gpio_set_duration,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_gpio_high_duration_struct));

    /*PWM*/
    const esp_console_cmd_t cmd_pwm_duty_struct = {
        .command = "set_duty",
        .help = "Set PWM duty cycle (0-100)",
        .hint = "<duty_cycle>",
        .func = &set_pwm_duty_cycle,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_pwm_duty_struct));

    const esp_console_cmd_t cmd_pwm_frequency_struct = {
        .command = "set_frequency",
        .help = "Set PWM frequency",
        .hint = "<frequency>",
        .func = &set_pwm_frequency,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_pwm_frequency_struct));

    const esp_console_cmd_t cmd_pwm_on_struct = {
        .command = "pwm_control",
        .help = "Control the PWM",
        .hint = "<on|off>",
        .func = &pwm_control,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd_pwm_on_struct));

    /* Prompt to be printed before each line.*/
    const char *prompt = LOG_COLOR_I PROMPT_STR "> " LOG_RESET_COLOR;

    printf("\n"
           "This is an example of ESP-IDF console component.\n"
           "Type 'help' to get the list of commands.\n"
           "Use UP/DOWN arrows to navigate through command history.\n"
           "Press TAB when typing command name to auto-complete.\n"
           "Press Enter or Ctrl+C will terminate the console environment.\n");

    /* Main loop */
    while (!exit_loop)
    {
        /* Get a line using linenoise.
         * The line is returned when ENTER is pressed.
         */
        char *line = linenoise(prompt);
        if (line == NULL)
        { 
            continue;
        }
        /* Add the command to the history if not empty*/
        if (strlen(line) > 0)
        {
            linenoiseHistoryAdd(line);
        }
        /* Try to run the command */
        int ret;
        esp_err_t err = esp_console_run(line, &ret);
        if (err == ESP_ERR_NOT_FOUND)
        {
            printf("Unrecognized command\n");
        }
        else if (err == ESP_ERR_INVALID_ARG)
        {
            // command was empty
        }
        else if (err == ESP_OK && ret != ESP_OK)
        {
            printf("Command returned non-zero error code: 0x%x (%s)\n", ret, esp_err_to_name(ret));
        }
        else if (err != ESP_OK)
        {
            printf("Internal error: %s\n", esp_err_to_name(err));
        }
        /* linenoise allocates line buffer on the heap, so need to free it */
        linenoiseFree(line);
    }
    ESP_LOGE(TAG, "Error or end-of-input, terminating console");
    esp_console_deinit();
}
/***********************************************************************
 * END OF FILE
 **********************************************************************/