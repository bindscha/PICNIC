#ifndef PICNIC_MESSAGE_P_H
#define PICNIC_MESSAGE_P_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include <QMetaType>
#include <QString>
#include <QByteArray>
#include "picnicdefs.h"
#include "pmessage.h"
#include "message.h"

#include "deviceaddress.h"

namespace PICNIC
{
    // Forward declarations
    class Community;
	class Network;
	class Channel;

    class MessagePrivate
    {
    public:
        MessagePrivate(const QByteArray &_content, const Community &_community);
		MessagePrivate(const QString &_content, const Community &_community);
		virtual ~MessagePrivate() {};
		
    public:
        const QByteArray &payload() const;
        const Community &community() const;

	protected:
        const QByteArray payload_;
        const Community &community_;
		
    };
	
    class UnicastMessagePrivate : public MessagePrivate
    {
    public:
        UnicastMessagePrivate(const QByteArray &_content, const Community &_community, const DeviceAddress &_receiver, const PayloadSensitivity _payloadSensitivity = PublicData);
		UnicastMessagePrivate(const QString &_content, const Community &_community, const DeviceAddress &_receiver, const PayloadSensitivity _payloadSensitivity = PublicData);
		UnicastMessagePrivate(const UnicastMessage &_unicastMessage);
	
        const DeviceAddress receiver() const;
        const PayloadSensitivity payloadSensitivity() const;

	protected:
        const DeviceAddress receiver_;
        const PayloadSensitivity payloadSensitivity_;
		
    };

    class BroadcastMessagePrivate : public MessagePrivate
    {
    public:
        BroadcastMessagePrivate(const QByteArray &_content, const Community &_community, const PayloadSensitivity _payloadSensitivity = PublicData, const HopCount _maxHopCount = DefaultMaxHopCount, const Range _maxRange = DefaultMaxRange, const ReceiverCount _maxReceivers = DefaultMaxReceivers);
		BroadcastMessagePrivate(const QString &_content, const Community &_community, const PayloadSensitivity _payloadSensitivity = PublicData, const HopCount _maxHopCount = DefaultMaxHopCount, const Range _maxRange = DefaultMaxRange, const ReceiverCount _maxReceivers = DefaultMaxReceivers);
		BroadcastMessagePrivate(const BroadcastMessage &_broadcastMessage);
		
        const PayloadSensitivity payloadSensitivity() const;
        const HopCount maxHopCount() const;
        const Range maxRange() const;
        const ReceiverCount maxReceivers() const;
		
    protected:
        const PayloadSensitivity payloadSensitivity_;
        const HopCount maxHopCount_;
        const Range maxRange_;
        const ReceiverCount maxReceivers_;

    };

    class ReceivedMessagePrivate : public MessagePrivate
    {
    public:
		ReceivedMessagePrivate(const QByteArray &_content, const Community &_community, const DeviceAddress &_sender, const HopCount _hopCount = DefaultHopCount);
		ReceivedMessagePrivate(const QString &_content, const Community &_community, const DeviceAddress &_sender, const HopCount _hopCount = DefaultHopCount);
        ReceivedMessagePrivate(const ReceivedMessage &_receivedMessage);
		
	public:
        const HopCount hopCount() const;
        const DeviceAddress sender() const;
	
	protected:
        const DeviceAddress sender_;
        const quint8 hopCount_;
		
    };

} // namespace PICNIC

#endif // PICNIC_MESSAGE_P_H
