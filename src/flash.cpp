// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include "flash.hpp"

#include "stm32f4xx.h"

void flash::setWaitStates(unsigned int waitStates) {

  if (waitStates > 15) {
    // TODO: Fatal error
    return;
  }

  FLASH->ACR |= waitStates << FLASH_ACR_LATENCY_Pos;
}

void flash::enableInstructionPrefetch() { FLASH->ACR |= FLASH_ACR_PRFTEN; }

void flash::enableInstructionCache() { FLASH->ACR |= FLASH_ACR_ICEN; }

void flash::enableDataCache() { FLASH->ACR |= FLASH_ACR_DCEN; }

void flash::enableAllCaches() {
  enableInstructionPrefetch();
  enableInstructionCache();
  enableDataCache();
}
