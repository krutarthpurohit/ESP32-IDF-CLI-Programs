set (srcs "Source/Uart_development.c")
idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS include
REQUIRES driver)