/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "lnn_net_builder_deps_mock.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS {
void *g_netBuilderDepsInterface;
NetBuilderDepsInterfaceMock::NetBuilderDepsInterfaceMock()
{
    g_netBuilderDepsInterface = reinterpret_cast<void *>(this);
}

NetBuilderDepsInterfaceMock::~NetBuilderDepsInterfaceMock()
{
    g_netBuilderDepsInterface = nullptr;
}

static NetBuilderDepsInterface *GetNetBuilderDepsInterface()
{
    return reinterpret_cast<NetBuilderDepsInterfaceMock *>(g_netBuilderDepsInterface);
}

extern "C" {
int32_t LnnGetSettingDeviceName(char *deviceName, uint32_t len)
{
    return GetNetBuilderDepsInterface()->LnnGetSettingDeviceName(deviceName, len);
}

int32_t AuthGetDeviceUuid(int64_t authId, char *uuid, uint16_t size)
{
    return GetNetBuilderDepsInterface()->AuthGetDeviceUuid(authId, uuid, size);
}

NodeInfo *LnnGetNodeInfoById(const char *id, IdCategory type)
{
    return GetNetBuilderDepsInterface()->LnnGetNodeInfoById(id, type);
}

int32_t LnnDeleteMetaInfo(const char *udid, ConnectionAddrType type)
{
    return GetNetBuilderDepsInterface()->LnnDeleteMetaInfo(udid, type);
}

int32_t TransGetConnByChanId(int32_t channelId, int32_t channelType, int32_t* connId)
{
    return GetNetBuilderDepsInterface()->TransGetConnByChanId(channelId, channelType, connId);
}

int32_t AuthMetaStartVerify(uint32_t connectionId, const uint8_t *key, uint32_t keyLen,
    uint32_t requestId, const AuthVerifyCallback *callBack)
{
    return GetNetBuilderDepsInterface()->AuthMetaStartVerify(connectionId, key, keyLen, requestId, callBack);
}

uint32_t AuthGenRequestId(void)
{
    return GetNetBuilderDepsInterface()->AuthGenRequestId();
}
}
}