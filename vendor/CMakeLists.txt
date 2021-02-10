add_library(vendor OBJECT)

target_sources(vendor PRIVATE
    segger_fault_handler.c
    startup_stm32f411xe.s
    system_stm32f4xx.c
)
