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

#include "joinmetanode_fuzzer.h"
#include "client_bus_center.h"
#include <cstddef>
#include <cstring>
#include <securec.h>
#include "softbus_def.h"
#include "softbus_type_def.h"
#include "softbus_bus_center.h"

namespace OHOS {
    void JoinMetaNodeCb(ConnectionAddr *addr, const char *networkId, int32_t retCode)
    {
        (void) addr;
        (void) networkId;
        (void) retCode;
    }

    void LeaveMetaNodeCb(const char *networkId, int32_t retCode)
    {
        (void) networkId;
        (void) retCode;
    }

    ConnectionAddr addr;
    static const int32_t MAX_CONNECT_TYPE = CONNECTION_ADDR_MAX;
    static const char *g_ip = "192.168.43.16";
    static const int32_t port = 6007;

    void GenRandAddr(const uint8_t *data, size_t size)
    {
        addr.type = (ConnectionAddrType)(size % MAX_CONNECT_TYPE);
        memcpy_s(addr.peerUid, MAX_ACCOUNT_HASH_LEN, data, size);
        memcpy_s(addr.info.ip.ip, IP_STR_MAX_LEN, g_ip, strlen(g_ip));
        addr.info.ip.port = port + size;
    }

    bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
    {
        if (data == nullptr || size < sizeof(CustomData)) {
            return false;
        }

        char *pkgName = (char *)malloc(size);
        if (pkgName == nullptr) {
            return false;
        }
        if (memset_s(pkgName, size, '\0', size) != EOK) {
            free(pkgName);
            return false;
        }
        if (memcpy_s(pkgName, size, data, size - 1) != EOK) {
            free(pkgName);
            return false;
        }

        GenRandAddr(data, size);
        JoinMetaNode(reinterpret_cast<const char *>(pkgName), &addr, (CustomData *)data, JoinMetaNodeCb);
        LeaveMetaNode(reinterpret_cast<const char *>(pkgName),
                      reinterpret_cast<const char *>(pkgName), LeaveMetaNodeCb);
        free(pkgName);
        return true;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}

