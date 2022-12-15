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

#include <gtest/gtest.h>
#include <securec.h>

#include "lnn_bus_center_ipc.cpp"
#include "bus_center_ipc_mock.h"
#include "softbus_bus_center.h"
#include "softbus_log.h"
#include "softbus_common.h"
#include "softbus_errcode.h"

namespace OHOS {
using namespace testing::ext;
using namespace testing;

#define TEST_PKGNAME       "testname"
#define TEST_PKGNAME2      "testname2"
#define TEST_ADDR          "1111222233334444"
#define TEST_NETWORK_ID    "6542316a57d"
#define TEST_NETWORK_ID2   "6542316a544"
#define TEST_ADDR_TYPE_LEN 17
#define TEST_RET_CODE      0
#define TEST_TYPE          1

class BusCenterClientProxyTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void BusCenterClientProxyTest::SetUpTestCase() { }

void BusCenterClientProxyTest::TearDownTestCase()
{
    g_joinLNNRequestInfo.clear();
    g_joinMetaNodeRequestInfo.clear();
    g_leaveLNNRequestInfo.clear();
    g_leaveMetaNodeRequestInfo.clear();
}

void BusCenterClientProxyTest::SetUp() { }

void BusCenterClientProxyTest::TearDown() { }

/*
 * @tc.name: LnnIpcServerJoin
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, LnnIpcServerJoinTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    ConnectionAddr addr;
    EXPECT_CALL(busCenterIpcMock, LnnIsSameConnectionAddr)
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(busCenterIpcMock, LnnServerJoin).WillRepeatedly(Return(SOFTBUS_OK));
    (void)memset_s(&addr, sizeof(ConnectionAddr), 0, sizeof(ConnectionAddr));
    AddJoinLNNInfo(TEST_PKGNAME, &addr);
    int32_t ret = LnnIpcServerJoin(nullptr, &addr, TEST_ADDR_TYPE_LEN);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = LnnIpcServerJoin(TEST_PKGNAME, nullptr, TEST_ADDR_TYPE_LEN);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = LnnIpcServerJoin(TEST_PKGNAME, &addr, sizeof(ConnectionAddr));
    EXPECT_TRUE(ret == SOFTBUS_OK);
    ret = LnnIpcServerJoin(TEST_PKGNAME, &addr, sizeof(ConnectionAddr));
    EXPECT_TRUE(ret == SOFTBUS_ALREADY_EXISTED);
}

/*
 * @tc.name: MetaNodeIpcServerJoin
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, MetaNodeIpcServerJoinTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    EXPECT_CALL(busCenterIpcMock, LnnIsSameConnectionAddr)
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    ON_CALL(busCenterIpcMock, MetaNodeServerJoin).WillByDefault(Return(SOFTBUS_OK));
    CustomData customData;
    ConnectionAddr addr;
    (void)memset_s(&addr, sizeof(ConnectionAddr), 0, sizeof(ConnectionAddr));
    (void)memset_s(&customData, sizeof(CustomData), 0, sizeof(CustomData));
    AddJoinLNNInfo(TEST_PKGNAME, &addr);
    AddJoinMetaNodeInfo(TEST_PKGNAME, &addr);
    int32_t ret = MetaNodeIpcServerJoin(nullptr, &addr, &customData, TEST_ADDR_TYPE_LEN);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = MetaNodeIpcServerJoin(TEST_PKGNAME, nullptr, &customData, TEST_ADDR_TYPE_LEN);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = MetaNodeIpcServerJoin(TEST_PKGNAME, &addr, &customData, TEST_ADDR_TYPE_LEN);
    EXPECT_TRUE(ret == SOFTBUS_ALREADY_EXISTED);
    ret = MetaNodeIpcServerJoin(TEST_PKGNAME, &addr, &customData, TEST_ADDR_TYPE_LEN);
    EXPECT_TRUE(ret == SOFTBUS_OK);
}

/*
 * @tc.name: LnnIpcServerLeave
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, LnnIpcServerLeaveTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    ON_CALL(busCenterIpcMock, LnnServerLeave).WillByDefault(Return(SOFTBUS_OK));
    int32_t ret = LnnIpcServerLeave(nullptr, nullptr);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = LnnIpcServerLeave(TEST_PKGNAME, nullptr);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = LnnIpcServerLeave(TEST_PKGNAME, TEST_NETWORK_ID);
    EXPECT_TRUE(ret == SOFTBUS_OK);
    ret = LnnIpcServerLeave(TEST_PKGNAME, TEST_NETWORK_ID);
    EXPECT_TRUE(ret == SOFTBUS_ALREADY_EXISTED);
}

/*
 * @tc.name: MetaNodeIpcServerLeave
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, MetaNodeIpcServerLeaveTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    ON_CALL(busCenterIpcMock, MetaNodeServerLeave).WillByDefault(Return(SOFTBUS_OK));
    int32_t ret = MetaNodeIpcServerLeave(nullptr, nullptr);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = MetaNodeIpcServerLeave(TEST_PKGNAME, nullptr);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = MetaNodeIpcServerLeave(TEST_PKGNAME, TEST_NETWORK_ID);
    EXPECT_TRUE(ret == SOFTBUS_OK);
    ret = MetaNodeIpcServerLeave(TEST_PKGNAME, TEST_NETWORK_ID);
    EXPECT_TRUE(ret == SOFTBUS_ALREADY_EXISTED);
}

/*
 * @tc.name: LnnIpcGetAllOnlineNodeInfo
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, LnnIpcGetAllOnlineNodeInfoTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    ON_CALL(busCenterIpcMock, LnnGetAllOnlineNodeInfo).WillByDefault(Return(SOFTBUS_OK));
    int32_t ret = LnnIpcGetAllOnlineNodeInfo(TEST_PKGNAME, nullptr, TEST_RET_CODE, nullptr);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = LnnIpcGetAllOnlineNodeInfo(TEST_PKGNAME, nullptr, sizeof(NodeBasicInfo), nullptr);
    EXPECT_TRUE(ret == SOFTBUS_OK);
}

/*
 * @tc.name: LnnIpcNotifyJoinResult
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, LnnIpcNotifyJoinResultTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    ConnectionAddr addr;
    (void)memset_s(&addr, sizeof(ConnectionAddr), 0, sizeof(ConnectionAddr));
    AddJoinLNNInfo(TEST_PKGNAME, &addr);
    AddJoinLNNInfo(TEST_PKGNAME2, &addr);
    EXPECT_CALL(busCenterIpcMock, LnnIsSameConnectionAddr)
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    int32_t ret =
        LnnIpcNotifyJoinResult(reinterpret_cast<void *>(&addr), TEST_ADDR_TYPE_LEN, TEST_NETWORK_ID, TEST_RET_CODE);
    EXPECT_TRUE(ret == SOFTBUS_OK);
}

/*
 * @tc.name: MetaNodeIpcNotifyJoinResult
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, MetaNodeIpcNotifyJoinResultTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    ConnectionAddr addr;
    (void)memset_s(&addr, sizeof(ConnectionAddr), 0, sizeof(ConnectionAddr));
    AddJoinMetaNodeInfo(TEST_PKGNAME, &addr);
    AddJoinMetaNodeInfo(TEST_PKGNAME2, &addr);
    EXPECT_CALL(busCenterIpcMock, LnnIsSameConnectionAddr)
        .WillOnce(Return(true))
        .WillRepeatedly(Return(false));
    int32_t ret = MetaNodeIpcNotifyJoinResult(nullptr, TEST_ADDR_TYPE_LEN, TEST_NETWORK_ID, TEST_RET_CODE);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);

    ret =
        MetaNodeIpcNotifyJoinResult(reinterpret_cast<void *>(&addr), TEST_ADDR_TYPE_LEN, TEST_NETWORK_ID, TEST_RET_CODE);
    EXPECT_TRUE(ret == SOFTBUS_OK);
}

/*
 * @tc.name: LnnIpcNotifyLeaveResult
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, LnnIpcNotifyLeaveResultTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    AddLeaveLNNInfo(TEST_PKGNAME, TEST_NETWORK_ID);
    AddLeaveLNNInfo(TEST_PKGNAME2, TEST_NETWORK_ID);
    int32_t ret = LnnIpcNotifyLeaveResult(nullptr, TEST_RET_CODE);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = LnnIpcNotifyLeaveResult(TEST_NETWORK_ID, TEST_RET_CODE);
    EXPECT_TRUE(ret == SOFTBUS_OK);
}

/*
 * @tc.name: MetaNodeIpcNotifyLeaveResult
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, MetaNodeIpcNotifyLeaveResultTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    AddLeaveLNNInfo(TEST_PKGNAME, TEST_NETWORK_ID);
    AddLeaveLNNInfo(TEST_PKGNAME2, TEST_NETWORK_ID);
    int32_t ret = MetaNodeIpcNotifyLeaveResult(nullptr, TEST_RET_CODE);
    EXPECT_TRUE(ret == SOFTBUS_INVALID_PARAM);
    ret = MetaNodeIpcNotifyLeaveResult(TEST_NETWORK_ID, TEST_RET_CODE);
    EXPECT_TRUE(ret == SOFTBUS_OK);
    ret = MetaNodeIpcNotifyLeaveResult(TEST_NETWORK_ID2, TEST_RET_CODE);
    EXPECT_TRUE(ret == SOFTBUS_OK);
}

/*
 * @tc.name: RemoveJoinRequestInfoByPkgName
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, RemoveJoinRequestInfoByPkgNameTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    ConnectionAddr addr;
    (void)memset_s(&addr, sizeof(ConnectionAddr), 0, sizeof(ConnectionAddr));
    AddJoinLNNInfo(TEST_PKGNAME, &addr);
    AddJoinLNNInfo(TEST_PKGNAME2, &addr);
    RemoveJoinRequestInfoByPkgName(TEST_PKGNAME);
    RemoveJoinRequestInfoByPkgName(TEST_PKGNAME2);
}

/*
 * @tc.name: RemoveLeaveRequestInfoByPkgName
 * @tc.desc: buscenter ipc test
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(BusCenterClientProxyTest, RemoveLeaveRequestInfoByPkgNameTest_01, TestSize.Level1)
{
    NiceMock<BusCenterIpcInterfaceMock> busCenterIpcMock;
    ConnectionAddr addr;
    (void)memset_s(&addr, sizeof(ConnectionAddr), 0, sizeof(ConnectionAddr));
    AddLeaveLNNInfo(TEST_PKGNAME, TEST_NETWORK_ID);
    AddLeaveLNNInfo(TEST_PKGNAME2, TEST_NETWORK_ID);
    RemoveLeaveRequestInfoByPkgName(TEST_PKGNAME);
    BusCenterServerDeathCallback(nullptr);
    BusCenterServerDeathCallback(TEST_PKGNAME);
}

} // namespace OHOS