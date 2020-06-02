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

#include "os_utils.h"

#include <errno.h>
#include <pthread.h>
#include <pw_osal/osal.h>

pw_os_error_t map_posix_to_osal_error(int ret) {
  pw_os_error_t err;

  switch (ret) {
    case 0:
      err = PW_OS_OK;
      break;

    case ENOMEM:
      err = PW_OS_ENOMEM;
      break;
    case ETIMEDOUT:
      err = PW_OS_TIMEOUT;
      break;
    case EBUSY:
      err = PW_OS_EBUSY;
      break;
    case EINVAL:
      err = PW_OS_EINVAL;
      break;
    case EDEADLK:
      err = PW_OS_BAD_MUTEX;
      break;
    case EPERM:
      err = PW_OS_ERR_PRIV;
      break;
    default:
      err = PW_OS_ERROR;
      break;
  }

  return err;
}
