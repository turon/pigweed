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

#include <nlassert.h>
#include <pw_osal/osal.h>

#define SuccessOrExit(aStatus) nlEXPECT((aStatus) == PW_OS_OK, exit)

#define VerifyOrExit(aCondition, anAction) \
  nlEXPECT_ACTION(aCondition, exit, anAction)
