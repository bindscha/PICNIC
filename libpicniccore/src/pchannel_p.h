#ifndef PICNIC_CHANNEL_P_H
#define PICNIC_CHANNEL_P_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include "picnicdefs.h"
#include "pconversions.h"
#include "pmessage.h"
#include "message.h"

/*!
    \file pchannel_p.h
    This file contains the %ChannelPrivate and the %ChannelHelper classes used as helper classes for %Channel.
*/

namespace PICNICH
{

	// This allows to connect the signal through two namespaces. Let's remember to whack the idiot that did not handle namespaces...
	typedef AwareNet::ReceivedMessage ReceivedMessage;

	/*! 
		\class ChannelHelper
		Represents a %PICNIC channel helper. This class is part of the %PICNICH namespace.
	*/
	
    class ChannelHelper : public QObject
    {
    Q_OBJECT

    public:
        ChannelHelper(QObject *_parent = 0);
		
		PICNIC::Error bind(PICNIC::ChannelId _channelId);

        PICNIC::Error send(const AwareNet::UnicastMessage &_message);
        PICNIC::Error send(const AwareNet::BroadcastMessage &_message);

	private:
	    Q_DISABLE_COPY(ChannelHelper)
		
    signals:
        void channelReady();
        void channelError(PICNIC::Error _error);
        void messageReceived(const PICNICH::ReceivedMessage &_message);

    private slots:
		void onChannelReady();
        void onChannelError(int _error);
		void onMessageReceived(const ReceivedMessage &_message);
	
    private:
		AwareNet::Channel channelPrivate_;
    };

} // namespace PICNICH

namespace PICNIC {

	// Forward declarations
	class BroadcastMessage;
	class UnicastMessage;
	class ReceivedMessage;
	
	/*! 
		\class ChannelPrivate
		Private implementing class for %Channel.
	*/
    class ChannelPrivate : public QObject
    {
    Q_OBJECT

    public:
        ChannelPrivate(QObject *_parent = 0);

        Error bind(ChannelId _channelId);

        Error send(const UnicastMessage &_message);
        Error send(const BroadcastMessage &_message);

	private:
	    Q_DISABLE_COPY(ChannelPrivate)
		
    signals:
        void channelReady();
        void channelError(PICNIC::Error _error);
        void messageReceived(const PICNIC::ReceivedMessage &_message);

    private slots:
		void onChannelReady();
        void onChannelError(PICNIC::Error _error);
		void onMessageReceived(const PICNICH::ReceivedMessage &_message);
	
    private:
		PICNICH::ChannelHelper channelHelper_;
    };
	
} // namespace PICNIC

#endif // PICNIC_CHANNEL_P_H

