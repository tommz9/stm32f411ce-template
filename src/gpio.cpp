// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include "gpio.hpp"

#include "clock.hpp"
#include "stm32f4xx.h"

using namespace gpio;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
static constexpr GPIO_Struct &selectGpio(Gpio gpio) {
  switch (gpio) {
  case Gpio::A:
    return *GPIOA;
  case Gpio::B:
    return *GPIOB;
  case Gpio::C:
    return *GPIOC;
  case Gpio::D:
    return *GPIOD;
  case Gpio::E:
    return *GPIOE;
  case Gpio::H:
    return *GPIOH;
  }
}

static constexpr clock::PeripheralClock peripheralClockForGpio(Gpio gpio) {
  switch (gpio) {
  case Gpio::A:
    return clock::PeripheralClock::GpioA;
  case Gpio::B:
    return clock::PeripheralClock::GpioB;
  case Gpio::C:
    return clock::PeripheralClock::GpioC;
  case Gpio::D:
    return clock::PeripheralClock::GpioD;
  case Gpio::E:
    return clock::PeripheralClock::GpioE;
  case Gpio::H:
    return clock::PeripheralClock::GpioH;
  }
}
#pragma GCC diagnostic pop

gpio::GpioPort::GpioPort(Gpio gpio) : m_gpio(selectGpio(gpio)) {
  clock::enablePeripheralClock(peripheralClockForGpio(gpio));
}

GpioPin gpio::GpioPort::allocatePin(unsigned int pin) {
  // TODO: Error checking

  this->m_allocationTable |= 1U << pin;
  return GpioPin(*this, pin);
}

gpio::GpioPin::GpioPin(GpioPort &port, unsigned int pin):
    m_port(port), m_pin(pin)
{
}


gpio::GpioPin::~GpioPin(){
    this->m_port.returnPin(*this);
}

// void gpio::GpioPin::setMode(PinMode mode){

// }

void gpio::GpioPin::high(){
    this->write(true);
}
void gpio::GpioPin::low(){
    this->write(false);
}
//void gpio::GpioPin::toggle();

//void gpio::GpioPin::write(bool value);
//bool gpio::GpioPin::read();
