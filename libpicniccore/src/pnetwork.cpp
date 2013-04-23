#include "pnetwork.h"
#include "pmessage.h"
#include "pcommunity.h"
#include "message.h"

//
// Network
//

// This allows to connect the signal through two namespaces. Let's remember to whack the idiot that did not handle namespaces...
typedef AwareNet::DeviceInfo DeviceInfoDummy;
typedef AwareNet::NetworkStatus NetworkStatusDummy;

PICNIC::Network::Network() :
	networkWrapper_(AwareNet::Network::getInstance())
{
	connect(&networkWrapper_, SIGNAL(deviceInfoReady(const DeviceInfo &)), this, SLOT(onDeviceInfoReady(const DeviceInfo &)));
	connect(&networkWrapper_, SIGNAL(networkStatusChanged(NetworkStatusDummy)), this, SLOT(onNetworkStatusChanged(NetworkStatusDummy)));
	connect(&networkWrapper_, SIGNAL(neighborhoodChanged(quint32)), this, SLOT(onNeighborhoodChanged(quint32)));
	connect(&networkWrapper_, SIGNAL(networkChanged(quint32)), this, SLOT(onNetworkChanged(quint32)));
	connect(&networkWrapper_, SIGNAL(addressChanged(DeviceAddress)), this, SLOT(onAddressChanged(DeviceAddress)));
	connect(&networkWrapper_, SIGNAL(deviceAppeared(DeviceAddress, bool)), this, SLOT(onDeviceAppeared(DeviceAddress, bool)));
	connect(&networkWrapper_, SIGNAL(deviceDisappeared(DeviceAddress)), this, SLOT(onDeviceDisappeared(DeviceAddress)));
}

PICNIC::Network::~Network()
{
}

PICNIC::Network &PICNIC::Network::instance()
{
	static PICNIC::Network instance;
	return instance;
}

PICNIC::Error PICNIC::Network::send(PICNIC::ChannelId _channelId, const PICNIC::UnicastMessage &_message)
{
	AwareNet::UnicastMessage messageToSend(_message.marshalledPayload());
	messageToSend.setCommunity(const_cast<PICNIC::CommunityPrivate *> (_message.community().communityPrivate()));
	messageToSend.setReceiver(_message.receiver());
	messageToSend.setSensitivity(toAwn(_message.payloadSensitivity()));
	return (PICNIC::Error) networkWrapper_.sendMessage(_channelId, messageToSend);
}

PICNIC::Error PICNIC::Network::send(PICNIC::ChannelId _channelId, const PICNIC::BroadcastMessage &_message)
{
	AwareNet::BroadcastMessage messageToSend(_message.marshalledPayload());
	messageToSend.setCommunity(const_cast<PICNIC::CommunityPrivate *> (_message.community().communityPrivate()));
	messageToSend.setSensitivity(toAwn(_message.payloadSensitivity()));
	messageToSend.setMaxHopCount(_message.maxHopCount());
	messageToSend.setMaxRange(_message.maxRange());
	messageToSend.setMaxReceivers(_message.maxReceivers());
	return (PICNIC::Error) networkWrapper_.sendMessage(_channelId, messageToSend);
}

void PICNIC::Network::deviceInfoReq(const DeviceAddress &_address)
{
	networkWrapper_.retrieveDeviceInfo(_address);
}

PICNIC::NetworkStatus PICNIC::Network::networkStatus() const
{
	return PICNIC::toPICNIC(networkWrapper_.getNetworkStatus());
}

DeviceAddress PICNIC::Network::ownAddress() const
{
	return networkWrapper_.getOwnAddress();
}

PICNIC::Network::NetworkId PICNIC::Network::networkId() const
{
	return networkWrapper_.getNetworkId();
}

PICNIC::Network::PayloadSize PICNIC::Network::maxPayloadSize() const
{
	return networkWrapper_.getMaxPayloadSize();
}

PICNIC::Network::NetworkSize PICNIC::Network::estimatedNetworkSize() const
{
	return networkWrapper_.getEstimatedNetworkSize();
}

PICNIC::Network::NeighborCount PICNIC::Network::neighborCount() const
{
	return networkWrapper_.getNeighborCount();
}

void PICNIC::Network::onDeviceInfoReady(const DeviceInfoPrivate &_deviceInformation)
{
	emit PICNIC::Network::deviceInfoReady(PICNIC::DeviceInfo(_deviceInformation));
}

void PICNIC::Network::onNetworkStatusChanged(NetworkStatusPrivate _newStatus)
{
	emit PICNIC::Network::networkStatusChanged(PICNIC::toPICNIC(_newStatus));
}

void PICNIC::Network::onNeighborhoodChanged(quint32 _neighborCount)
{
	emit PICNIC::Network::neighborhoodChanged(_neighborCount);
}

void PICNIC::Network::onNetworkChanged(quint32 _estimatedSize)
{
	emit PICNIC::Network::networkChanged(_estimatedSize);
}

void PICNIC::Network::onAddressChanged(const DeviceAddress &_newAddress)
{
	emit PICNIC::Network::addressChanged(_newAddress);
}

void PICNIC::Network::onDeviceAppeared(const DeviceAddress &_address, bool _isNeighbor)
{
	emit PICNIC::Network::deviceAppeared(_address, _isNeighbor ? PICNIC::Network::NEIGHBOR : PICNIC::Network::NOT_NEIGHBOR);
}

void PICNIC::Network::onDeviceDisappeared(const DeviceAddress &_address)
{
	emit PICNIC::Network::deviceDisappeared(_address);
}
