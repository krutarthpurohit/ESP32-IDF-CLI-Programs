set (srcs "Source/Cli_development.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS include .
REQUIRES driver console vfs nvs_flash UART Pwm_Developement GPIO ADC I2C SPI_Protocol)
