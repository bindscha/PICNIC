#ifndef PICNIC_ENCMESSAGE_H
#define PICNIC_ENCMESSAGE_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Alexandre Duc <alexandre.duc@epfl.ch>


#include <QObject>
#include <QMetaType>
#include <QString>
#include <QByteArray>
#include <gcrypt.h>
#include "pmessage.h"

namespace PICNIC
{
	//Forward declarations
	class EncryptedUnicastMessagePrivate;
	class EncryptedBroadcastMessagePrivate;
	class DecryptedReceivedMessagePrivate;
	
    class EncryptedUnicastMessage : public UnicastMessage
    {
    public:
        EncryptedUnicastMessage(const QString& _content, const Community &_community, const DeviceAddress &_receiver, const PayloadSensitivity _payloadSensitivity = PublicData);
        EncryptedUnicastMessage(const QByteArray& _content, const Community &_community, const DeviceAddress &_receiver, const PayloadSensitivity _payloadSensitivity = PublicData);
		EncryptedUnicastMessage(const EncryptedUnicastMessage &_unicastMessage);

	public:
		const QByteArray marshalledPayload() const;

	private:
		Q_DECLARE_PRIVATE(EncryptedUnicastMessage);

    };

class EncryptedBroadcastMessage : public BroadcastMessage
    {
    public:
		EncryptedBroadcastMessage(const QString& _content, const Community &_community, const PayloadSensitivity _payloadSensitivity = PublicData, const HopCount _maxHopCount = DefaultMaxHopCount, const Range _maxRange = DefaultMaxRange, const ReceiverCount _maxReceivers = DefaultMaxReceivers);
        	EncryptedBroadcastMessage(const QByteArray& _content, const Community &_community, const PayloadSensitivity _payloadSensitivity = PublicData, const HopCount _maxHopCount = DefaultMaxHopCount, const Range _maxRange = DefaultMaxRange, const ReceiverCount _maxReceivers = DefaultMaxReceivers);
		EncryptedBroadcastMessage(const EncryptedBroadcastMessage &_broadcastMessage);
		~EncryptedBroadcastMessage();
		
	public:
        	const QByteArray marshalledPayload() const;

	private:
		Q_DECLARE_PRIVATE(EncryptedBroadcastMessage);

    };

    class DecryptedReceivedMessage : public ReceivedMessage
    {
    protected:
		DecryptedReceivedMessage(const QByteArray &_content, const Community &_community, const DeviceAddress &_sender, const HopCount _hopCount = DefaultHopCount);
		DecryptedReceivedMessage(const QString &_content, const Community &_community, const DeviceAddress &_sender, const HopCount _hopCount = DefaultHopCount);
		DecryptedReceivedMessage(const DecryptedReceivedMessage &_receivedMessage);
		
	public:
        	const QByteArray marshalledPayload() const;

	private:
		Q_DECLARE_PRIVATE(DecryptedReceivedMessage);

	protected:
        	friend class ChannelPrivate;

		
    };

} // namespace PICNIC

#endif // PICNIC_ENCMESSAGE_H
