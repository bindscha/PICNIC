#ifndef PICNIC_DEVICEINFO_H
#define PICNIC_DEVICEINFO_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include <qdatetime.h>
#include "pconversions.h"

// TODO: this one needs to go...
#include "deviceaddress.h"

/*!
    \file pdeviceinfo.h
    This file contains the %DeviceInfo class used throughout %PICNIC to represent a particular device and its associated information.
*/

namespace PICNIC
{

	// Forward declarations
	class Network;
	
	/*! 
		\class DeviceInfo
		Represents a %PICNIC device and associated information.
	*/
    class DeviceInfo
    {
	public:
		/*! Device proximity */
		enum DeviceProximity {
			NEAR, /*!< Device is nearby */
			FAR /*!< Device is farther away */
		};
		
		/*! Device known */
		enum DeviceKnown {
			KNOWN,  /*!< Device is known */
			UNKNOWN /*!< Device is unknown */
		};
		
		/*! Type of device statistics */
		enum DeviceStatisticsType {
			LAST_MESSAGE_RECEIVED,  /*!< Timestamp of last message received */
			LAST_NEAR_MESSAGE_RECEIVED /*!< Timestamp of last message received as device was nearby */
		};
	
		/*! Device statistic */
		typedef QDateTime DeviceStatistic;

    private:
        DeviceInfo();
		Q_DISABLE_COPY(DeviceInfo);
		
	public:
        DeviceAddress address() const;
        DeviceProximity proximity() const;
        DeviceKnown known() const;
        DeviceStatistic statistic(DeviceStatisticsType _statistic) const;
		
	protected:
		DeviceInfo(const DeviceInfoPrivate &_deviceInfoPrivate);
		
		friend class Network;
		
	private:
		const DeviceInfoPrivate &deviceInfoPrivate_;
		
    };

} // namespace PICNIC

#endif // PICNIC_DEVICEINFO_H
