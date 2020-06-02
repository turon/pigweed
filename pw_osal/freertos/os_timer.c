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

#include <pw_osal/osal.h>

#include "os_hw.h"

static void pw_os_timer_cb(TimerHandle_t freertosTimer) {
  struct pw_os_timer* timer = pvTimerGetTimerID(freertosTimer);
  assert(timer);

  pw_os_timer_stop(timer);

  timer->func(timer->arg);
}

pw_os_error_t pw_os_timer_init(struct pw_os_timer* timer,
                               pw_os_timer_fn* tm_cb,
                               void* tm_arg) {
  memset(timer, 0, sizeof(*timer));
  timer->func = tm_cb;
  timer->arg = tm_arg;
  timer->handle = xTimerCreate("timer", 1, pdFALSE, timer, pw_os_timer_cb);

  return PW_OS_OK;
}

pw_os_error_t pw_os_timer_start(struct pw_os_timer* timer, pw_os_time_t ticks) {
  BaseType_t woken1, woken2, woken3;

  if (ticks < 0) {
    return PW_OS_INVALID_PARAM;
  }

  if (ticks == 0) {
    ticks = 1;
  }

  if (chip_hw_in_isr()) {
    xTimerStopFromISR(timer->handle, &woken1);
    xTimerChangePeriodFromISR(timer->handle, ticks, &woken2);
    xTimerResetFromISR(timer->handle, &woken3);

    portYIELD_FROM_ISR(woken1 || woken2 || woken3);
  } else {
    xTimerStop(timer->handle, portMAX_DELAY);
    xTimerChangePeriod(timer->handle, ticks, portMAX_DELAY);
    xTimerReset(timer->handle, portMAX_DELAY);
  }

  return PW_OS_OK;
}

pw_os_time_t pw_os_timer_remaining_ticks(struct pw_os_timer* timer,
                                         pw_os_time_t now) {
  pw_os_time_t rt;
  uint32_t exp;

  exp = xTimerGetExpiryTime(timer->handle);

  if (exp > now) {
    rt = exp - now;
  } else {
    rt = 0;
  }

  return rt;
}
