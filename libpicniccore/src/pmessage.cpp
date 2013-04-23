#include "pmessage.h"
#include "pmessage_p.h"
#include "pcommunity.h"
#include "pchannel_p.h"
#include "deviceaddress.h"
#include "message.h"

//
// Message
//

PICNIC::Message::Message(PICNIC::MessagePrivate *const _messagePrivate) : 
	d_ptr(_messagePrivate)
{
}

PICNIC::Message::~Message()
{
	if(d_ptr != NULL)
	{
		delete d_ptr;
	}
}

const QByteArray &PICNIC::Message::payload() const
{
	return d_ptr->payload();
}

const PICNIC::Community &PICNIC::Message::community() const 
{
	return d_ptr->community();
}

//
// UnicastMessage
//

PICNIC::UnicastMessage::UnicastMessage(const QByteArray& _content, const PICNIC::Community &_community, const DeviceAddress &_receiver, const PICNIC::PayloadSensitivity _payloadSensitivity) :
	PICNIC::Message(new PICNIC::UnicastMessagePrivate::UnicastMessagePrivate(_content, _community, _receiver, _payloadSensitivity))
{
}

PICNIC::UnicastMessage::UnicastMessage(const QString& _content, const PICNIC::Community &_community, const DeviceAddress &_receiver, const PICNIC::PayloadSensitivity _payloadSensitivity) :
	PICNIC::Message(new PICNIC::UnicastMessagePrivate::UnicastMessagePrivate(_content, _community, _receiver, _payloadSensitivity))
{
}

PICNIC::UnicastMessage::UnicastMessage(const PICNIC::UnicastMessage &_unicastMessage) :
	PICNIC::Message(new PICNIC::UnicastMessagePrivate::UnicastMessagePrivate(_unicastMessage))
{
}

PICNIC::UnicastMessage::UnicastMessage(UnicastMessagePrivate *const _unicastMessagePrivate) :
	PICNIC::Message(_unicastMessagePrivate)
{
}

const QByteArray PICNIC::UnicastMessage::marshalledPayload() const
{
	return payload();
}

const DeviceAddress PICNIC::UnicastMessage::receiver() const
{
	return (dynamic_cast<PICNIC::UnicastMessagePrivate *const> (d_ptr))->receiver();
}

const PICNIC::PayloadSensitivity PICNIC::UnicastMessage::payloadSensitivity() const
{
	return (dynamic_cast<PICNIC::UnicastMessagePrivate *const> (d_ptr))->payloadSensitivity();
}

//
// BroadcastMessage
//

PICNIC::BroadcastMessage::BroadcastMessage(const QByteArray& _content, const PICNIC::Community &_community, const PICNIC::PayloadSensitivity _payloadSensitivity, const PICNIC::HopCount _maxHopCount, const PICNIC::Range _maxRange, const PICNIC::ReceiverCount _maxReceivers) :
	PICNIC::Message(new PICNIC::BroadcastMessagePrivate::BroadcastMessagePrivate(_content, _community, _payloadSensitivity, _maxHopCount, _maxRange, _maxReceivers))
{
}

PICNIC::BroadcastMessage::BroadcastMessage(const QString& _content, const PICNIC::Community &_community, const PICNIC::PayloadSensitivity _payloadSensitivity, const PICNIC::HopCount _maxHopCount, const PICNIC::Range _maxRange, const PICNIC::ReceiverCount _maxReceivers) :
	PICNIC::Message(new PICNIC::BroadcastMessagePrivate::BroadcastMessagePrivate(_content, _community, _payloadSensitivity, _maxHopCount, _maxRange, _maxReceivers))
{
}

PICNIC::BroadcastMessage::BroadcastMessage(const PICNIC::BroadcastMessage &_broadcastMessage) :
	PICNIC::Message(new PICNIC::BroadcastMessagePrivate::BroadcastMessagePrivate(_broadcastMessage))
{
}

PICNIC::BroadcastMessage::BroadcastMessage(BroadcastMessagePrivate *const _broadcastMessagePrivate) :
	PICNIC::Message(_broadcastMessagePrivate)
{
}

const QByteArray PICNIC::BroadcastMessage::marshalledPayload() const
{
	return payload();
}

const PICNIC::PayloadSensitivity PICNIC::BroadcastMessage::payloadSensitivity() const
{
	return (dynamic_cast<PICNIC::BroadcastMessagePrivate *const> (d_ptr))->payloadSensitivity();
}

const PICNIC::HopCount PICNIC::BroadcastMessage::maxHopCount() const
{
	return (dynamic_cast<PICNIC::BroadcastMessagePrivate *const> (d_ptr))->maxHopCount();
}

const PICNIC::Range PICNIC::BroadcastMessage::maxRange() const
{
	return (dynamic_cast<PICNIC::BroadcastMessagePrivate *const> (d_ptr))->maxRange();
}

const PICNIC::ReceiverCount PICNIC::BroadcastMessage::maxReceivers() const
{
	return (dynamic_cast<PICNIC::BroadcastMessagePrivate *const> (d_ptr))->maxReceivers();
}

//
// ReceivedMessage
//

PICNIC::ReceivedMessage::ReceivedMessage(const QByteArray &_content, const PICNIC::Community &_community, const DeviceAddress &_sender, const PICNIC::HopCount _hopCount) : 
	PICNIC::Message(new PICNIC::ReceivedMessagePrivate::ReceivedMessagePrivate(_content, _community, _sender, _hopCount))
{
}

PICNIC::ReceivedMessage::ReceivedMessage(const QString &_content, const PICNIC::Community &_community, const DeviceAddress &_sender, const PICNIC::HopCount _hopCount) : 
	PICNIC::Message(new PICNIC::ReceivedMessagePrivate::ReceivedMessagePrivate(_content, _community, _sender, _hopCount))
{
}

PICNIC::ReceivedMessage::ReceivedMessage(const PICNIC::ReceivedMessage &_receivedMessage) :
	PICNIC::Message(new PICNIC::ReceivedMessagePrivate::ReceivedMessagePrivate(_receivedMessage))
{
}

PICNIC::ReceivedMessage::ReceivedMessage(ReceivedMessagePrivate *const _receivedMessagePrivate) :
	PICNIC::Message(_receivedMessagePrivate)
{
}

const PICNIC::HopCount PICNIC::ReceivedMessage::hopCount() const
{
	return (dynamic_cast<PICNIC::ReceivedMessagePrivate *const> (d_ptr))->hopCount();
}

const DeviceAddress PICNIC::ReceivedMessage::sender() const
{
	return (dynamic_cast<PICNIC::ReceivedMessagePrivate *const> (d_ptr))->sender();
}
