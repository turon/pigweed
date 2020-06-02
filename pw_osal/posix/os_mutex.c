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
#include <pthread.h>
#include <pw_osal/osal.h>

#include "os_utils.h"

pw_os_error_t pw_os_mutex_init(struct pw_os_mutex* mu) {
  int ret = 0;

  ret = pthread_mutexattr_init(&mu->attr);
  SuccessOrExit(ret);

  ret = pthread_mutexattr_settype(&mu->attr, PTHREAD_MUTEX_RECURSIVE);
  SuccessOrExit(ret);

  ret = pthread_mutex_init(&mu->lock, &mu->attr);
  SuccessOrExit(ret);

exit:
  return (ret) ? PW_OS_BAD_MUTEX : PW_OS_OK;
}

pw_os_error_t pw_os_mutex_give(struct pw_os_mutex* mu) {
  int ret = (pthread_mutex_unlock(&mu->lock));
  SuccessOrExit(ret);

exit:
  return map_posix_to_osal_error(ret);
}

pw_os_error_t pw_os_mutex_take(struct pw_os_mutex* mu, pw_os_time_t timeout) {
  int ret;

#ifdef __APPLE__
  ret = pthread_mutex_lock(&mu->lock);
  SuccessOrExit(ret);
#else
  if (timeout == PW_OS_TIME_FOREVER) {
    ret = pthread_mutex_lock(&mu->lock);
    SuccessOrExit(ret);
  } else {
    ret = clock_gettime(CLOCK_REALTIME, &mu->wait);
    SuccessOrExit(ret);

    mu->wait.tv_sec += timeout / 1000;
    mu->wait.tv_nsec += (timeout % 1000) * 1000000;

    ret = pthread_mutex_timedlock(&mu->lock, &mu->wait);
    SuccessOrExit(ret);
  }
#endif

exit:
  return map_posix_to_osal_error(ret);
}
