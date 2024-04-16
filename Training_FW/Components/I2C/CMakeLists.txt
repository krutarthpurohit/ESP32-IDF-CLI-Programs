set(srcs "Source/I2C_Development.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "." 
                    REQUIRES driver
                    REQUIRES ssd1306
                    REQUIRES app_oled)