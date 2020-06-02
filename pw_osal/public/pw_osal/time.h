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
 * Time functions
 */

/**
 * @brief Get system uptime.
 *
 * This routine returns the elapsed time since the system booted,
 * in milliseconds.
 *
 * @return Current uptime.
 */
pw_os_time_t pw_os_time_get(void);

pw_os_time_t pw_os_time_get_ms(void);

pw_os_time_t pw_os_time_ms_to_ticks(pw_os_time_t ms);

pw_os_time_t pw_os_time_ticks_to_ms(pw_os_time_t ticks);

#ifdef __cplusplus
}
#endif
