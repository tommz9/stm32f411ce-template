// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#pragma once

namespace clock {
// Frequency of System Timer
const unsigned int sysTickFreq = 1000;

// Frequency of the crystal
const unsigned int installedCrystalFreq = 16'000'000;

enum class PeripheralClock { GpioA, GpioB, GpioC, GpioD, GpioE, GpioH };

// Switches the clock source to the crystal
void enableCrystalClock();

// Returns the frequency of the system clock
unsigned int getSysClk();

// Configures the System Timer Interrupt to fire with frequency sysTickFreq
void configureSysTick();

// Get the current tick
unsigned int getCurrentTick();

// Approximate delay function in ms
void delayMs(int ms);

// Must be called before the peripheral is used
void enablePeripheralClock(PeripheralClock clock);
void disablePeripheralClock(PeripheralClock clock);

} // namespace clock
