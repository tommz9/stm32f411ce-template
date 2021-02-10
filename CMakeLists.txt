# Copyright 2021 Tomas Barton, tommz9@gmail.com
#
# Licensed under the Apache License, Version 2.0

cmake_minimum_required(VERSION 3.13)

project(stm32f411_template C CXX ASM)

if (NOT CMAKE_BUILD_TYPE )
    message(WARNING "Build type not specified.")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# The MCU architecture specs
set(arch_flags 
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -mthumb
    -mabi=aapcs
)

# Compiler and Linker options
set(common_flags
    $<$<C_COMPILER_ID:GNU>:--specs=nosys.specs>
    $<$<C_COMPILER_ID:GNU>:--specs=nano.specs>
)

# Compiler options
set(compile_flags
    -Wall -Wextra
    -Wshadow
    -Wdouble-promotion
    -Wformat=2 
    -Wformat-truncation
    -Wformat-signedness
    -Wundef
    -Wconversion
    -Werror
    $<$<COMPILE_LANGUAGE:CXX>:-Weffc++>
    -ffunction-sections 
    -fdata-sections 
    -fstack-usage 
    -fno-strict-aliasing 
    -fno-builtin 
    -ffast-math
    -fno-common
    -fstack-usage -Wstack-usage=256
    $<$<COMPILE_LANGUAGE:C>:-std=c11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
)

# Linker Options
set(link_flags
    -Wl,--gc-sections -static
    -T ${CMAKE_CURRENT_LIST_DIR}/vendor/STM32F411CEUX.ld
    -flto
    -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
    -Wl,--print-memory-usage
)

# Add folder-wise  options, will be passed to added subdirectories
add_compile_options(
    ${arch_flags}
    ${common_flags}
    ${compile_flags}
)

add_definitions(
    -DSTM32F411xE
)

# include after options have been defined
add_subdirectory("src/")
add_subdirectory("vendor/")

# add the executable
# all code comes from libraries -> need to have a dummy empty file
add_executable(stm32f411_template.elf dummy.c)

target_link_libraries(stm32f411_template.elf
    app
    vendor
)

target_link_options(stm32f411_template.elf PRIVATE 
    ${arch_flags} 
    ${common_flags}
    ${link_flags}
)

# Print size after build
# add_custom_command(TARGET stm32f411_template.elf POST_BUILD
#     COMMAND ${ARM_SIZE} --format=berkeley "stm32f411_template.elf"
#     COMMENT "Invoking: Cross ARM GNU Print Size"
# )

# Make the compilation fail if not formatted
# add_custom_command(TARGET stm32f411_template.elf PRE_BUILD
#     COMMAND clang-format --Werror --dry-run --style=llvm "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/src/*.hpp"
#     COMMENT "Invoking: Checking formatting."
# )
