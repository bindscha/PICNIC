#include "pchannel_p.h"
#include "pcommunity.h"

//
// ChannelHelper
//

PICNICH::ChannelHelper::ChannelHelper(QObject *_parent) :
	channelPrivate_(_parent)
{
	connect(&channelPrivate_, SIGNAL(channelReady()), this, SLOT(onChannelReady()));
	connect(&channelPrivate_, SIGNAL(channelError(int)), this, SLOT(onChannelError(int)));
	connect(&channelPrivate_, SIGNAL(messageReceived(const ReceivedMessage &)), this, SLOT(onMessageReceived(const ReceivedMessage &)));
}

PICNIC::Error PICNICH::ChannelHelper::bind(PICNIC::ChannelId _channelId)
{
	return (PICNIC::Error) channelPrivate_.bind(_channelId);
}

PICNIC::Error PICNICH::ChannelHelper::send(const AwareNet::UnicastMessage &_message)
{
	return (PICNIC::Error) channelPrivate_.sendMessage(_message);
}

PICNIC::Error PICNICH::ChannelHelper::send(const AwareNet::BroadcastMessage &_message)
{
	return (PICNIC::Error) channelPrivate_.sendMessage(_message);
}

void PICNICH::ChannelHelper::onChannelReady()
{
	emit channelReady();
}

void PICNICH::ChannelHelper::onChannelError(int _error)
{
	emit channelError((PICNIC::Error) _error);
}

void PICNICH::ChannelHelper::onMessageReceived(const PICNICH::ReceivedMessage &_message)
{
	emit messageReceived(_message);
}

//
// ChannelPrivate
//

PICNIC::ChannelPrivate::ChannelPrivate(QObject *_parent) :
	channelHelper_(_parent)
{
	connect(&channelHelper_, SIGNAL(channelReady()), this, SLOT(onChannelReady()));
	connect(&channelHelper_, SIGNAL(channelError(PICNIC::Error)), this, SLOT(onChannelError(PICNIC::Error)));
	connect(&channelHelper_, SIGNAL(messageReceived(const PICNICH::ReceivedMessage &)), this, SLOT(onMessageReceived(const PICNICH::ReceivedMessage &)));
}

PICNIC::Error PICNIC::ChannelPrivate::bind(PICNIC::ChannelId _channelId)
{
	return channelHelper_.bind(_channelId);
}

PICNIC::Error PICNIC::ChannelPrivate::send(const PICNIC::UnicastMessage &_message)
{
	AwareNet::UnicastMessage messageToSend(_message.marshalledPayload());
	messageToSend.setCommunity(const_cast<PICNIC::CommunityPrivate *> (_message.community().communityPrivate()));
	messageToSend.setReceiver(_message.receiver());
	messageToSend.setSensitivity(toAwn(_message.payloadSensitivity()));
	return channelHelper_.send(messageToSend);
}

PICNIC::Error PICNIC::ChannelPrivate::send(const PICNIC::BroadcastMessage &_message)
{
	AwareNet::BroadcastMessage messageToSend(_message.marshalledPayload());
	messageToSend.setCommunity(const_cast<PICNIC::CommunityPrivate *> (_message.community().communityPrivate()));
	messageToSend.setSensitivity(toAwn(_message.payloadSensitivity()));
	messageToSend.setMaxHopCount(_message.maxHopCount());
	messageToSend.setMaxRange(_message.maxRange());
	messageToSend.setMaxReceivers(_message.maxReceivers());
	return channelHelper_.send(messageToSend);
}

void PICNIC::ChannelPrivate::onChannelReady()
{
	emit channelReady();
}

void PICNIC::ChannelPrivate::onChannelError(PICNIC::Error _error)
{
	emit channelError(_error);
}

void PICNIC::ChannelPrivate::onMessageReceived(const PICNICH::ReceivedMessage &_message)
{
	QByteArray payload = _message.getPayload();
	PICNIC::Community community = PICNIC::Community(const_cast<PICNIC::CommunityPrivate *const> (_message.getCommunity()));
	DeviceAddress sender = _message.getSender();
	HopCount hopCount = _message.getHopCount();
	const PICNIC::ReceivedMessage receivedMessage(payload, community, sender, hopCount);
	emit messageReceived(receivedMessage);
}
