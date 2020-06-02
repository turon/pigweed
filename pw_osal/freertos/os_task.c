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

void pw_os_task_dispatch(void* arg) {
  struct pw_os_task* task = (struct pw_os_task*)arg;

  assert(task);
  assert(task->func);
  task->func(task->arg);
}

pw_os_error_t pw_os_task_init(struct pw_os_task* task,
                              const char* name,
                              pw_os_task_func_t func,
                              void* arg,
                              uint8_t prio,
                              uint16_t stack_size) {
  pw_os_base_t err;

  if ((task == NULL) || (func == NULL)) {
    return PW_OS_INVALID_PARAM;
  }

  task->func = func;
  task->arg = arg;

  err = xTaskCreate(pw_os_task_dispatch,
                    name,
                    stack_size / sizeof(pw_os_base_t),
                    task,
                    prio,
                    &task->handle);

  return (err == pdPASS) ? PW_OS_OK : PW_OS_ENOMEM;
}
