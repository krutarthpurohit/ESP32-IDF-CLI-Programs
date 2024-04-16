set (srcs "Source/spi_protocol.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS include
REQUIRES driver                    )