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
 * Timer
 */

/**
 * @brief Initialize a timer.
 *
 * This routine initializes a timer, prior to its first use.
 *
 * @param timer     Address of timer.
 * @param cb        Callback function to invoke once timer expires.
 * @param arg       Argument to pass to timer callback function.
 *
 * @retval PW_OS_OK Timer was created.
 * @retval PW_OS_ERROR Timer creation failed.
 */
pw_os_error_t pw_os_timer_init(struct pw_os_timer* timer,
                               pw_os_timer_fn cb,
                               void* arg);

/**
 * @brief Start a timer.
 *
 * This routine starts a timer, and resets its status to zero. The timer
 * begins counting down using the specified duration and period values.
 *
 * Attempting to start a timer that is already running is permitted.
 * The timer's status is reset to zero and the timer begins counting down
 * using the new duration and period values.
 *
 * @param timer     Address of timer.
 * @param duration  Initial timer duration [ticks].
 *
 * @retval PW_OS_OK Message received.
 * @retval PW_OS_EBUSY Returned without waiting.
 */
pw_os_error_t pw_os_timer_start_ms(struct pw_os_timer* timer,
                                   pw_os_time_t duration);

/**
 * @brief Start a timer.
 *
 * This routine starts a timer, and resets its status to zero. The timer
 * begins counting down using the specified duration and period values.
 *
 * Attempting to start a timer that is already running is permitted.
 * The timer's status is reset to zero and the timer begins counting down
 * using the new duration and period values.
 *
 * @param timer     Address of timer.
 * @param ticks     Initial timer duration [CPU ticks].
 *
 * @retval PW_OS_OK Message received.
 * @retval PW_OS_EBUSY Returned without waiting.
 */
pw_os_error_t pw_os_timer_start(struct pw_os_timer* timer, pw_os_time_t ticks);

/**
 * @brief Stop a timer.
 *
 * This routine stops a running timer prematurely. The timer's stop function,
 * if one exists, is invoked by the caller.
 *
 * Attempting to stop a timer that is not running is permitted, but has no
 * effect on the timer.
 *
 * @note Can be called by ISRs.  The stop handler has to be callable from ISRs
 * if @a pw_os_timer_stop is to be called from ISRs.
 *
 * @param timer     Address of timer.
 *
 * @return N/A
 */
pw_os_error_t pw_os_timer_stop(struct pw_os_timer* timer);

/**
 * @brief Check whether the given timer has been initialized.
 *
 * @param timer     Address of timer.
 *
 * @retval PW_OS_OK Timer is initialized.
 * @retval PW_OS_EINVAL Timer is invalid.
 */
pw_os_error_t pw_os_timer_inited(struct pw_os_timer* timer);

bool pw_os_timer_is_active(struct pw_os_timer* timer);

pw_os_time_t pw_os_timer_get_ticks(struct pw_os_timer* timer);

pw_os_time_t pw_os_timer_remaining_ticks(struct pw_os_timer* timer,
                                         pw_os_time_t time);

void pw_os_timer_arg_set(struct pw_os_timer* timer, void* arg);

void* pw_os_timer_arg_get(struct pw_os_timer* timer);

#ifdef __cplusplus
}
#endif
