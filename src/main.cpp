// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include "clock.hpp"
#include "flash.hpp"
#include "gpio.hpp"
#include "system.hpp"

void configureSystem() {
  system::enableExtraExceptions();
  clock::enableCrystalClock();
  flash::enableAllCaches();
  clock::configureSysTick();
}

int main(void) {
  configureSystem();

  gpio::Port portA(gpio::Gpio::C);

  auto ledPin = portA.allocatePin(13);
  ledPin.setMode(gpio::PinMode::Output);

  while (1) {
    ledPin.high();
    clock::delayMs(500);
    ledPin.low();
    clock::delayMs(500);
  }
  return 0;
}
