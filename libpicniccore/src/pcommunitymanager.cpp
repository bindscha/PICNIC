#include "pcommunitymanager.h"
#include "pcommunity.h"

// Thank you NRC!
#include "message.h"

// 
// CommunityManager
// 

PICNIC::CommunityManager::CommunityManager() : 
	communityManagerPrivate_(CommunityManagerPrivate::getInstance())
{
}

PICNIC::CommunityManager::~CommunityManager()
{
}

PICNIC::CommunityManager &PICNIC::CommunityManager::instance()
{
	static PICNIC::CommunityManager instance;
	return instance;
}

const PICNIC::Community &PICNIC::CommunityManager::defaultCommunity()
{
	static PICNIC::Community defaultCommunity = PICNIC::Community(const_cast<PICNIC::CommunityPrivate *const> (AwareNet::BroadcastMessage().getCommunity()));
	return defaultCommunity;
}
