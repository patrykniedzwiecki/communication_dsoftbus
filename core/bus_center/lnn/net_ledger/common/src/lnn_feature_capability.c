/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "lnn_feature_capability.h"

#include <stdint.h>

#include "softbus_errcode.h"
#include "softbus_feature_config.h"
#include "softbus_log.h"

#define DEFAUTL_LNN_FEATURE 0x3E2 // 0x3EA

int32_t LnnSetFeatureCapability(uint64_t *feature, FeatureCapability capaBit)
{
    if (feature == NULL || capaBit >= BIT_FEATURE_COUNT) {
        LLOGE("in para error");
        return SOFTBUS_INVALID_PARAM;
    }
    *feature = (*feature) | (1 << (uint64_t)capaBit);
    return SOFTBUS_OK;
}

int32_t LnnClearFeatureCapability(uint64_t *feature, FeatureCapability capaBit)
{
    if (feature == NULL || capaBit >= BIT_FEATURE_COUNT) {
        LLOGE("in para error");
        return SOFTBUS_INVALID_PARAM;
    }
    *feature = (*feature) & (~(1 << (uint64_t)capaBit));
    return SOFTBUS_OK;
}

bool IsFeatureSupport(uint64_t feature, FeatureCapability capaBit)
{
    return ((feature & (1 << (uint64_t)capaBit)) != 0);
}

uint64_t LnnGetFeatureCapabilty(void)
{
    uint64_t configValue;
    if (SoftbusGetConfig(SOFTBUS_INT_LNN_SUPPORT_FEATURE,
        (unsigned char*)&configValue, sizeof(configValue)) != SOFTBUS_OK) {
        LLOGE("get lnn feature fail, use default value");
        configValue = DEFAUTL_LNN_FEATURE;
    }
    LLOGI("lnn feature is %lu", configValue);
    return configValue;
}