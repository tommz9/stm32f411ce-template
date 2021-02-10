// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#pragma once

namespace power {

enum class VoltageScale : unsigned int {
  Reserved = 0U,
  Scale3 = 1U,
  Scale2 = 2U,
  Scale1 = 3U
};

// This needs to be configured is CPU freq is high (consult datasheet)
void setRegulatorVoltageScaling(VoltageScale scale);

} // namespace power