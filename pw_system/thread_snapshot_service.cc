// Copyright 2022 The Pigweed Authors
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

#include "pw_system/thread_snapshot_service.h"

#include "pw_thread/thread_snapshot_service.h"

namespace pw::system {
namespace {

thread::ThreadSnapshotServiceBuilder<> system_thread_snapshot_service;

}  // namespace

void RegisterThreadSnapshotService(rpc::Server& rpc_server) {
  rpc_server.RegisterService(system_thread_snapshot_service);
}

}  // namespace pw::system
