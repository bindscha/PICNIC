#ifndef PICNIC_MESSAGE_H
#define PICNIC_MESSAGE_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include <QMetaType>
#include <QString>
#include <QByteArray>
#include "pconversions.h"
#include "picnicdefs.h"
#include "deviceaddress.h"

namespace PICNIC
{
    // Forward declarations
    class Community;
	class Network;
	
	class ChannelPrivate;
	
	class MessagePrivate;
	class UnicastMessagePrivate;
	class BroadcastMessagePrivate;
	class ReceivedMessagePrivate;

	typedef quint8 HopCount;
	typedef quint16 Range;
	typedef quint16 ReceiverCount;
	
	const HopCount DefaultMaxHopCount = 10;
	const Range DefaultMaxRange = 1000;
	const ReceiverCount DefaultMaxReceivers = 100;
	const HopCount DefaultHopCount = 0;

    class Message
    {
    protected:
		Message(MessagePrivate *const _messagePrivate);
		virtual ~Message();
		
    public:
        const QByteArray &payload() const;
        const Community &community() const;

    protected:
        MessagePrivate *const d_ptr;
		
	private:
		Q_DECLARE_PRIVATE(Message);
		
    };
	
    class UnicastMessage : public Message
    {
    public:
        UnicastMessage(const QString& _content, const Community &_community, const DeviceAddress &_receiver, const PayloadSensitivity _payloadSensitivity = PublicData);
        UnicastMessage(const QByteArray& _content, const Community &_community, const DeviceAddress &_receiver, const PayloadSensitivity _payloadSensitivity = PublicData);
		UnicastMessage(const UnicastMessage &_unicastMessage);

	protected:
		UnicastMessage(UnicastMessagePrivate *const _unicastMessagePrivate);
		
	public:
        const DeviceAddress receiver() const;
        const PayloadSensitivity payloadSensitivity() const;

	protected:
		virtual const QByteArray marshalledPayload() const;
		
	private:
		Q_DECLARE_PRIVATE(UnicastMessage);
		
	protected:
		friend class ChannelPrivate;
		friend class Network;
    };

    class BroadcastMessage : public Message
    {
    public:
		BroadcastMessage(const QString& _content, const Community &_community, const PayloadSensitivity _payloadSensitivity = PublicData, const HopCount _maxHopCount = DefaultMaxHopCount, const Range _maxRange = DefaultMaxRange, const ReceiverCount _maxReceivers = DefaultMaxReceivers);
        BroadcastMessage(const QByteArray& _content, const Community &_community, const PayloadSensitivity _payloadSensitivity = PublicData, const HopCount _maxHopCount = DefaultMaxHopCount, const Range _maxRange = DefaultMaxRange, const ReceiverCount _maxReceivers = DefaultMaxReceivers);
		BroadcastMessage(const BroadcastMessage &_broadcastMessage);
		
	protected:
		BroadcastMessage(BroadcastMessagePrivate *const _broadcastMessagePrivate);
		
	public:
        const PayloadSensitivity payloadSensitivity() const;
        const HopCount maxHopCount() const;
        const Range maxRange() const;
        const ReceiverCount maxReceivers() const;

	protected:
		virtual const QByteArray marshalledPayload() const;
		
	private:
		Q_DECLARE_PRIVATE(BroadcastMessage);
		
	protected:
		friend class ChannelPrivate;
		friend class Network;
    };

    class ReceivedMessage : public Message
    {
    protected:
		ReceivedMessage(const QByteArray &_content, const Community &_community, const DeviceAddress &_sender, const HopCount _hopCount = DefaultHopCount);
		ReceivedMessage(const QString &_content, const Community &_community, const DeviceAddress &_sender, const HopCount _hopCount = DefaultHopCount);
		ReceivedMessage(const ReceivedMessage &_receivedMessage);
		
	protected:
		ReceivedMessage(ReceivedMessagePrivate *const _receivedMessagePrivate);
		
	public:
        const HopCount hopCount() const;
        const DeviceAddress sender() const;

	private:
		Q_DECLARE_PRIVATE(ReceivedMessage);
		
	protected:
        friend class ChannelPrivate;
		
    };

} // namespace PICNIC

#endif // PICNIC_MESSAGE_H
