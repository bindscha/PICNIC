#include "pdeviceinfo.h"
#include "pnetwork.h"

//
// DeviceInfo
//

PICNIC::DeviceInfo::DeviceInfo(const DeviceInfoPrivate &_deviceInfoPrivate) :
	deviceInfoPrivate_(_deviceInfoPrivate)
{
}

DeviceAddress PICNIC::DeviceInfo::address() const
{
	return deviceInfoPrivate_.address();
}

PICNIC::DeviceInfo::DeviceProximity PICNIC::DeviceInfo::proximity() const
{
	return deviceInfoPrivate_.isNear() ? PICNIC::DeviceInfo::NEAR : PICNIC::DeviceInfo::FAR;
}

PICNIC::DeviceInfo::DeviceKnown PICNIC::DeviceInfo::known() const
{
	return deviceInfoPrivate_.isKnown() ? PICNIC::DeviceInfo::KNOWN : PICNIC::DeviceInfo::UNKNOWN;
}

PICNIC::DeviceInfo::DeviceStatistic PICNIC::DeviceInfo::statistic(DeviceStatisticsType _statistic) const
{
	switch(_statistic) {
		case PICNIC::DeviceInfo::LAST_MESSAGE_RECEIVED :
			return deviceInfoPrivate_.receivedLastMessage();
		case PICNIC::DeviceInfo::LAST_NEAR_MESSAGE_RECEIVED : 
			return deviceInfoPrivate_.receivedLastNearMessage();
		default : 	// Should never happen..
			return QDateTime::QDateTime();
	}
}
