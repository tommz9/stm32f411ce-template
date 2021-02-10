# STM32F411CE Cmake Template (Blackpill)

This is a simple project template for STM32F411CE (Blackpill).

## Features

Implemented:

- build a binary file for STM32F411
- works under Linux and Windows
- uses ARM GNU toolchain

Planned:

- build using clang (LLVM)
- support for unit testing under the host

# Usage

Requirements: cmake, make, ARM Toolchain (from ARM or your distribution package system)

## Linux

```bash
cd stm32f411ce-template
mkdir build
cd build
cmake -Darm_toolchain=~/gcc-arm-none-eabi-10-2020-q4-major/ -DCMAKE_TOOLCHAIN_FILE=../arm-gcc-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

## Windows

On windows you will need to get `make` installed. The easies way seems to be getting it from Chocolatey.

1. go to https://chocolatey.org/install
2. Install Chocolatey
3. then `choco install make` in the terminal

Cmake and ARM Toolchain can be installed using installer packages. 

- https://cmake.org/download/
- https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

I like to used cmake-gui on Windows (because I find it difficult to type paths in windows shell):

1. Open cmake-gui
2. Select your source folder.
3. Select build folder (usually a folder named `build` in the root of the project).
4. Click "Configure"
5. In the dialog window select "Unix Makefiles" and "Specify toolchain file for cross-compiling".
6. Browse for the toolchain file.
7. Error will show up. Fill out `arm_toolchain` to point at the installation of the ARM toolchain. Usually "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2020-q4-major".
8. Select `CMAKE_BUILD_TYPE` to either "Debug" or "Release".
9. Run Configure again. It should work now.
10. Run Generate.
11. Open a powershell window in the "build" folder. Open the folder in Explorer, Shift+Right-click anywhere in the folder and select "Open Powershell window here".
12. Type `make`.

Another useful options options are `make clean` to remove build artifacts, `make VERBOSE=1` to show how the compiler is invoked with all parameters. 

## Adding new files and folders

Create a new `.c` or `.cpp` file and add it to the `CMakeLists.txt` in the folder with the source, ie `src/CMakeLists.txt`.

If a new root level folder is needed, create the folder and then copy the `src/CMakeLists.txt` file into the new folder. Modify the file to include sources files in the new folder and give the target a unique name (ie. rename `app` to something else). Then modify the root `CMakeLists.txt` to `add_subdirectory("new_folder")` and also add the new target to `target_link_libraries`.

# Alternatives

- https://github.com/ObKo/stm32-cmake an excellent project that provides CMake targets for the entire lineup of STM32 Arm Cortex MCUs. This works well and is easy to use, however it is a complex project with many features therefore I decided to create something simpler. 

# Credit

This project contains several files from ST Micro, the vendor of he MCU. The files are in the folder `vendor`.

There is also a hard fault handler from SEGGER https://wiki.segger.com/Cortex-M_Fault
