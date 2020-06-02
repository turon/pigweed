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

pw_os_error_t pw_os_mutex_init(struct pw_os_mutex* mu) {
  if (!mu) {
    return PW_OS_INVALID_PARAM;
  }

  mu->handle = xSemaphoreCreateRecursiveMutex();
  assert(mu->handle);

  return (mu->handle == NULL) ? PW_OS_BAD_MUTEX : PW_OS_OK;
}

pw_os_error_t pw_os_mutex_take(struct pw_os_mutex* mu, pw_os_time_t timeout) {
  BaseType_t ret;

  assert(!chip_hw_in_isr());

  if (!mu) {
    return PW_OS_INVALID_PARAM;
  }

  assert(mu->handle);

  ret = xSemaphoreTakeRecursive(mu->handle, timeout);

  return ret == pdPASS ? PW_OS_OK : PW_OS_TIMEOUT;
}

pw_os_error_t pw_os_mutex_give(struct pw_os_mutex* mu) {
  assert(!chip_hw_in_isr());

  if (!mu) {
    return PW_OS_INVALID_PARAM;
  }

  assert(mu->handle);

  if (xSemaphoreGiveRecursive(mu->handle) != pdPASS) {
    return PW_OS_BAD_MUTEX;
  }

  return PW_OS_OK;
}
