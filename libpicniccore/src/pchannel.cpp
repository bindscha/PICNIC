#include "pchannel.h"
#include "pchannel_p.h"
#include "pmessage.h"

//
// Channel
//

PICNIC::Channel::Channel(QObject *_parent) :
	channelPrivate_(new PICNIC::ChannelPrivate(_parent))
{
	connect(channelPrivate_, SIGNAL(channelReady()), this, SLOT(onChannelReady()));
	connect(channelPrivate_, SIGNAL(channelError(PICNIC::Error)), this, SLOT(onChannelError(PICNIC::Error)));
	connect(channelPrivate_, SIGNAL(messageReceived(const PICNIC::ReceivedMessage &)), this, SLOT(onMessageReceived(const PICNIC::ReceivedMessage &)));
}

PICNIC::Channel::~Channel()
{
	if(channelPrivate_ != NULL)
	{
		delete channelPrivate_;
	}
}

PICNIC::Error PICNIC::Channel::bind(PICNIC::ChannelId _channelId)
{
	return channelPrivate_->bind(_channelId);
}

PICNIC::Error PICNIC::Channel::send(const PICNIC::UnicastMessage &_message)
{
	return channelPrivate_->send(_message);
}

PICNIC::Error PICNIC::Channel::send(const PICNIC::BroadcastMessage &_message)
{
	return channelPrivate_->send(_message);
}

void PICNIC::Channel::onChannelReady()
{
	emit channelReady();
}

void PICNIC::Channel::onChannelError(PICNIC::Error _error)
{
	emit channelError(_error);
}

void PICNIC::Channel::onMessageReceived(const PICNIC::ReceivedMessage &_message)
{
	emit messageReceived(_message);
}
