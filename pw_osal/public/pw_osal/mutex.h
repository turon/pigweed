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

#include <pw_osal/osal.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Mutexes
 */

/**
 * @brief Initialize a mutex.
 *
 * This routine initializes a mutex object, prior to its first use.
 *
 * Upon completion, the mutex is available and does not have an owner.
 *
 * @param mutex Address of the mutex.
 *
 * @return N/A
 */
pw_os_error_t pw_os_mutex_init(struct pw_os_mutex* mutex);

/**
 * @brief Lock a mutex.
 *
 * This routine locks @a mutex. If the mutex is locked by another task,
 * the calling task waits until the mutex becomes available or until
 * a timeout occurs.
 *
 * A task is permitted to lock a mutex it has already locked. The operation
 * completes immediately and the lock count is increased by 1.
 *
 * @param mutex Address of the mutex.
 * @param timeout Waiting period to lock the mutex (in milliseconds),
 *                or one of the special values PW_OS_TIME_NO_WAIT and
 * PW_OS_TIME_FOREVER.
 *
 * @retval PW_OS_OK Mutex locked.
 * @retval PW_OS_EBUSY Returned without waiting.
 * @retval PW_OS_TIMEOUT Waiting period timed out.
 */
pw_os_error_t pw_os_mutex_take(struct pw_os_mutex* mutex, pw_os_time_t timeout);

/**
 * @brief Unlock a mutex.
 *
 * This routine unlocks @a mutex. The mutex must already be locked by the
 * calling task.
 *
 * The mutex cannot be claimed by another task until it has been unlocked by
 * the calling task as many times as it was previously locked by that
 * task.
 *
 * @param mutex Address of the mutex.
 *
 * @return N/A
 */
pw_os_error_t pw_os_mutex_give(struct pw_os_mutex* mutex);

#ifdef __cplusplus
}
#endif
