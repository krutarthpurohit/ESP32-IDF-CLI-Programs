set(srcs "Source/pwm.c")
idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS Include
REQUIRES driver)