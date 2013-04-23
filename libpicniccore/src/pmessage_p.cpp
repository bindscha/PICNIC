#include "pmessage_p.h"
#include "message.h"
#include "pcommunity.h"
#include "picnicdefs.h"

//
// MessagePrivate
//

PICNIC::MessagePrivate::MessagePrivate(const QByteArray &_content, const PICNIC::Community &_community) : 
	payload_(QByteArray(_content)), community_(_community)
{
}

PICNIC::MessagePrivate::MessagePrivate(const QString &_content, const PICNIC::Community &_community) : 
	payload_(_content.toUtf8()), community_(_community)
{
}

const QByteArray &PICNIC::MessagePrivate::payload() const
{
	return payload_;
}

const PICNIC::Community &PICNIC::MessagePrivate::community() const 
{
	return community_;
}

//
// UnicastMessagePrivate
//

PICNIC::UnicastMessagePrivate::UnicastMessagePrivate(const QByteArray& _content, const PICNIC::Community &_community, const DeviceAddress &_receiver, const PICNIC::PayloadSensitivity _payloadSensitivity) :
	PICNIC::MessagePrivate::MessagePrivate(_content, _community), receiver_(_receiver), payloadSensitivity_(_payloadSensitivity)
{
}

PICNIC::UnicastMessagePrivate::UnicastMessagePrivate(const QString& _content, const PICNIC::Community &_community, const DeviceAddress &_receiver, const PICNIC::PayloadSensitivity _payloadSensitivity) :
	PICNIC::MessagePrivate::MessagePrivate(_content, _community), receiver_(_receiver), payloadSensitivity_(_payloadSensitivity)
{
}

PICNIC::UnicastMessagePrivate::UnicastMessagePrivate(const UnicastMessage &_unicastMessage) :
	PICNIC::MessagePrivate::MessagePrivate(_unicastMessage.payload(), _unicastMessage.community()), receiver_(_unicastMessage.receiver()), payloadSensitivity_(_unicastMessage.payloadSensitivity())
{
}

const DeviceAddress PICNIC::UnicastMessagePrivate::receiver() const
{
	return receiver_;
}

const PICNIC::PayloadSensitivity PICNIC::UnicastMessagePrivate::payloadSensitivity() const
{
	return payloadSensitivity_;
}

//
// BroadcastMessagePrivate
//

PICNIC::BroadcastMessagePrivate::BroadcastMessagePrivate(const QByteArray& _content, const PICNIC::Community &_community, const PICNIC::PayloadSensitivity _payloadSensitivity, const PICNIC::HopCount _maxHopCount, const PICNIC::Range _maxRange, const PICNIC::ReceiverCount _maxReceivers) :
	PICNIC::MessagePrivate::MessagePrivate(_content, _community), payloadSensitivity_(_payloadSensitivity), maxHopCount_(_maxHopCount), maxRange_(_maxRange), maxReceivers_(_maxReceivers)
{
}

PICNIC::BroadcastMessagePrivate::BroadcastMessagePrivate(const QString& _content, const PICNIC::Community &_community, const PICNIC::PayloadSensitivity _payloadSensitivity, const PICNIC::HopCount _maxHopCount, const PICNIC::Range _maxRange, const PICNIC::ReceiverCount _maxReceivers) :
	PICNIC::MessagePrivate::MessagePrivate(_content, _community), payloadSensitivity_(_payloadSensitivity), maxHopCount_(_maxHopCount), maxRange_(_maxRange), maxReceivers_(_maxReceivers)
{
}

PICNIC::BroadcastMessagePrivate::BroadcastMessagePrivate(const BroadcastMessage &_broadcastMessage) :
	PICNIC::MessagePrivate::MessagePrivate(_broadcastMessage.payload(), _broadcastMessage.community()), payloadSensitivity_(_broadcastMessage.payloadSensitivity()), maxHopCount_(_broadcastMessage.maxHopCount()), maxRange_(_broadcastMessage.maxRange()), maxReceivers_(_broadcastMessage.maxReceivers())
{
}

const PICNIC::PayloadSensitivity PICNIC::BroadcastMessagePrivate::payloadSensitivity() const
{
	return payloadSensitivity_;
}

const PICNIC::HopCount PICNIC::BroadcastMessagePrivate::maxHopCount() const
{
	return maxHopCount_;
}

const PICNIC::Range PICNIC::BroadcastMessagePrivate::maxRange() const
{
	return maxRange_;
}

const PICNIC::ReceiverCount PICNIC::BroadcastMessagePrivate::maxReceivers() const
{
	return maxReceivers_;
}

//
// ReceivedMessagePrivate
//

PICNIC::ReceivedMessagePrivate::ReceivedMessagePrivate(const QByteArray &_content, const PICNIC::Community &_community, const DeviceAddress &_sender, const PICNIC::HopCount _hopCount) : 
	PICNIC::MessagePrivate::MessagePrivate(_content, _community), sender_(_sender), hopCount_(_hopCount)
{
}

PICNIC::ReceivedMessagePrivate::ReceivedMessagePrivate(const QString &_content, const PICNIC::Community &_community, const DeviceAddress &_sender, const PICNIC::HopCount _hopCount) : 
	PICNIC::MessagePrivate::MessagePrivate(_content, _community), sender_(_sender), hopCount_(_hopCount)
{
}

PICNIC::ReceivedMessagePrivate::ReceivedMessagePrivate(const ReceivedMessage &_receivedMessage) : 
	PICNIC::MessagePrivate::MessagePrivate(_receivedMessage.payload(), _receivedMessage.community()), sender_(_receivedMessage.sender()), hopCount_(_receivedMessage.hopCount())
{
}

const PICNIC::HopCount PICNIC::ReceivedMessagePrivate::hopCount() const
{
	return hopCount_;
}

const DeviceAddress PICNIC::ReceivedMessagePrivate::sender() const
{
	return sender_;
}
