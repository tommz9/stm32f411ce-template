// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include "clock.hpp"
#include "flash.hpp"
#include "system.hpp"

void configureSystem() {
  system::enableExtraExceptions();
  clock::enableCrystalClock();
  flash::enableAllCaches();
  clock::configureSysTick();
}

int main(void) {
  configureSystem();

  while (1) {
    clock::delayMs(1000);
  }
  return 0;
}
