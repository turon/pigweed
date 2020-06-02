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
 * Semaphores
 */

/**
 * @brief Initialize a semaphore.
 *
 * This routine initializes a semaphore object, prior to its first use.
 *
 * @param sem Address of the semaphore.
 * @param tokens Initial semaphore count.
 *
 * @return N/A
 */
pw_os_error_t pw_os_sem_init(struct pw_os_sem* sem, uint16_t tokens);

/**
 * @brief Take a semaphore.
 *
 * This routine takes @a sem.
 *
 * @note Can be called by ISRs, but @a timeout must be set to
 * PW_OS_TIME_NO_WAIT.
 *
 * @param sem Address of the semaphore.
 * @param timeout Waiting period to take the semaphore (in milliseconds),
 *                or one of the special values PW_OS_TIME_NO_WAIT and
 * PW_OS_TIME_FOREVER.
 *
 * @retval PW_OS_OK Semaphore taken.
 * @retval PW_OS_EBUSY Returned without waiting.
 * @retval PW_OS_TIMEOUT Waiting period timed out.
 */
pw_os_error_t pw_os_sem_take(struct pw_os_sem* sem, pw_os_time_t timeout);

/**
 * @brief Give a semaphore.
 *
 * This routine gives @a sem, unless the semaphore is already at its maximum
 * permitted count.
 *
 * @note Can be called by ISRs.
 *
 * @param sem Address of the semaphore.
 *
 * @return N/A
 */
pw_os_error_t pw_os_sem_give(struct pw_os_sem* sem);

#ifdef __cplusplus
}
#endif
