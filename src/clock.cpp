// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include "clock.hpp"

#include "stm32f4xx.h"

#include "flash.hpp"
#include "power.hpp"

using namespace clock;

// millisecond counter
volatile static unsigned int ticks = 0;

static unsigned int systemClk = 16'000'000U;

extern "C" void SysTick_Handler() { ++ticks; }

void clock::enableCrystalClock() {
  // Enable the crystal oscillator
  RCC->CR |= RCC_CR_HSEON;

  // Wait for the oscillator to start
  while (!(RCC->CR & RCC_CR_HSERDY)) {
  }

  // Configure PLL
  RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; // HSE as the source

  // The the input to VCO can be max 2 MHz
  RCC->PLLCFGR |= (25U << RCC_PLLCFGR_PLLM_Pos);

  // VCO Out should be 192 MHz here given 25MHz crystal
  RCC->PLLCFGR |= (192U << RCC_PLLCFGR_PLLN_Pos);

  // Main System Clock divider (max 100 MHz), 0U is division by 2 Main clock
  // should be 96 MHz
  RCC->PLLCFGR |= (0U << RCC_PLLCFGR_PLLP_Pos);

  // 48 MHz clock for USB
  RCC->PLLCFGR |= (4U << RCC_PLLCFGR_PLLQ_Pos);

  // Set power level to the highest state (needed for system clock > 90 MHz)
  // Needs to be enabled before PLL
  power::setRegulatorVoltageScaling(power::VoltageScale::Scale1);

  // Enable PLL
  RCC->CR |= RCC_CR_PLLON;

  // Wait for PLL to stabilize
  while (!(RCC->CR & RCC_CR_PLLRDY)) {
  }

  // Set Wait states for flash access (Table 5 datasheet)
  flash::setWaitStates(3);

  // Clock down the APB low speed bus (should be 50 MHz)
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

  // Use PLL as the system clock
  RCC->CFGR |= RCC_CFGR_SW_PLL;

  systemClk = 96'000'000U;
}

unsigned int clock::getSysClk() { return systemClk; }

void clock::configureSysTick() {
  // This function switches the clock source to the System Clock (not  AHB
  // divided by 8)
  SysTick_Config(getSysClk() / sysTickFreq);
}

unsigned int clock::getCurrentTick() { return ticks; }

void clock::delayMs(int ms) {
  unsigned int wait_until = getCurrentTick() + ms;

  while (getCurrentTick() < wait_until) {
  }

  // TODO: Maybe deal with overflow?
}

void clock::enablePeripheralClock(PeripheralClock clock) {
  // TODO: Should be locked
  switch (clock) {
  case PeripheralClock::GpioA:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    break;
  case PeripheralClock::GpioB:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    break;
  case PeripheralClock::GpioC:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    break;
  case PeripheralClock::GpioD:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    break;
  case PeripheralClock::GpioE:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    break;
  case PeripheralClock::GpioH:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    break;
  }
}

void clock::disablePeripheralClock(PeripheralClock clock) {
  // TODO: Should be locked
  switch (clock) {
  case PeripheralClock::GpioA:
    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
    break;
  case PeripheralClock::GpioB:
    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
    break;
  case PeripheralClock::GpioC:
    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
    break;
  case PeripheralClock::GpioD:
    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
    break;
  case PeripheralClock::GpioE:
    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
    break;
  case PeripheralClock::GpioH:
    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
    break;
  }
}
