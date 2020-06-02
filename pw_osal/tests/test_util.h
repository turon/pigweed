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

#include <gtest/gtest.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define PASS (0)
//#define FAIL (-1)

#define SuccessOrQuit(ERR, MSG) \
  EXPECT_EQ(ERR, 0)  // << "\nFAILED " << __FUNCTION__ << ":line #" << __LINE__
                     // << " - " << MSG << "\n"

#define VerifyOrQuit(TST, MSG) \
  EXPECT_TRUE(TST)  // << "\nFAILED " << __FUNCTION__ << ":line #" << __LINE__
                    // << " - " << MSG << "\n"

#if DEBUG
#include <stdio.h>
#define TEST_LOG(...) printf(__VA_ARGS__)
#else
#define TEST_LOG(...)
#endif

#ifdef __cplusplus
}
#endif
