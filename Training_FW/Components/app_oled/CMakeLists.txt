set(srcs "src/app_oled.c")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS include
REQUIRES driver ssd1306)