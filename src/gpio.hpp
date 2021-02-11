// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#pragma once

// Forward declaration to the peripheral header file
struct GPIO_Struct;

namespace gpio {

class GpioPort;
class GpioPin;

enum class Gpio { A, B, C, D, E, H };

enum class PinMode { Input, Output };

class GpioPort {
private:
  GPIO_Struct &m_gpio;
  unsigned int m_allocationTable = 0;

public:
  GpioPort(Gpio gpio);

  GpioPin allocatePin(unsigned int pin);
  void returnPin(GpioPin pin);
};

class GpioPin {
private:
  GpioPort &m_port;
  unsigned int m_pin;

public:
  GpioPin(GpioPort &port, unsigned int pin);
  ~GpioPin();

  void setMode(PinMode mode);

  void high();
  void low();
  void toggle();

  void write(bool value);
  bool read();
};

} // namespace gpio
