// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>

#include "testreceiver.h"
#include "pmessage.h"


TestReceiver::TestReceiver(QObject *parent) :
    QObject(parent),
    channel_(this)
{
    // Channel provides signals to notify about changes in it's state.
	connect(&channel_, SIGNAL(channelReady()), this, SLOT(onChannelReady()));
    connect(&channel_, SIGNAL(channelError(PICNIC::Error)), this, SLOT(onChannelError(PICNIC::Error)));
    connect(&channel_, SIGNAL(messageReceived(PICNIC::ReceivedMessage)), this, SLOT(onMessageReceived(PICNIC::ReceivedMessage)));
	
    // In order to send and receive messages a channel
    // should be bound to a service ID.
    channel_.bind(EXAMPLE_SERVICE_ID);
}

/**
  * Slot that is called when channel is ready.
  */
void TestReceiver::onChannelReady()
{
    QTextStream out(stdout);
    out << "Channel ready" << endl;
}

/**
  * Print a message if there is an error binding
  * the channel.
  */
void TestReceiver::onChannelError(Error errorCode)
{
    QTextStream err(stderr);
    err << "Channel error " << errorCode << endl;
}

/**
  * Slot that is called when a message is received.
  */
void TestReceiver::onMessageReceived(const PICNIC::ReceivedMessage &msg)
{
    QTextStream out(stdout);
    out << "Received Message: " << QString(msg.payload()) << endl;
}

