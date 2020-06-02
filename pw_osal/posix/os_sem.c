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

#include <errno.h>
#include <pw_osal/osal.h>
#include <semaphore.h>
#include <time.h>

#include "os_utils.h"

#ifdef __APPLE__

pw_os_error_t pw_os_sem_init(struct pw_os_sem* sem, uint16_t tokens) {
  sem->lock = dispatch_semaphore_create(tokens);
  return (sem->lock == NULL) ? PW_OS_ENOMEM : PW_OS_OK;
}

pw_os_error_t pw_os_sem_give(struct pw_os_sem* sem) {
  int woke = dispatch_semaphore_signal(sem->lock);
  (void)woke;
  return PW_OS_OK;
}

pw_os_error_t pw_os_sem_take(struct pw_os_sem* sem, pw_os_time_t timeout) {
  int expired = dispatch_semaphore_wait(sem->lock, timeout);
  return (expired) ? PW_OS_TIMEOUT : PW_OS_OK;
}

#else

pw_os_error_t pw_os_sem_init(struct pw_os_sem* sem, uint16_t tokens) {
  int ret = sem_init(&sem->lock, 0, tokens);
  return map_posix_to_osal_error(ret);
}

pw_os_error_t pw_os_sem_give(struct pw_os_sem* sem) {
  int ret = sem_post(&sem->lock);
  return map_posix_to_osal_error(ret);
}

pw_os_error_t pw_os_sem_take(struct pw_os_sem* sem, pw_os_time_t timeout) {
  int ret;
  struct timespec wait;

  if (timeout == PW_OS_TIME_FOREVER) {
    ret = sem_wait(&sem->lock);
    SuccessOrExit(ret);
  } else {
    ret = clock_gettime(CLOCK_REALTIME, &wait);
    SuccessOrExit(ret);

    wait.tv_sec += timeout / 1000;
    wait.tv_nsec += (timeout % 1000) * 1000000;
    ret = sem_timedwait(&sem->lock, &wait);
    ret = (ret) ? errno : PW_OS_OK;
    SuccessOrExit(ret);
  }

exit:
  return map_posix_to_osal_error(ret);
}

#endif  // __APPLE__
