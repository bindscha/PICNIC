#ifndef PICNIC_COMMUNITYMANAGER_H
#define PICNIC_COMMUNITYMANAGER_H

// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>


#include <QObject>
#include <QByteArray>
#include <QMutex>
#include "pconversions.h"

/*!
    \file pcommunitymanager.h
    This file contains the %CommunityManager used to manage (i.e. create, delete) %PICNIC %Communities.
*/

namespace PICNIC
{

    // Forward declarations
    class Community;

	/*! 
		\class CommunityManager
		Manages %PICNIC %Communities.
	*/
    class CommunityManager : public QObject
    {
    Q_OBJECT

    public:
        static CommunityManager &instance();
		
		static const Community &defaultCommunity();

    private:
        CommunityManager();
		~CommunityManager();
		Q_DISABLE_COPY(CommunityManager);

    public:
        /*int createCommunity(QByteArray &identifier, QString &description, QString &userAlias, bool setActive = true, bool showAlias = true);
        int createPrivateCommunity(QByteArray &identifier, QString &description, QString &userAlias, QByteArray &sharedKey, bool setActive = true, bool showAlias = true);
        int createPersonalCommunity(QByteArray &identifier, QString &description, QString &userAlias, QByteArray &publicKey, QByteArray &privateKey, bool setActive = true, bool showAlias = true);
        int destroyCommunity(Community &community);*/

    private:
        CommunityManagerPrivate &communityManagerPrivate_;
        
    };

} // namespace PICNIC

#endif // PICNIC_COMMUNITYMANAGER_H
