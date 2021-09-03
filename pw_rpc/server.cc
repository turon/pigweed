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

#include "pw_rpc/server.h"

#include <algorithm>

#include "pw_log/log.h"
#include "pw_rpc/internal/endpoint.h"
#include "pw_rpc/internal/packet.h"
#include "pw_rpc/server_context.h"

namespace pw::rpc {
namespace {

using std::byte;

using internal::Packet;
using internal::PacketType;

}  // namespace

Status Server::ProcessPacket(std::span<const byte> data,
                             ChannelOutput& interface) {
  internal::Call* call;
  Result<Packet> result = Endpoint::ProcessPacket(data, Packet::kServer, call);

  if (!result.ok()) {
    return result.status();
  }

  Packet& packet = *result;

  internal::Channel* channel = GetInternalChannel(packet.channel_id());
  if (channel == nullptr) {
    // If the requested channel doesn't exist, try to dynamically assign one.
    channel = AssignChannel(packet.channel_id(), interface);
    if (channel == nullptr) {
      // If a channel can't be assigned, send a RESOURCE_EXHAUSTED error. Never
      // send responses to error messages, though, to avoid infinite cycles.
      if (packet.type() != PacketType::CLIENT_ERROR) {
        internal::Channel temp_channel(packet.channel_id(), &interface);
        temp_channel
            .Send(Packet::ServerError(packet, Status::ResourceExhausted()))
            .IgnoreError();
      }
      return OkStatus();  // OK since the packet was handled
    }
  }

  const auto [service, method] = FindMethod(packet);

  if (method == nullptr) {
    // Don't send responses to errors to avoid infinite error cycles.
    if (packet.type() != PacketType::CLIENT_ERROR) {
      channel->Send(Packet::ServerError(packet, Status::NotFound()))
          .IgnoreError();
    }
    return OkStatus();  // OK since the packet was handled.
  }

  switch (packet.type()) {
    case PacketType::REQUEST: {
      // If the REQUEST is for an ongoing RPC, cancel it, then call it again.
      if (call != nullptr) {
        call->HandleError(Status::Cancelled());
      }

      internal::CallContext context(*this, *channel, *service, *method);
      method->Invoke(context, packet);
      break;
    }
    case PacketType::CLIENT_STREAM:
      HandleClientStreamPacket(packet, *channel, call);
      break;
    case PacketType::CLIENT_ERROR:
      if (call != nullptr) {
        call->HandleError(packet.status());
      }
      break;
    case PacketType::CANCEL:
      HandleCancelPacket(packet, *channel, call);
      break;
    case PacketType::CLIENT_STREAM_END:
      HandleClientStreamPacket(packet, *channel, call);
      break;
    default:
      channel->Send(Packet::ServerError(packet, Status::Unimplemented()))
          .IgnoreError();  // TODO(pwbug/387): Handle Status properly
      PW_LOG_WARN("Unable to handle packet of type %u",
                  unsigned(packet.type()));
  }
  return OkStatus();
}

std::tuple<Service*, const internal::Method*> Server::FindMethod(
    const internal::Packet& packet) {
  // Packets always include service and method IDs.
  auto service = std::find_if(services_.begin(), services_.end(), [&](auto& s) {
    return s.id() == packet.service_id();
  });

  if (service == services_.end()) {
    return {};
  }

  return {&(*service), service->FindMethod(packet.method_id())};
}

void Server::HandleClientStreamPacket(const internal::Packet& packet,
                                      internal::Channel& channel,
                                      internal::Call* call) const {
  if (call == nullptr) {
    PW_LOG_DEBUG(
        "Received client stream packet for method that is not pending");
    channel.Send(Packet::ServerError(packet, Status::FailedPrecondition()))
        .IgnoreError();  // TODO(pwbug/387): Handle Status properly
    return;
  }

  if (!call->has_client_stream()) {
    channel.Send(Packet::ServerError(packet, Status::InvalidArgument()))
        .IgnoreError();  // TODO(pwbug/387): Handle Status properly
    return;
  }

  if (!call->client_stream_open()) {
    channel.Send(Packet::ServerError(packet, Status::FailedPrecondition()))
        .IgnoreError();  // TODO(pwbug/387): Handle Status properly
    return;
  }

  if (packet.type() == PacketType::CLIENT_STREAM) {
    call->HandleClientStream(packet.payload());
  } else {  // Handle PacketType::CLIENT_STREAM_END.
    call->EndClientStream();
  }
}

void Server::HandleCancelPacket(const Packet& packet,
                                internal::Channel& channel,
                                internal::Call* call) const {
  if (call == nullptr) {
    channel.Send(Packet::ServerError(packet, Status::FailedPrecondition()))
        .IgnoreError();  // TODO(pwbug/387): Handle Status properly
    PW_LOG_DEBUG("Received CANCEL packet for method that is not pending");
  } else {
    call->HandleError(Status::Cancelled());
  }
}

}  // namespace pw::rpc
