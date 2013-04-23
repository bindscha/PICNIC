#ifndef PICNIC_NETWORK_H
#define PICNIC_NETWORK_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include <QMutex>
#include "picnicdefs.h"
#include "pconversions.h"
#include "pdeviceinfo.h"

#include "deviceaddress.h"

/*!
    \file pnetwork.h
    This file contains the %Network class which represents the actual NIC network in %PICNIC.
*/

namespace PICNIC
{

	// Forward declarations
    class UnicastMessage;
    class BroadcastMessage;

	/*! 
		\class Network
		Represents the actual network in %PICNIC.
	*/
    class Network : public QObject
    {
        Q_OBJECT
		
	public:		
		/*! Network identifier */
		typedef QString NetworkId;
		
		/*! Message payload size */
		typedef quint32 PayloadSize;
		
		/*! Network size */
		typedef quint32 NetworkSize;
		
		/*! Number of neighbors */
		typedef quint32 NeighborCount;
		
		/*! Device neighbor status */
		enum NeighborStatus {
			NEIGHBOR, /*!< Device is a neighbor */
			NOT_NEIGHBOR /*!< Device is not a neighbor */
		};

	private:
		Network();
		~Network();
		Q_DISABLE_COPY(Network);

    public:
        static Network &instance();

    public:
        Error send(ChannelId _channelId, const UnicastMessage &_message);
        Error send(ChannelId _channelId, const BroadcastMessage &_message);

        void deviceInfoReq(const DeviceAddress &_address);

    public:
        NetworkStatus networkStatus() const;
        DeviceAddress ownAddress() const;
        NetworkId networkId() const;
        PayloadSize maxPayloadSize() const;
        NetworkSize estimatedNetworkSize() const;
        NeighborCount neighborCount() const;

    signals:
        void deviceInfoReady(const DeviceInfo &_deviceInformation);
        void networkStatusChanged(NetworkStatus _newStatus);
        void neighborhoodChanged(NeighborCount _neighborCount);
        void networkChanged(NetworkSize _estimatedSize);
        void addressChanged(const DeviceAddress &_newAddress);
        void deviceAppeared(const DeviceAddress &_address, NeighborStatus _neighborStatus);
        void deviceDisappeared(const DeviceAddress &_address);

	private slots:
		void onDeviceInfoReady(const DeviceInfoPrivate &_deviceInformation);
        void onNetworkStatusChanged(NetworkStatusPrivate _newStatus);
        void onNeighborhoodChanged(quint32 _neighborCount);
        void onNetworkChanged(quint32 _estimatedSize);
        void onAddressChanged(const DeviceAddress &_newAddress);
        void onDeviceAppeared(const DeviceAddress &_address, bool _isNeighbor);
        void onDeviceDisappeared(const DeviceAddress &_address);
		
    private:
        NetworkPrivate &networkWrapper_;
		
    };

} // namespace PICNIC

#endif // PICNIC_NETWORK_H
