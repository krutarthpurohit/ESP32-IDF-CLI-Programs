
set(srcs "Source/Adc_development.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS include
                    PRIV_REQUIRES driver esp_adc)