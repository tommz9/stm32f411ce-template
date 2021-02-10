// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include "clock.hpp"
#include "flash.hpp"

void configureSysem() {
  clock::enableCrystalClock();
  flash::enableAllCaches();
  clock::configureSysTick();
}

int main(void) {
  configureSysem();

  while (1) {
    clock::delayMs(1000);
  }
  return 0;
}
