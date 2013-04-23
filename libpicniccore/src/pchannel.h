#ifndef PICNIC_CHANNEL_H
#define PICNIC_CHANNEL_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include "picnicdefs.h"
#include "pconversions.h"


/*!
    \file pchannel.h
    This file contains the %Channel class used throughout PICNIC to represent a communication channel.
*/

namespace PICNIC
{

	// Forward declarations
	class ChannelPrivate;
	class BroadcastMessage;
	class UnicastMessage;
	class ReceivedMessage;
	
	/*! 
		\class Channel
		Represents a %PICNIC community channel.
	*/
	
    class Channel : public QObject
    {
    Q_OBJECT

    public:
        Channel(QObject *_parent = 0);
		~Channel();
		
        Error bind(ChannelId _channelId);

        Error send(const UnicastMessage &_message);
        Error send(const BroadcastMessage &_message);

	private:
	    Q_DISABLE_COPY(Channel)
		
    signals:
        void channelReady();
        void channelError(PICNIC::Error _error);
        void messageReceived(const PICNIC::ReceivedMessage &_message);

    private slots:
		void onChannelReady();
        void onChannelError(PICNIC::Error _error);
		void onMessageReceived(const PICNIC::ReceivedMessage &_message);
	
    private:
		ChannelPrivate *const channelPrivate_;
    };

} // namespace PICNIC

#endif // PICNIC_CHANNEL_H

