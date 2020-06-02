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

#include <pw_osal/osal.h>

#include "RingPthread.h"

extern "C" {

typedef RingPthread ring_t;

pw_os_error_t pw_os_queue_init(struct pw_os_queue* msgq,
                               size_t msg_size,
                               size_t max_msgs) {
  msgq->q = new ring_t(msg_size, max_msgs);
  msgq->sig_cb = NULL;
  msgq->sig_arg = NULL;

  return (msgq->q) ? PW_OS_OK : PW_OS_ENOMEM;
}

void pw_os_queue_set_signal_cb(struct pw_os_queue* msgq,
                               pw_os_signal_fn signal_cb,
                               void* data) {
  msgq->sig_cb = signal_cb;
  msgq->sig_arg = data;
}

bool pw_os_queue_is_empty(struct pw_os_queue* msgq) {
  ring_t* q = static_cast<ring_t*>(msgq->q);

  if (q->size()) {
    return 1;
  } else {
    return 0;
  }
}

int pw_os_queue_inited(const struct pw_os_queue* msgq) {
  return (msgq->q != NULL);
}

pw_os_error_t pw_os_queue_put(struct pw_os_queue* msgq, void* data) {
  ring_t* q = static_cast<ring_t*>(msgq->q);
  q->put(data);

  if (msgq->sig_cb) {
    msgq->sig_cb(msgq->sig_arg);
  }

  return PW_OS_OK;
}

pw_os_error_t pw_os_queue_get(struct pw_os_queue* msgq,
                              void* data,
                              pw_os_time_t tmo) {
  ring_t* q = static_cast<ring_t*>(msgq->q);
  bool success = q->get(data, tmo);

  return (success) ? PW_OS_OK : PW_OS_TIMEOUT;
}

}  // extern "C"
