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

/**
 * This macro checks for the specified status, which is expected to commonly be
 * successful, and branches to the local label 'exit' if the status is
 * unsuccessful.
 *
 * @param[in]  aStatus     A scalar status to be evaluated against zero (0).
 *
 */
#define SuccessOrExit(aStatus) \
  do {                         \
    if ((aStatus) != 0) {      \
      goto exit;               \
    }                          \
  } while (false)

/**
 * This macro checks for the specified condition, which is expected to commonly
 * be true, and both executes @a ... and branches to the local label 'exit' if
 * the condition is false.
 *
 * @param[in]  aCondition  A Boolean expression to be evaluated.
 * @param[in]  aAction     An expression or block to execute when the assertion
 * fails.
 *
 */
#define VerifyOrExit(aCondition, aAction) \
  do {                                    \
    if (!(aCondition)) {                  \
      aAction;                            \
      goto exit;                          \
    }                                     \
  } while (false)

pw_os_error_t map_posix_to_osal_error(int ret);
