// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>

#include "testsender.h"
#include "pmessage.h"
#include "pcommunitymanager.h"


TestSender::TestSender(QObject *parent) :
    QObject(parent),
    channel_(this)
{
    // Channel provides signals to notify about changes in it's state.
    connect(&channel_, SIGNAL(channelError(PICNIC::Error)), this, SLOT(onChannelError(PICNIC::Error)));
    connect(&channel_, SIGNAL(channelReady()), this, SLOT(onChannelReady()));
    // In order to send and receive messages a channel
    // should be bound to a service ID.
    channel_.bind(EXAMPLE_SERVICE_ID);
}

/**
  * Broadcast a message
  * \param message The message to send
  */
void TestSender::send(QString payload)
{
	BroadcastMessage message(payload.toUtf8(), CommunityManager::defaultCommunity());
	channel_.send(message);
}

/**
  * Slot that is called when channel is ready.
  * Just send the hello message.
  */
void TestSender::onChannelReady()
{
    QTextStream out(stdout);
    out << "Channel ready" << endl;
    send("Hello world!");
}

/**
  * Print a message if there is an error binding
  * the channel.
  */
void TestSender::onChannelError(Error errorCode)
{
    QTextStream err(stderr);
    err << "Channel error " << errorCode << endl;
}

