// Copyright 2020 The Pigweed Authors
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

#pragma once

#include <stdbool.h>

#if PW_DEVICE_LAYER_TARGET_NRF5
#include <nrf52840.h>

static inline bool chip_hw_in_isr() {
  /* XXX hw specific! */
  return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;
}

#else

static inline bool chip_hw_in_isr() { return false; }

#endif  // PW_DEVICE_LAYER_TARGET_NRF5
