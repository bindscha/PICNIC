#ifndef TESTSENDER_H
#define TESTSENDER_H

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

class TestSender : public QObject
{
Q_OBJECT
public:
    explicit TestSender(QObject *parent = 0);
	
    // Send a message
    void send(QString payload);

public slots:
    // Called when the channel is set up to
    // send a hello message
    void onChannelReady();
	
    // Called when there is an error
    void onChannelError(PICNIC::Error errorCode);
private:
    Channel channel_;
};

#endif // TESTSENDER_H
