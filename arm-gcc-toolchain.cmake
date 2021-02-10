# Copyright 2021 Tomas Barton, tommz9@gmail.com
#
# Licensed under the Apache License, Version 2.0

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)


set(arm_toolchain "Not Defined" CACHE PATH "Path to the arm toolchain folder.")


set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(UNIX)
    set(CMAKE_C_COMPILER   ${arm_toolchain}/bin/arm-none-eabi-gcc CACHE INTERNAL "")
    set(CMAKE_CXX_COMPILER ${arm_toolchain}/bin/arm-none-eabi-g++ CACHE INTERNAL "")
    set(ARM_SIZE ${arm_toolchain}/bin/arm-none-eabi-size CACHE INTERNAL "")
elseif(WIN32)
    set(CMAKE_C_COMPILER   ${arm_toolchain}/bin/arm-none-eabi-gcc.exe CACHE INTERNAL "")
    set(CMAKE_CXX_COMPILER ${arm_toolchain}/bin/arm-none-eabi-g++.exe CACHE INTERNAL "")
    set(ARM_SIZE ${arm_toolchain}/bin/arm-none-eabi-size.exe CACHE INTERNAL "")
endif()

set(CMAKE_C_FLAGS_DEBUG "-g3 -Og -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG")

set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Og -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG")
