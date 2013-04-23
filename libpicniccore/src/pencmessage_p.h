#ifndef PICNIC_ENCMESSAGE_P_H
#define PICNIC_ENCMESSAGE_P_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Alexandre Duc <alexandre.duc@epfl.ch>


#include <QObject>
#include <QMetaType>
#include <QString>
#include <QByteArray>
#include "pencmessage.h"
#include "pmessage_p.h"
#include "pencrypt.h"

namespace PICNIC
{
    class EncryptedUnicastMessagePrivate : public UnicastMessagePrivate
    {
    public:
        EncryptedUnicastMessagePrivate(const QByteArray& _content, const Community &_community, const DeviceAddress &_receiver, const PayloadSensitivity _payloadSensitivity = PrivateData);
	EncryptedUnicastMessagePrivate(const EncryptedUnicastMessage &_unicastMessage);

	const QByteArray marshalledPayload() const;

    protected:
        const QByteArray  marshalledPayload_; 
    private:
	static const QByteArray initPayload(const QByteArray& _content);		
	static const QByteArray key();
	static const QByteArray nonce();
    };

    class EncryptedBroadcastMessagePrivate : public BroadcastMessagePrivate
    {
    public:
        EncryptedBroadcastMessagePrivate(const QByteArray& _content, const Community &_community, const PayloadSensitivity _payloadSensitivity = PublicData, const HopCount _maxHopCount = DefaultMaxHopCount, const Range _maxRange = DefaultMaxRange, const ReceiverCount _maxReceivers = DefaultMaxReceivers);
	EncryptedBroadcastMessagePrivate(const EncryptedBroadcastMessage &_broadcastMessage);
	const QByteArray marshalledPayload() const;

    protected:
        const QByteArray marshalledPayload_;

    private:
	static const QByteArray initPayload(const QByteArray& _content);
	static const QByteArray key();
	static const QByteArray nonce();
    };



    class DecryptedReceivedMessagePrivate : public ReceivedMessagePrivate
    {
    public:
	DecryptedReceivedMessagePrivate(const QByteArray &_content, const Community &_community, const DeviceAddress &_sender, const HopCount _hopCount = DefaultHopCount);
        DecryptedReceivedMessagePrivate(const DecryptedReceivedMessage &_receivedMessage);
	const QByteArray marshalledPayload() const;
    protected:
        const QByteArray marshalledPayload_;
    private:
	static const QByteArray initPayload(const QByteArray& _content);
	static const QByteArray key();
	static const QByteArray nonce();

    };

} // namespace PICNIC

#endif // PICNIC_ENCMESSAGE_P_H
