/*
 * Copyright (C) 2016 Simon Fels <morphis@gravedo.de>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ANBOX_ANDROID_HOST_CONNECTOR_H_
#define ANBOX_ANDROID_HOST_CONNECTOR_H_

#include <memory>
#include <thread>
#include <atomic>

namespace anbox {
namespace bridge {
class PendingCallCache;
class RpcChannel;
} // namespace bridge
class LocalSocketConnection;
class MessageProcessor;
class AndroidApiSkeleton;
class PlatformApiStub;
class HostConnector {
public:
    HostConnector();
    ~HostConnector();

    void start();
    void stop();

    std::shared_ptr<anbox::PlatformApiStub> platform_api_stub() const;

private:
    void main_loop();

    std::shared_ptr<LocalSocketConnection> socket_;
    std::shared_ptr<bridge::PendingCallCache> pending_calls_;
    std::shared_ptr<AndroidApiSkeleton> android_api_skeleton_;
    std::shared_ptr<MessageProcessor> message_processor_;
    std::shared_ptr<bridge::RpcChannel> rpc_channel_;
    std::shared_ptr<anbox::PlatformApiStub> platform_api_stub_;
    std::thread thread_;
    std::atomic<bool> running_;
};
} // namespace anbox

#endif