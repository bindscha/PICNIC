#include "pcommunity.h"
#include "pchannel_p.h"
#include "pnetwork.h"
#include "pcommunitymanager.h"

// 
// Community
// 

PICNIC::Community::Community(CommunityPrivate *const _communityPrivate) : 
	communityPrivate_(_communityPrivate)
{
}

const PICNIC::CommunityPrivate *const PICNIC::Community::communityPrivate() const
{
	return communityPrivate_;
}

PICNIC::Community::CommunityType PICNIC::Community::communityType() const
{
	switch(communityPrivate_->getCommunityType())
	{
		case AwareNet::Community::Public : 
			return PICNIC::Community::Public;
        case AwareNet::Community::Private : 
			return PICNIC::Community::Private;
        case AwareNet::Community::Personal : 
			return PICNIC::Community::Personal;
        case AwareNet::Community::OwnPersonal : 
			return PICNIC::Community::OwnPersonal;
		default :	// Should never happen
			return PICNIC::Community::Public;
	}
}

PICNIC::Community::CommunityDescription PICNIC::Community::description() const
{
	return communityPrivate_->getDescription();
}
		
PICNIC::Community::ActivityStatus PICNIC::Community::activityStatus() const
{
	return communityPrivate_->isActive() ? PICNIC::Community::Active : PICNIC::Community::Inactive;
}

PICNIC::Community::UserAliasStatus PICNIC::Community::userAliasStatus() const
{
	return communityPrivate_->isUserAliasShown() ? PICNIC::Community::Shown : PICNIC::Community::Hidden;
}
