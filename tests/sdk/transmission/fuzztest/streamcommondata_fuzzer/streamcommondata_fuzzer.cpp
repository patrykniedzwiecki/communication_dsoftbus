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

#include "streamcommondata_fuzzer.h"
#include "stream_common_data.h"
#include "common_inner.h"
#include "stream_common.h"
#include <securec.h>
#include <memory>
#include <cstddef>
#include <cstdint>

using namespace std;

namespace OHOS {
    void InitStreamDataTest(const uint8_t* data, size_t size)
    {
        if ((data == nullptr) || (size < Communication::SoftBus::MAX_STREAM_LEN)) {
            return;
        }
        char *buf = new char[Communication::SoftBus::MAX_STREAM_LEN + 1];
        if (memcpy_s(buf, Communication::SoftBus::MAX_STREAM_LEN + 1,
            data, Communication::SoftBus::MAX_STREAM_LEN) != EOK) {
            return;
        }
        char *ext = new char[Communication::SoftBus::MAX_STREAM_LEN + 1];
        if (memcpy_s(ext, Communication::SoftBus::MAX_STREAM_LEN + 1,
            data, Communication::SoftBus::MAX_STREAM_LEN) != EOK) {
            return;
        }
        std::unique_ptr<char[]> inputbuf (buf);
        std::unique_ptr<char[]> inputext (ext);

        Communication::SoftBus::StreamCommonData streamcommondata;
        streamcommondata.InitStreamData(std::move(inputbuf), Communication::SoftBus::MAX_STREAM_LEN + 1,
            std::move(inputext), Communication::SoftBus::MAX_STREAM_LEN + 1);
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::InitStreamDataTest(data, size);
    return 0;
}

