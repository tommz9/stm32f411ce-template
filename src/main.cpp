// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include "clock.hpp"
#include "flash.hpp"
#include "system.hpp"
#include "gpio.hpp"

void configureSystem() {
  system::enableExtraExceptions();
  clock::enableCrystalClock();
  flash::enableAllCaches();
  clock::configureSysTick();
}

int main(void) {
  configureSystem();

  gpio::GpioPort portA(gpio::Gpio::A);

  auto ledPin = portA.allocatePin(12);
  ledPin.setMode(gpio::PinMode::Output);

  while (1) {
    ledPin.high();
    clock::delayMs(500);
    ledPin.low();
    clock::delayMs(500);
  }
  return 0;
}
