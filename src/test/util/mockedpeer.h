// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "test-util-export.h"

#include <boost/variant.hpp>

#include "internalpeer.h"
#include "testglobal.h"

namespace test {

/// Variant-based wrapper struct for supported protocol messages
struct ProtocolMessage;

TEST_UTIL_EXPORT void PrintTo(const ProtocolMessage&, std::ostream*);

/**
 * Mocked peer that can be used in test cases involving SignalProxy.
 *
 * This mock class is intended to be used for testing on the abstraction level of Quassel protocol messages; it does not support
 * mocking e.g. serialization or network connections, or other lower-level implementation details of specific peer types.
 *
 * To set expectations, use EXPECT_CALL on the mocked Dispatches() method and the provided protocol message matchers like this:
 *
 * @code
 * EXPECT_CALL(*peer, Dispatches(RpcCall(QByteArray{SIGNAL(sendData(int,QString))}, ElementsAre(42, "Hello"))));
 * @endcode
 *
 * The matchers take matchers themselves for their individual arguments, so you can do things like
 *
 * @code
 * EXPECT_CALL(*peer, Dispatches(RpcCall(_, Contains(42))));
 * @endcode
 *
 * @note For now, MockedPeer only supports SignalProxy message types. It can be extended in the future to support auth messages,
 *       as well.
 */
class TEST_UTIL_EXPORT MockedPeer : public InternalPeer
{
    Q_OBJECT

public:
    MockedPeer(QObject* parent = nullptr);
    ~MockedPeer() override;

    /// Every message dispatched goes through this mocked method, which can be used with the protocol message machters to define expectations
    MOCK_METHOD1(Dispatches, void(const ProtocolMessage&));

    using InternalPeer::dispatch;
    void dispatch(const QuasselProtocol::SyncMessage&) override;
    void dispatch(const QuasselProtocol::RpcCall&) override;
    void dispatch(const QuasselProtocol::InitRequest&) override;
    void dispatch(const QuasselProtocol::InitData&) override;

private:
    void dispatchInternal(const ProtocolMessage&);

    template<typename T>
    void realDispatch(const T&);

    friend struct DispatchVisitor;
};

// ---- Matchers for defining protocol message expectations for Dispatches() ---------------------------------------------------------------

TEST_UTIL_EXPORT ::testing::Matcher<const ProtocolMessage&> SyncMessage(::testing::Matcher<QByteArray> className,
                                                                        ::testing::Matcher<QString> objectName,
                                                                        ::testing::Matcher<QByteArray> slotName,
                                                                        ::testing::Matcher<QVariantList> params);

TEST_UTIL_EXPORT ::testing::Matcher<const ProtocolMessage&> RpcCall(::testing::Matcher<QByteArray> signalName,
                                                                    ::testing::Matcher<QVariantList> params);

TEST_UTIL_EXPORT ::testing::Matcher<const ProtocolMessage&> InitRequest(::testing::Matcher<QByteArray> className,
                                                                        ::testing::Matcher<QString> objectName);

TEST_UTIL_EXPORT ::testing::Matcher<const ProtocolMessage&> InitData(::testing::Matcher<QByteArray> className,
                                                                     ::testing::Matcher<QString> objectName,
                                                                     ::testing::Matcher<QVariantMap> initData);

}  // namespace test
