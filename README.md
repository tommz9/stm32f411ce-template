# STM32F411CE Cmake Template (Blackpill)

This is a simple project template for STM32F411CE (Blackpill).

# Usage

```bash
cd stm32f411ce-template
mkdir build
cd build
cmake -Darm_toolchain=~/gcc-arm-none-eabi-10-2020-q4-major/ -DCMAKE_TOOLCHAIN_FILE=../arm-gcc-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

# Credit

This project contains several files from ST Micro, the vendor of he MCU. The files are in the folder `vendor`.
