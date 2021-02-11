// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#pragma once

// Forward declaration to the peripheral header file
struct GPIO_Struct;

namespace gpio {

class Port;
class Pin;

enum class Gpio { A, B, C, D, E, H };

enum class PinMode { Input, Output };

class Port {
  friend class Pin;

private:
  GPIO_Struct &m_gpio;
  unsigned int m_allocationTable = 0;

  void returnPin(const Pin &pin);

public:
  Port(Gpio gpio);

  Pin allocatePin(unsigned int pin);
};

class Pin {
  friend class Port;

private:
  Port &m_port;
  unsigned int m_pin;

  Pin(Port &port, unsigned int pin);
  Pin(const Pin &) = delete;

public:
  ~Pin();

  void setMode(PinMode mode);

  void high();
  void low();
  void toggle();

  void write(bool value);
  bool read();
};

} // namespace gpio
