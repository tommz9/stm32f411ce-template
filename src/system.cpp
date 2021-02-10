#include "system.hpp"

#include "stm32f4xx.h"

void system::enableExtraExceptions() {
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk | SCB_CCR_UNALIGN_TRP_Msk;
}
