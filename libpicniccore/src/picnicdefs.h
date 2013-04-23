#ifndef PICNIC_DEFS_H
#define PICNIC_DEFS_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include "awarenetdefs.h"
#include "deviceinfo.h"

/*!
    \file picnicdefs.h
    This file contains the constant variables and enums used in PICNIC Core API.
*/

/*! \def PICNIC_ADDRESS_SIZE
    \brief Size of the addresses that are used in %PICNIC.
*/
#define PICNIC_ADDRESS_SIZE 6

/*!
    \namespace PICNIC
    Namespace for PICNIC
*/

namespace PICNIC
{
    /*! %PICNIC error codes. */
    enum Error {
        NoError = 0, /*!< All ok */
        InvalidArgumentError = -2, /*!< Invalid argument */
        NoPermissionsError = -3, /*!< Permission error */
        InternalError = -6, /*!< Internal core platform error */
        BusyError = -7, /*!< %PICNIC is busy too much traffic. */
        OutOfMemoryError = -8, /*!< Core platform out of memory. */
        InvalidVersionError = -9, /*!< Invalid version of %PICNIC or core platform in use. */

        NotImplemented = - 100, /*!< This feature is not implemented yet.*/

        // Connection
        AlreadyTryingToConnect = -900, /*!< Trying to connect to core platform. */
        CorePlatformNotConnected = -901, /*!< Connection to core platform is not established. */

        // Message sending
        AloneInAwarenet = -950, /*!< No other devices in the %PICNIC, cannot send messages. */
        AwarenetNotAvailableCurrently = -951, /*!< %PICNIC is not available currently. Device is using some other WLAN network. */
        PayloadSizeExceeded = -952, /*!< Payload of the message exceeds the maximum payload size of the %PICNIC. */

        // Channel
        ChannelIsAlreadyConnectedOrConnecting = -1000, /*!< Returned if bind() is called twice. */
        ChannelConnectCallTimedOut = -1001, /*!< Problem with core platform. Core platform might not be running properly. */
        ChannelIsNotConnected = -1002 /*!< Returned if sendMessage() is called before bind(). */
    };

    /*! %PICNIC network status. */
    enum NetworkStatus {
        Unavailable, /*!< %Network not available, device is using the radio for something else. */
        Alone, /*!< No other devices in the %PICNIC. */
        Ready, /*!< All ok, ready to send and receive messages. */
        Busy /*!< %PICNIC is congested by traffic, sending might not be possible. */
    };

    /*! %Message payload sensitivity. */
    enum PayloadSensitivity {
        PublicData = 0, /*!< Not sensitive. */
        ProtectedData = 1, /*!< Sensitive. The Core Platform will provide a random %PICNIC address when sending the message. Notice that is impossible to get responses.*/
        PrivateData = 2 /*!< Highly Sensitive. The Core Platform will provide a random %PICNIC address when sending the message. The message will only be send if there are enough devices in %PICNIC. Notice that is impossible to get responses.*/
    };

    /*! %Community types. */
    enum CommunityType {
        PublicPeerCommunity = 0, /*!< Public community */
        PrivatePeerCommunity = 1, /*!< Private community */
        PrivatePersonalCommunity = 2, /*!< TBD */
        OwnPrivatePersonalCommunity = 3 /*!< TBD */
    };
	
	/*! 
		Converts %PICNIC %Errors to %AwareNet %Errors.
	*/
	AwareNet::Error toAwn(Error _error);
	
	/*! 
		Converts %PICNIC %NetworkStatus to %AwareNet %NetworkStatus.
	*/
	AwareNet::NetworkStatus toAwn(NetworkStatus _networkStatus);
	
	/*! 
		Converts %PICNIC %PayloadSensitivity to %AwareNet %PayloadSensitivity.
	*/
	AwareNet::PayloadSensitivity toAwn(PayloadSensitivity _payloadSensitivity);
	
	/*! 
		Converts %PICNIC %CommunityType to %AwareNet %CommunityKind.
	*/
	AwareNet::CommunityKind toAwn(CommunityType _communityKind);
	
	/*! 
		Converts %AwareNet %Errors to %PICNIC %Errors.
	*/
	Error toPICNIC(AwareNet::Error _error);
	
	/*! 
		Converts %AwareNet %NetworkStatus to %PICNIC %NetworkStatus.
	*/
	NetworkStatus toPICNIC(AwareNet::NetworkStatus _networkStatus);
	
	/*! 
		Converts %AwareNet %PayloadSensitivity to %PICNIC %PayloadSensitivity.
	*/
	PayloadSensitivity toPICNIC(AwareNet::PayloadSensitivity _payloadSensitivity);
	
	/*! 
		Converts %AwareNet %CommunityKind to %PICNIC %CommunityType.
	*/
	CommunityType toPICNIC(AwareNet::CommunityKind _communityKind);
	
	/*! 
		Channel identifier
	*/
	typedef quint32 ChannelId;
	
}

#endif // PICNIC_DEFS_H
