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

#include <assert.h>
#include <pw_osal/osal.h>
#include <stddef.h>
#include <string.h>

#include "os_hw.h"

pw_os_error_t pw_os_queue_get(struct pw_os_queue* queue,
                              void* data,
                              pw_os_time_t tmo) {
  BaseType_t woken;
  BaseType_t ret;

  if (chip_hw_in_isr()) {
    assert(tmo == 0);
    ret = xQueueReceiveFromISR(queue->handle, data, &woken);
    portYIELD_FROM_ISR(woken);
  } else {
    ret = xQueueReceive(queue->handle, data, tmo);
  }
  assert(ret == pdPASS || ret == errQUEUE_EMPTY);

  return PW_OS_OK;
}

pw_os_error_t pw_os_queue_put(struct pw_os_queue* queue, void* data) {
  BaseType_t woken;
  BaseType_t ret;

  if (chip_hw_in_isr()) {
    ret = xQueueSendToBackFromISR(queue->handle, data, &woken);
    portYIELD_FROM_ISR(woken);
  } else {
    ret = xQueueSendToBack(queue->handle, data, portMAX_DELAY);
  }

  assert(ret == pdPASS);

  return PW_OS_OK;
}
