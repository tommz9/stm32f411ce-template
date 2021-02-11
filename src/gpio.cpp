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

gpio::Port::Port(Gpio gpio) : m_gpio(selectGpio(gpio)) {
  clock::enablePeripheralClock(peripheralClockForGpio(gpio));
}

Pin gpio::Port::allocatePin(unsigned int pin) {
  // TODO: Error checking
  // TODO: Locking

  this->m_allocationTable |= 1U << pin;
  return Pin(*this, pin);
}

void gpio::Port::returnPin(const Pin &pin) {
  this->m_allocationTable &= ~(1U << pin.m_pin);
}

gpio::Pin::Pin(Port &port, unsigned int pin) : m_port(port), m_pin(pin) {}

gpio::Pin::~Pin() { this->m_port.returnPin(*this); }

void gpio::Pin::setMode(PinMode mode) {

  uint32_t shift = this->m_pin * 2;

  this->m_port.m_gpio.MODER &= ~(0x03U << shift);

  if (mode == PinMode::Output) {
    this->m_port.m_gpio.MODER |= 0x01U << (shift);
  }
}

void gpio::Pin::high() { this->m_port.m_gpio.BSRR = (1U << this->m_pin); }

void gpio::Pin::low() { this->m_port.m_gpio.BSRR = (1U << (this->m_pin + 16)); }

void gpio::Pin::toggle() { this->write(!this->read()); }

void gpio::Pin::write(bool value) {
  if (value) {
    this->high();
  } else {
    this->low();
  }
}

bool gpio::Pin::read() { return this->m_port.m_gpio.IDR & (1U << this->m_pin); }
