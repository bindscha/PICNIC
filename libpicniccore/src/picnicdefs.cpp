#include "picnicdefs.h"
#include "awarenetdefs.h"

//
// PICNIC Defintions
//

AwareNet::Error PICNIC::toAwn(PICNIC::Error _error)
{
	switch(_error)
	{
		case PICNIC::NoError : 
			return AwareNet::NoError;
        case PICNIC::InvalidArgumentError :
			return AwareNet::InvalidArgumentError;
        case PICNIC::NoPermissionsError :
			return AwareNet::NoPermissionsError;
        case PICNIC::InternalError :
			return AwareNet::InternalError;
        case PICNIC::BusyError :
			return AwareNet::BusyError;
        case PICNIC::OutOfMemoryError :
			return AwareNet::OutOfMemoryError;
        case PICNIC::InvalidVersionError :
			return AwareNet::InvalidVersionError;
        case PICNIC::NotImplemented :
			return AwareNet::NotImplemented;
        case PICNIC::AlreadyTryingToConnect :
			return AwareNet::AlreadyTryingToConnect;
        case PICNIC::CorePlatformNotConnected :
			return AwareNet::CorePlatformNotConnected;
        case PICNIC::AloneInAwarenet :
			return AwareNet::AloneInAwarenet;
        case PICNIC::AwarenetNotAvailableCurrently :
			return AwareNet::AwarenetNotAvailableCurrently;
        case PICNIC::PayloadSizeExceeded :
			return AwareNet::PayloadSizeExceeded;
        case PICNIC::ChannelIsAlreadyConnectedOrConnecting :
			return AwareNet::ChannelIsAlreadyConnectedOrConnecting;
        case PICNIC::ChannelConnectCallTimedOut :
			return AwareNet::ChannelConnectCallTimedOut;
        case PICNIC::ChannelIsNotConnected :
			return AwareNet::ChannelIsNotConnected;
		default :	// Should never happen
			return AwareNet::InternalError;
	}
}
	
AwareNet::NetworkStatus PICNIC::toAwn(PICNIC::NetworkStatus _networkStatus)
{
	switch(_networkStatus)
	{
		case PICNIC::Unavailable : 
			return AwareNet::Unavailable;
        case PICNIC::Alone : 
			return AwareNet::Alone;
        case PICNIC::Ready : 
			return AwareNet::Ready;
        case PICNIC::Busy :
			return AwareNet::Busy;
		default :	// Should never happen
			return AwareNet::Unavailable;
	}
}
	
AwareNet::PayloadSensitivity PICNIC::toAwn(PICNIC::PayloadSensitivity _payloadSensitivity)
{
	switch(_payloadSensitivity)
	{
		case PICNIC::PublicData :
			return AwareNet::PublicData;
        case PICNIC::ProtectedData :
			return AwareNet::ProtectedData;
        case PICNIC::PrivateData :
			return AwareNet::PrivateData;
		default : 	// Should never happen
			return AwareNet::PublicData;
	}
}
	
AwareNet::CommunityKind PICNIC::toAwn(PICNIC::CommunityType _communityKind)
{
	switch(_communityKind)
	{
		case PICNIC::PublicPeerCommunity : 
			return AwareNet::PublicPeerCommunity;
        case PICNIC::PrivatePeerCommunity : 
			return AwareNet::PrivatePeerCommunity;
        case PICNIC::PrivatePersonalCommunity : 
			return AwareNet::PrivatePersonalCommunity;
        case PICNIC::OwnPrivatePersonalCommunity : 
			return AwareNet::OwnPrivatePersonalCommunity;
		default :	// Should never happen
			return AwareNet::PublicPeerCommunity;
	}
}

PICNIC::Error PICNIC::toPICNIC(AwareNet::Error _error)
{
	switch(_error)
	{
		case AwareNet::NoError : 
			return PICNIC::NoError;
        case AwareNet::InvalidArgumentError :
			return PICNIC::InvalidArgumentError;
        case AwareNet::NoPermissionsError :
			return PICNIC::NoPermissionsError;
        case AwareNet::InternalError :
			return PICNIC::InternalError;
        case AwareNet::BusyError :
			return PICNIC::BusyError;
        case AwareNet::OutOfMemoryError :
			return PICNIC::OutOfMemoryError;
        case AwareNet::InvalidVersionError :
			return PICNIC::InvalidVersionError;
        case AwareNet::NotImplemented :
			return PICNIC::NotImplemented;
        case AwareNet::AlreadyTryingToConnect :
			return PICNIC::AlreadyTryingToConnect;
        case AwareNet::CorePlatformNotConnected :
			return PICNIC::CorePlatformNotConnected;
        case AwareNet::AloneInAwarenet :
			return PICNIC::AloneInAwarenet;
        case AwareNet::AwarenetNotAvailableCurrently :
			return PICNIC::AwarenetNotAvailableCurrently;
        case AwareNet::PayloadSizeExceeded :
			return PICNIC::PayloadSizeExceeded;
        case AwareNet::ChannelIsAlreadyConnectedOrConnecting :
			return PICNIC::ChannelIsAlreadyConnectedOrConnecting;
        case AwareNet::ChannelConnectCallTimedOut :
			return PICNIC::ChannelConnectCallTimedOut;
        case AwareNet::ChannelIsNotConnected :
			return PICNIC::ChannelIsNotConnected;
		default :	// Should never happen
			return PICNIC::InternalError;
	}
}
	
PICNIC::NetworkStatus PICNIC::toPICNIC(AwareNet::NetworkStatus _networkStatus)
{
	switch(_networkStatus)
	{
		case AwareNet::Unavailable : 
			return PICNIC::Unavailable;
        case AwareNet::Alone : 
			return PICNIC::Alone;
        case AwareNet::Ready : 
			return PICNIC::Ready;
        case AwareNet::Busy :
			return PICNIC::Busy;
		default :	// Should never happen
			return PICNIC::Unavailable;
	}
}
	
PICNIC::PayloadSensitivity PICNIC::toPICNIC(AwareNet::PayloadSensitivity _payloadSensitivity)
{
	switch(_payloadSensitivity)
	{
		case AwareNet::PublicData :
			return PICNIC::PublicData;
        case AwareNet::ProtectedData :
			return PICNIC::ProtectedData;
        case AwareNet::PrivateData :
			return PICNIC::PrivateData;
		default : 	// Should never happen
			return PICNIC::PublicData;
	}
}
	
PICNIC::CommunityType PICNIC::toPICNIC(AwareNet::CommunityKind _communityKind)
{
	switch(_communityKind)
	{
		case AwareNet::PublicPeerCommunity : 
			return PICNIC::PublicPeerCommunity;
        case AwareNet::PrivatePeerCommunity : 
			return PICNIC::PrivatePeerCommunity;
        case AwareNet::PrivatePersonalCommunity : 
			return PICNIC::PrivatePersonalCommunity;
        case AwareNet::OwnPrivatePersonalCommunity : 
			return PICNIC::OwnPrivatePersonalCommunity;
		default :	// Should never happen
			return PICNIC::PublicPeerCommunity;
	}
}
