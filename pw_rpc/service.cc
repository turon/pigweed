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

#include "pw_rpc/internal/service.h"

#include "pw_rpc/internal/packet.h"

namespace pw::rpc::internal {

void Service::ProcessPacket(const Packet& request,
                            Packet& response,
                            span<std::byte> payload_buffer) {
  response.set_service_id(id_);

  for (const Method& method : methods_) {
    if (method.id == request.method_id()) {
      // TODO(frolv): call the method i guess
      response.set_method_id(method.id);
    }
  }

  (void)payload_buffer;
}

}  // namespace pw::rpc::internal
