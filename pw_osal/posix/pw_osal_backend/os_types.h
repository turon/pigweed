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

/**
 *    @file
 *          Provides an definitions of Pigweed OSAL data structures for
 * portability to POSIX platforms.
 */

#pragma once

#include <pthread.h>
#include <semaphore.h>

#ifdef __APPLE__
#include <dispatch/dispatch.h>
#endif

/* The highest and lowest task priorities */
#define PW_OS_PRIORITY_MIN (sched_get_priority_min(SCHED_RR))
#define PW_OS_PRIORITY_MAX (sched_get_priority_max(SCHED_RR))
#define PW_OS_PRIORITY_APP (PW_OS_PRIORITY_MIN + 1)

typedef int pw_os_base_t;
typedef int pw_os_stack_t;

struct pw_os_task {
  pthread_t handle;
  pthread_attr_t attr;
  struct sched_param param;
  const char* name;
};

struct pw_os_queue {
  void* q;
  pw_os_signal_fn* sig_cb;
  void* sig_arg;
};

struct pw_os_mutex {
  pthread_mutex_t lock;
  pthread_mutexattr_t attr;
  struct timespec wait;
};

struct pw_os_sem {
#ifdef __APPLE__
  dispatch_semaphore_t lock;
#else
  sem_t lock;
#endif
};
