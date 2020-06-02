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
 * Message queue
 */

/**
 * @brief Initialize a message queue.
 *
 * This routine initializes a message queue object, prior to its first use.
 *
 * Message queues deliver complete copies of fixed size messages from a producer
 * to a consumer in a thread-safe manner.
 *
 * @param msgq Address of the message queue.
 * @param msg_size Message size (in bytes).
 * @param max_msgs Maximum number of messages that can be queued.
 *
 * @return N/A
 */
pw_os_error_t pw_os_queue_init(struct pw_os_queue* msgq,
                               size_t msg_size,
                               size_t max_msgs);

/**
 * @brief Receive a message from a message queue.
 *
 * This routine receives a message from message queue @a q in a "first in,
 * first out" manner.
 *
 * @note Can be called by ISRs, but @a timeout must be set to
 * PW_OS_TIME_NO_WAIT.
 *
 * @param msgq Address of the message queue.
 * @param data Address of area to hold the received message.
 * @param timeout Waiting period to receive the message (in milliseconds),
 *                or one of the special values PW_OS_TIME_NO_WAIT and
 * PW_OS_TIME_FOREVER.
 *
 * @retval PW_OS_OK Message received.
 * @retval PW_OS_EBUSY Returned without waiting.
 * @retval PW_OS_TIMEOUT Waiting period timed out.
 */
pw_os_error_t pw_os_queue_get(struct pw_os_queue* msgq,
                              void* data,
                              pw_os_time_t timeout);

/**
 * @brief Send a message to a message queue.
 *
 * This routine sends a message to message queue @a q.
 *
 * @note Can be called by ISRs.
 *
 * @param msgq Address of the message queue.
 * @param data Pointer to the message.
 *
 * @retval PW_OS_OK Message sent.
 * @retval PW_OS_EBUSY Returned without waiting or queue purged.
 * @retval PW_OS_TIMEOUT Waiting period timed out.
 */
pw_os_error_t pw_os_queue_put(struct pw_os_queue* msgq, void* data);

/**
 * @brief Returns whether the given message queue is initialized and valid.
 *
 * @param msgq Address of the message queue.
 *
 * @retval PW_OS_OK Queue is valid.
 * @retval PW_OS_EINVAL Queue is not valid.
 */
int pw_os_queue_inited(const struct pw_os_queue* msgq);

bool pw_os_queue_is_empty(struct pw_os_queue* msgq);

void pw_os_queue_set_signal_cb(struct pw_os_queue* msgq,
                               pw_os_signal_fn signal_cb,
                               void* data);

#ifdef __cplusplus
}
#endif
