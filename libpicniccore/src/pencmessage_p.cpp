#include "pencmessage_p.h"
#include "pencrypt.h"

//
// EncryptedUnicastMessagePrivate
//

PICNIC::EncryptedUnicastMessagePrivate::EncryptedUnicastMessagePrivate(const QByteArray& _content, const PICNIC::Community &_community, const DeviceAddress &_receiver, const PICNIC::PayloadSensitivity _payloadSensitivity) :
	PICNIC::UnicastMessagePrivate::UnicastMessagePrivate(_content, _community, _receiver, _payloadSensitivity), marshalledPayload_(initPayload(_content))
{	
}

PICNIC::EncryptedUnicastMessagePrivate::EncryptedUnicastMessagePrivate(const EncryptedUnicastMessage &_unicastMessage) :
	PICNIC::UnicastMessagePrivate::UnicastMessagePrivate(_unicastMessage.payload(), _unicastMessage.community(), _unicastMessage.receiver(), _unicastMessage.payloadSensitivity()), marshalledPayload_(_unicastMessage.marshalledPayload())  
{
}

const QByteArray PICNIC::EncryptedUnicastMessagePrivate::marshalledPayload() const
{
	return marshalledPayload_;
}

const QByteArray PICNIC::EncryptedUnicastMessagePrivate::initPayload(const QByteArray &_content)
{
	QByteArray* temp = new QByteArray();
	Encrypt::EAXEncrypt(_content, *temp, key(), nonce()); //TODO error management
	QByteArray ret = QByteArray(*temp);
	delete temp;
	return ret;
}

const QByteArray PICNIC::EncryptedUnicastMessagePrivate::key()
{
	return QByteArray("crypto is fun !!");
}
const QByteArray PICNIC::EncryptedUnicastMessagePrivate::nonce()
{
	return QByteArray("a nice nonce ! !");				  
}

//
// EncryptedBroadcastMessagePrivate
//

PICNIC::EncryptedBroadcastMessagePrivate::EncryptedBroadcastMessagePrivate(const QByteArray& _content, const PICNIC::Community &_community, const PICNIC::PayloadSensitivity _payloadSensitivity, const PICNIC::HopCount _maxHopCount, const PICNIC::Range _maxRange, const PICNIC::ReceiverCount _maxReceivers) :
	PICNIC::BroadcastMessagePrivate::BroadcastMessagePrivate(_content, _community,_payloadSensitivity,_maxHopCount,_maxRange,_maxReceivers), marshalledPayload_(initPayload(_content)) 
{
}

PICNIC::EncryptedBroadcastMessagePrivate::EncryptedBroadcastMessagePrivate(const EncryptedBroadcastMessage &_broadcastMessage) :
	PICNIC::BroadcastMessagePrivate::BroadcastMessagePrivate(_broadcastMessage.payload(), _broadcastMessage.community(),_broadcastMessage.payloadSensitivity(),_broadcastMessage.maxHopCount(),_broadcastMessage.maxRange(),_broadcastMessage.maxReceivers()), marshalledPayload_(_broadcastMessage.marshalledPayload())
{
}

const QByteArray PICNIC::EncryptedBroadcastMessagePrivate::marshalledPayload() const
{
	return marshalledPayload_;
}

const QByteArray PICNIC::EncryptedBroadcastMessagePrivate::initPayload(const QByteArray& _content)
{
	QByteArray* temp = new QByteArray();
	Encrypt::EAXEncrypt(_content, *temp, key(), nonce()); //TODO error management
	QByteArray ret = QByteArray(*temp);
	delete temp;
	return ret;
}


const QByteArray PICNIC::EncryptedBroadcastMessagePrivate::key()
{
	return QByteArray("crypto is fun !!");
}
const QByteArray PICNIC::EncryptedBroadcastMessagePrivate::nonce()
{
	return QByteArray("a nice nonce ! !");				  
}

//
// DecryptedReceivedMessagePrivate
//
PICNIC::DecryptedReceivedMessagePrivate::DecryptedReceivedMessagePrivate(const QByteArray &_content, const PICNIC::Community &_community, const DeviceAddress &_sender, const PICNIC::HopCount _hopCount) : 
	PICNIC::ReceivedMessagePrivate::ReceivedMessagePrivate(initPayload(_content), _community,_sender,_hopCount), marshalledPayload_(QByteArray(_content))
{
}

PICNIC::DecryptedReceivedMessagePrivate::DecryptedReceivedMessagePrivate(const DecryptedReceivedMessage &_receivedMessage) : 
	PICNIC::ReceivedMessagePrivate::ReceivedMessagePrivate(_receivedMessage.payload(), _receivedMessage.community(),_receivedMessage.sender(),_receivedMessage.hopCount()), marshalledPayload_(_receivedMessage.marshalledPayload())
{
}

const QByteArray PICNIC::DecryptedReceivedMessagePrivate::marshalledPayload() const
{
	return marshalledPayload_;
}

const QByteArray PICNIC::DecryptedReceivedMessagePrivate::initPayload(const QByteArray& _content)
{
	QByteArray* temp = new QByteArray();
	Encrypt::EAXDecrypt(_content, *temp, key(), nonce()); //TODO error management
	QByteArray ret = QByteArray(*temp);
	delete temp;
	return ret;
}


const QByteArray PICNIC::DecryptedReceivedMessagePrivate::key()
{
	return QByteArray("crypto is fun !!");
}
const QByteArray PICNIC::DecryptedReceivedMessagePrivate::nonce()
{
	return QByteArray("a nice nonce ! !");				  
}


