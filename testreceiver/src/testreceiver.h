#ifndef TESTRECEIVER_H
#define TESTRECEIVER_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include "pmessage.h"
#include "pchannel.h"
#include "picnicdefs.h"

#define EXAMPLE_SERVICE_ID 9999

using namespace PICNIC;

class TestReceiver : public QObject
{
Q_OBJECT
public:
    explicit TestReceiver(QObject *parent = 0);

public slots:
    // Called when the channel is set up to
    // send a hello message
    void onChannelReady();
	
    // Called when there is an error
    void onChannelError(PICNIC::Error errorCode);
	
	// Called when a message is received
	void onMessageReceived(const PICNIC::ReceivedMessage &msg);
	
private:
    Channel channel_;
};

#endif // TESTRECEIVER_H
