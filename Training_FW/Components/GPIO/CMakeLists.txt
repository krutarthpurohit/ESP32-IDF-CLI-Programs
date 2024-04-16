# Set the source files for the component
set (srcs "source/GPIO_Development.c")

# Register the component
idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "Include"
                    REQUIRES driver freertos console)
