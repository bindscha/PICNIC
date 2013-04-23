#ifndef PICNIC_CONVERSIONS_H
#define PICNIC_CONVERSIONS_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include "awarenetdefs.h"
#include "deviceinfo.h"
#include "channel.h"
#include "community.h"
#include "communitymanager.h"
#include "network.h"

/*!
    \file pconversions.h
    This file contains conversion definitions between %AwareNet and %PICNIC.
*/

namespace PICNIC
{
    
	/*! Private device information definition */
	typedef AwareNet::DeviceInfo DeviceInfoPrivate;
	
	/*! Private community definition */
	typedef AwareNet::Community CommunityPrivate;
	
	/*! Private community manager definition */
	typedef AwareNet::CommunityManager CommunityManagerPrivate;
	
	/*! Private network definition */
	typedef AwareNet::Network NetworkPrivate;
	
	/*! Private network status definition */
	typedef AwareNet::NetworkStatus NetworkStatusPrivate;
	
}

#endif // PICNIC_CONVERSIONS_H
