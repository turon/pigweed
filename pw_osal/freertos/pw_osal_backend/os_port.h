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

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PW_OS_TIME_NO_WAIT 0
#define PW_OS_TIME_FOREVER portMAX_DELAY
#define PW_OS_TICKS_PER_SEC configTICK_RATE_HZ

#define PW_OS_PRIORITY_MIN 1
#define PW_OS_PRIORITY_MAX configMAX_PRIORITIES
#define PW_OS_PRIORITY_APP (PW_OS_PRIORITY_MIN + 1)

typedef BaseType_t pw_os_base_t;
typedef StackType_t pw_os_stack_t;

typedef TickType_t pw_os_time_t;
typedef int32_t pw_os_stime_t;

struct pw_os_mutex {
  SemaphoreHandle_t handle;
};

struct pw_os_sem {
  SemaphoreHandle_t handle;
};

struct pw_os_queue {
  QueueHandle_t handle;
};

struct pw_os_timer {
  TimerHandle_t handle;
  pw_os_timer_fn* func;
  void* arg;
};

struct pw_os_task {
  TaskHandle_t handle;
  pw_os_task_func_t func;
  void* arg;
};

static inline bool pw_os_os_started(void) {
  return xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
}

static inline uint16_t pw_os_sem_get_count(struct pw_os_sem* sem) {
  assert(sem);
  assert(sem->handle);
  return uxSemaphoreGetCount(sem->handle);
}

static inline pw_os_error_t pw_os_timer_stop(struct pw_os_timer* tm) {
  assert(tm);
  assert(tm->handle);
  return xTimerStop(tm->handle, portMAX_DELAY);
}

static inline bool pw_os_timer_is_active(struct pw_os_timer* tm) {
  assert(tm);
  assert(tm->handle);
  return xTimerIsTimerActive(tm->handle) == pdTRUE;
}

static inline pw_os_error_t pw_os_queue_init(struct pw_os_queue* queue,
                                             size_t msg_size,
                                             size_t max_msgs) {
  queue->handle = xQueueCreate(max_msgs, msg_size);
  return PW_OS_OK;
}

static inline int pw_os_queue_inited(const struct pw_os_queue* queue) {
  return (queue->handle != NULL);
}

pw_os_error_t pw_os_timer_start(struct pw_os_timer* timer, pw_os_time_t ticks);

static inline pw_os_time_t pw_os_time_ms_to_ticks(pw_os_time_t ms) {
  return (ms * PW_OS_TICKS_PER_SEC) / 1000;
}

static inline pw_os_time_t pw_os_time_ticks_to_ms(pw_os_time_t ticks) {
  return (ticks * 1000) / PW_OS_TICKS_PER_SEC;
}

static inline pw_os_time_t pw_os_time_get(void) {
  return xTaskGetTickCountFromISR();
}

static inline pw_os_time_t pw_os_time_get_ms(void) {
  return pw_os_time_ticks_to_ms(pw_os_time_get());
}

static inline pw_os_error_t pw_os_timer_start_ms(struct pw_os_timer* timer,
                                                 pw_os_time_t duration) {
  pw_os_time_t ticks = pw_os_time_ms_to_ticks(duration);
  return pw_os_timer_start(timer, ticks);
}

static inline pw_os_time_t pw_os_timer_get_ticks(struct pw_os_timer* tm) {
  assert(tm);
  assert(tm->handle);
  return xTimerGetExpiryTime(tm->handle);
}

static inline void* pw_os_timer_arg_get(struct pw_os_timer* timer) {
  assert(timer);
  return timer->arg;
}

static inline void pw_os_timer_arg_set(struct pw_os_timer* timer, void* arg) {
  assert(timer);
  timer->arg = arg;
}

static inline void pw_os_task_yield(void) { taskYIELD(); }

static inline void pw_os_task_sleep(pw_os_time_t ticks) { vTaskDelay(ticks); }

static inline void pw_os_task_sleep_ms(pw_os_time_t ms) {
  pw_os_task_sleep(pw_os_time_ms_to_ticks(ms));
}

static inline void* pw_os_get_current_task_id(void) {
  return xTaskGetCurrentTaskHandle();
}

static inline void pw_os_sched_start(void) { vTaskStartScheduler(); }

#ifdef __cplusplus
}
#endif
