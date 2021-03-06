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

#include <string.h>

namespace std {

using ::size_t;

// Only a small subset of functions are exposed here.

using ::memchr;
using ::memcmp;
using ::memcpy;
using ::memmove;
using ::memset;

using ::strcat;
using ::strcpy;
using ::strncpy;

using ::strcmp;
using ::strlen;
using ::strncmp;

}  // namespace std
