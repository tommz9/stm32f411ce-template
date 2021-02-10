# Copyright 2021 Tomas Barton, tommz9@gmail.com
#
# Licensed under the Apache License, Version 2.0

add_library(app STATIC)

target_sources(app PRIVATE
    clock.cpp 
    flash.cpp
    main.cpp
    power.cpp
)

target_include_directories(app PRIVATE
    ${PROJECT_SOURCE_DIR}/vendor/
)