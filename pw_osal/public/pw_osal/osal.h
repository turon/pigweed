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

#include <pw_status/status.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void pw_os_timer_fn(void* arg);
typedef void pw_os_signal_fn(void* arg);
typedef void* (*pw_os_task_func_t)(void*);

enum pw_os_error {
  PW_OS_OK = PW_STATUS_OK,
  PW_OS_ENOMEM = PW_STATUS_RESOURCE_EXHAUSTED,
  PW_OS_EINVAL = PW_STATUS_UNKNOWN,
  PW_OS_INVALID_PARAM = PW_STATUS_INVALID_ARGUMENT,
  PW_OS_MEM_NOT_ALIGNED = PW_STATUS_FAILED_PRECONDITION,
  PW_OS_BAD_MUTEX = PW_STATUS_RESOURCE_EXHAUSTED,
  PW_OS_TIMEOUT = PW_STATUS_DEADLINE_EXCEEDED,
  PW_OS_ERR_IN_ISR = PW_STATUS_FAILED_PRECONDITION,
  PW_OS_ERR_PRIV = PW_STATUS_UNAUTHENTICATED,
  PW_OS_OS_NOT_STARTED = PW_STATUS_FAILED_PRECONDITION,
  PW_OS_ENOENT = PW_STATUS_FAILED_PRECONDITION,
  PW_OS_EBUSY = PW_STATUS_UNAVAILABLE,
  PW_OS_ERROR = PW_STATUS_UNKNOWN,
};

typedef enum pw_os_error pw_os_error_t;

/* Include OS-specific definitions */
#include "pw_osal_backend/os_port.h"

#ifdef __cplusplus
}
#endif
