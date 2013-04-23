#include "pencmessage.h"
#include "pencmessage_p.h"


//
// EncryptedUnicastMessage
//

PICNIC::EncryptedUnicastMessage::EncryptedUnicastMessage(const QByteArray& _content, const PICNIC::Community &_community, const DeviceAddress &_receiver, const PICNIC::PayloadSensitivity _payloadSensitivity) :
	PICNIC::UnicastMessage(new PICNIC::EncryptedUnicastMessagePrivate::EncryptedUnicastMessagePrivate(_content, _community, _receiver, _payloadSensitivity))
{
}

PICNIC::EncryptedUnicastMessage::EncryptedUnicastMessage(const QString& _content, const PICNIC::Community &_community, const DeviceAddress &_receiver, const PICNIC::PayloadSensitivity _payloadSensitivity) :
	PICNIC::UnicastMessage(new PICNIC::EncryptedUnicastMessagePrivate::EncryptedUnicastMessagePrivate(_content.toUtf8(), _community, _receiver, _payloadSensitivity))
{
}

PICNIC::EncryptedUnicastMessage::EncryptedUnicastMessage(const PICNIC::EncryptedUnicastMessage &_unicastMessage) :
	PICNIC::UnicastMessage(new PICNIC::EncryptedUnicastMessagePrivate::EncryptedUnicastMessagePrivate(_unicastMessage)) 
{
}

const QByteArray PICNIC::EncryptedUnicastMessage::marshalledPayload() const
{
	return (dynamic_cast<PICNIC::EncryptedUnicastMessagePrivate *const> (d_ptr))->marshalledPayload();
}


//
// EncryptedBroadcastMessage
//

PICNIC::EncryptedBroadcastMessage::EncryptedBroadcastMessage(const QByteArray& _content, const PICNIC::Community &_community, const PICNIC::PayloadSensitivity _payloadSensitivity, const PICNIC::HopCount _maxHopCount, const PICNIC::Range _maxRange, const PICNIC::ReceiverCount _maxReceivers) :
	PICNIC::BroadcastMessage(new PICNIC::EncryptedBroadcastMessagePrivate::EncryptedBroadcastMessagePrivate(_content, _community, _payloadSensitivity, _maxHopCount, _maxRange, _maxReceivers))
{
}

PICNIC::EncryptedBroadcastMessage::EncryptedBroadcastMessage(const QString& _content, const PICNIC::Community &_community, const PICNIC::PayloadSensitivity _payloadSensitivity, const PICNIC::HopCount _maxHopCount, const PICNIC::Range _maxRange, const PICNIC::ReceiverCount _maxReceivers) :
	PICNIC::BroadcastMessage(new PICNIC::EncryptedBroadcastMessagePrivate::EncryptedBroadcastMessagePrivate(_content.toUtf8(), _community, _payloadSensitivity, _maxHopCount, _maxRange, _maxReceivers))
{
}

PICNIC::EncryptedBroadcastMessage::EncryptedBroadcastMessage(const PICNIC::EncryptedBroadcastMessage &_broadcastMessage) :
	PICNIC::BroadcastMessage(new PICNIC::EncryptedBroadcastMessagePrivate::EncryptedBroadcastMessagePrivate(_broadcastMessage))
{
}

PICNIC::EncryptedBroadcastMessage::~EncryptedBroadcastMessage()
{
	//delete (dynamic_cast<PICNIC::EncryptedBroadcastMessagePrivate *const>(d_ptr));
	//delete d_ptr;
}

const QByteArray PICNIC::EncryptedBroadcastMessage::marshalledPayload() const
{
	return (dynamic_cast<PICNIC::EncryptedBroadcastMessagePrivate *const> (d_ptr))->marshalledPayload();
}

//
// DecryptedReceivedMessage
//

PICNIC::DecryptedReceivedMessage::DecryptedReceivedMessage(const QByteArray &_content, const PICNIC::Community &_community, const DeviceAddress &_sender, const PICNIC::HopCount _hopCount) : 
	PICNIC::ReceivedMessage(new PICNIC::DecryptedReceivedMessagePrivate::DecryptedReceivedMessagePrivate(_content, _community, _sender, _hopCount))
{
}

PICNIC::DecryptedReceivedMessage::DecryptedReceivedMessage(const QString &_content, const PICNIC::Community &_community, const DeviceAddress &_sender, const PICNIC::HopCount _hopCount) : 
	PICNIC::ReceivedMessage(new PICNIC::DecryptedReceivedMessagePrivate::DecryptedReceivedMessagePrivate(_content.toUtf8(), _community, _sender, _hopCount))
{
}

PICNIC::DecryptedReceivedMessage::DecryptedReceivedMessage(const PICNIC::DecryptedReceivedMessage &_receivedMessage) :
	PICNIC::ReceivedMessage(new PICNIC::DecryptedReceivedMessagePrivate::DecryptedReceivedMessagePrivate(_receivedMessage))
{
}
const QByteArray PICNIC::DecryptedReceivedMessage::marshalledPayload() const
{
	return (dynamic_cast<PICNIC::DecryptedReceivedMessagePrivate *const> (d_ptr))->marshalledPayload();
}
