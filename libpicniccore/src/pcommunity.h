#ifndef PICNIC_COMMUNITY_H
#define PICNIC_COMMUNITY_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include <QMetaType>
#include <QString>
#include "pconversions.h"

/*!
    \file pcommunity.h
    This file contains the %Community class used throughout PICNIC to represent a community and its associated information.
*/

namespace PICNIC
{

	// Forward declarations
	class ChannelPrivate;
	class Network;
	
	class CommunityManager;

	/*! 
		\class Community
		Represents a %PICNIC community and associated information.
	*/
    class Community : public QObject
    {
    Q_OBJECT

    public:
		/*! Community type */
        enum CommunityType {
            Public,     /*!< No encryption */
            Private,    /*!< Shared key encryption */
            Personal,   /*!< Someone's personal community */
            OwnPersonal /*!< Devices own personal community */
        };
		
		/*! Community description */
		typedef QString CommunityDescription;
		
		/*! Community activity status */
		enum ActivityStatus {
			Active,		/*!< Community is active */
			Inactive	/*!< Community is inactive */
		};
		
		/*! Community user alias hiding status */
		enum UserAliasStatus {
			Shown,		/*!< User alias is shown */
			Hidden		/*!< User alias is hidden */
		};

    private:
        Community();
		Q_DISABLE_COPY(Community);

    public:
        CommunityType communityType() const;
        CommunityDescription description() const;
		
		ActivityStatus activityStatus() const;
        UserAliasStatus userAliasStatus() const;
        
		// Disabled until support for these is provided!
		// void activityStatusIs(ActivityStatus _activityStatus);
        // void userAliasStatusIs(UserAliasStatus _userAliasStatus);
		
	signals:
		void userAliasChanged(QString _newUserAlias);
		
	protected:
        Community(CommunityPrivate *const _communityPrivate);
		
		const CommunityPrivate *const communityPrivate() const;
		
		friend class ChannelPrivate;
		friend class Network;
		
		friend class CommunityManager;
		
    protected:
		CommunityPrivate *const communityPrivate_;
	
    };

} // namespace PICNIC

#endif // PICNIC_COMMUNITY_H
