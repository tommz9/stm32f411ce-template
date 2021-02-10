// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#pragma once

namespace flash {

// This needs to be called if the system freq is high (consult datasheet)
void setWaitStates(unsigned int waitStates);

void enableInstructionPrefetch();
void enableInstructionCache();
void enableDataCache();
void enableAllCaches();

} // namespace flash
