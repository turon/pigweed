# Copyright 2020 The Pigweed Authors
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

load(
    "//pw_build:pigweed.bzl",
    "pw_cc_library",
    "pw_cc_test",
)

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache License 2.0

pw_cc_library(
    name = "pw_osal",
    srcs = [
        "posix/os_mutex.c",
        "posix/os_queue.cc",
        "posix/os_sem.c",
        "posix/os_task.c",
        "posix/os_time.c",
        "posix/os_timer.c",
        "posix/os_utils.c",
        "posix/os_utils.h",
        "posix/RingPthread.h",
        "posix/pw_osal_backend/os_port.h",
        "posix/pw_osal_backend/os_time.h",
        "posix/pw_osal_backend/os_types.h",
    ],
    hdrs = [
        "public/pw_osal/mutex.h",
        "public/pw_osal/osal.h",
        "public/pw_osal/queue.h",
        "public/pw_osal/sem.h",
        "public/pw_osal/task.h",
        "public/pw_osal/time.h",
        "public/pw_osal/timer.h",
        "public/Ring.h",
    ],
    includes = ["public"],
)

pw_cc_test(
    name = "test_os_mutex",
    srcs = [
        "tests/test_os_mutex.cc",
        "tests/test_util.h"
    ],
    deps = [
        ":pw_osal",
        "//pw_unit_test",
    ],
)

pw_cc_test(
    name = "test_os_sem",
    srcs = [
        "tests/test_os_sem.cc",
        "tests/test_util.h"
    ],
    deps = [
        ":pw_osal",
        "//pw_unit_test",
    ],
)

pw_cc_test(
    name = "test_os_queue",
    srcs = [
        "tests/test_os_queue.cc",
        "tests/test_util.h"
    ],
    deps = [
        ":pw_osal",
        "//pw_unit_test",
    ],
)

pw_cc_test(
    name = "test_os_task",
    srcs = [
        "tests/test_os_task.cc",
        "tests/test_util.h"
    ],
    deps = [
        ":pw_osal",
        "//pw_unit_test",
    ],
)

pw_cc_test(
    name = "test_os_timer",
    srcs = [
        "tests/test_os_timer.cc",
        "tests/test_util.h"
    ],
    deps = [
        ":pw_osal",
        "//pw_unit_test",
    ],
)

pw_cc_test(
    name = "test_ring",
    srcs = [
        "tests/test_ring.cc",
        "tests/test_util.h"
    ],
    deps = [
        ":pw_osal",
        "//pw_unit_test",
    ],
)
