add_library(vendor STATIC)

target_sources(vendor PRIVATE
    startup_stm32f411xe.s
    system_stm32f4xx.c
)
