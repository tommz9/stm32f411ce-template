// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include "power.hpp"

#include "stm32f4xx.h"

void power::setRegulatorVoltageScaling(VoltageScale scale) {
  PWR->CR =
      (PWR->CR & ~PWR_CR_VOS_Msk) | (((unsigned int)scale) << PWR_CR_VOS_Pos);
}
