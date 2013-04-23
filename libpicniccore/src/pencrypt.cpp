#include "pencrypt.h"
#define TAU 15

/*
Encrypts or decrypts (depending on the last boolean) the input buffer over inputLength bytes and stores the result in outputBuffer. 
The encryption algorithm is "algo" using the mode of operation "mode". 
*/
bool PICNIC::Encrypt::crypt(const char * inputBuffer, const size_t inputLength,  char * outputBuffer, const size_t outputLength,  const char * key, const size_t keyLength,  const char * iniVector, const int algo, const int mode, const unsigned int flags, bool encrypt)
{

    gcry_error_t     gcryError;
    gcry_cipher_hd_t gcryCipherHd;
    size_t blkLength = gcry_cipher_get_algo_blklen(algo);

    gcryError = gcry_cipher_open(&gcryCipherHd, algo, mode,flags); 
    if (gcryError)
    {
        std::cerr <<"gcry_cipher_open failed:" <<gcry_strsource(gcryError) <<"/" <<gcry_strerror(gcryError) <<std::endl;
        return false;
    }

    gcryError = gcry_cipher_setkey(gcryCipherHd, key, keyLength);
    if (gcryError)
    {
        std::cerr <<"gcry_cipher_setkey failed:" <<gcry_strsource(gcryError) <<"/" <<gcry_strerror(gcryError) <<std::endl;
        return false;
    }
//different function for ctr mode
    gcryError = (mode == GCRY_CIPHER_MODE_CTR) ? gcry_cipher_setctr(gcryCipherHd, iniVector, blkLength) : gcry_cipher_setiv(gcryCipherHd, iniVector, blkLength);
    if (gcryError)
    {
        std::cerr <<"gcry_cipher_setiv failed:" <<gcry_strsource(gcryError) <<"/" <<gcry_strerror(gcryError) <<std::endl;
        return false;
    }
if(encrypt)
{
    gcryError = gcry_cipher_encrypt(gcryCipherHd, outputBuffer, outputLength, inputBuffer, inputLength);
    if (gcryError)
    {
        std::cerr <<"gcry_cipher_encrypt failed:" <<gcry_strsource(gcryError) <<"/" <<gcry_strerror(gcryError) <<std::endl;
        return false;
    }
}
else
{
gcryError = gcry_cipher_decrypt(gcryCipherHd, outputBuffer, outputLength, inputBuffer, inputLength);
    if (gcryError)
    {
        std::cerr <<"gcry_cipher_decrypt failed:" <<gcry_strsource(gcryError) <<"/" <<gcry_strerror(gcryError) <<std::endl;
        return false;
    }
}
 gcry_cipher_close(gcryCipherHd);
return true;
}

/*
Computes the CBCMAC of the message using encryption algorithm "algo".
*/
void PICNIC::Encrypt::CBCMAC(const char * message, const size_t messageLength, char * MACBuffer, const char * key, const size_t keyLength, const int algo)
{
	char iniVector[gcry_cipher_get_algo_blklen(algo)];
	memset(iniVector, 0, gcry_cipher_get_algo_blklen(algo));
	crypt(message, messageLength, MACBuffer, gcry_cipher_get_algo_blklen(algo), key, keyLength, iniVector, algo, GCRY_CIPHER_MODE_CBC, GCRY_CIPHER_CBC_MAC,true);
}


/*
Multiplies by two a 128 bit word in GF(2^128)
*/
void PICNIC::Encrypt::multByTwo(unsigned char k[]){
	unsigned char carry = 0;
for (int i=15; i>=1; i-=2)
{
	unsigned char carry2 = k[i] >> 7;
	k[i] += k[i] + carry;
	carry = k[i-1] >> 7;
	k[i-1] += k[i-1] + carry2;
}
if (carry)
{
	k[15] ^= 0x87;	
}
}

/*
Computes the OMAC for AES_128
*/
void PICNIC::Encrypt::OMAC(const char * message, const size_t messageLength, char* MACBuffer, const char* key, const size_t keyLength)
{
	const size_t blockLength = 16; //16 bytes for AES_128
	//TODO : L constant somewhere ?
	char L[blockLength] = {0}; 
	char zero[blockLength] = {0};
	crypt(zero, blockLength, L, blockLength, key, keyLength, zero, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_ECB, 0, true); //L = EncK(0);
	
	multByTwo((unsigned char*)L);//L = 2L in GF(2^128)

	size_t newSize = 0;
	unsigned char* newMessage;
	if (messageLength  % blockLength != 0) // if the message size isn't a multiple of blocksize we pad 10^x and we xor with another L
	{
		multByTwo((unsigned char*)L); //We multiply L again by 2
		newSize = (messageLength / blockLength + 1) * blockLength;
		newMessage = (unsigned char*)calloc(newSize,1);
		memcpy(newMessage, message, messageLength);
		newMessage[messageLength] = (unsigned char)0x80; 
	}
	else
	{
		newSize = messageLength;
		newMessage = (unsigned char*)calloc(newSize,1);
		memcpy(newMessage, message, messageLength);
	}
	for (int i =blockLength-1; i >= 0; --i)
		newMessage[newSize-i] ^= L[i]; //We XOR the end of the message with L

	CBCMAC((char*)newMessage, newSize, MACBuffer, key, keyLength, GCRY_CIPHER_AES128);
	free(newMessage);
}

/*
Computes the OMAC_T of the message. OMAC_T is defined in the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
I consists of the OMAC([t]||message), where [t] is the character representation of the integer t. 
*/
void PICNIC::Encrypt::OMAC_T(const char * message, const size_t messageLength, char* MACBuffer, const char* key, const size_t keyLength, const char t)
{
	char* newMessage = (char*)calloc(messageLength + 1, 1);
	newMessage[0] = t;
	memcpy(&newMessage[1], message, messageLength);
	OMAC(message, messageLength, MACBuffer, key, keyLength);
	free(newMessage);
}

/*
Encrypts the message m using the EAX autenticated mode of operation, following the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
*/
bool PICNIC::Encrypt::EAXEncrypt(const char * message, const size_t messageLength, char* authCiphertext, const char* key, const size_t keyLength, const char* nonce, const unsigned int tau)
{
	if(tau > 16)
		return false; // tau has wrong value
	char NMac[16];
	char CMac[16];
	char tag[16] = {0};
	char ciphertext[messageLength];
	OMAC_T(nonce, 16, NMac, key, keyLength, '0');
	crypt(message, messageLength, ciphertext, messageLength, key, keyLength, NMac, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CTR, 0, true);
	OMAC_T(ciphertext, messageLength, CMac, key, keyLength, '2');
	
	for(int i = 0; i < 16 ; ++i)
	{
		tag[i] = NMac[i] ^ CMac[i];
	}
	memcpy(authCiphertext, ciphertext, messageLength);
	memcpy(&authCiphertext[messageLength], tag, tau);
	return true;
}

/*
Decrypts the message m using the EAX autenticated mode of operation, following the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
*/
bool PICNIC::Encrypt::EAXDecrypt(const char * message, const size_t messageLength, char* plaintext, const char* key, const size_t keyLength, const char* nonce, const unsigned int tau)
{
	char NMac[16];
	char CMac[16];
	char tag[16] = {0};
	if (messageLength < tau)
		return false; //message too small
	size_t ciphertextLength = messageLength - tau;
	OMAC_T(nonce, 16, NMac, key, keyLength, '0');
	OMAC_T(message, ciphertextLength, CMac, key, keyLength, '2');

	for(int i = 0; i < 16 ; ++i)
	{
		tag[i] = NMac[i] ^ CMac[i];
	}
	if(memcmp(tag, &message[ciphertextLength], tau) == 0) //tag corresponds
	{
		crypt(message, ciphertextLength, plaintext, ciphertextLength, key, keyLength, NMac, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CTR, 0, false);
		return true; 
	}
	return false; //Authentication failed
}

/*
Encrypts the message m using the EAX autenticated mode of operation, following the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
*/
bool PICNIC::Encrypt::EAXEncrypt(const QByteArray &_plaintext, QByteArray &_ciphertext, const QByteArray &_key, const QByteArray &_nonce){
	char charCipher[_plaintext.size()];
	bool ret = EAXEncrypt(_plaintext.constData(), _plaintext.size(), charCipher, _key.constData(), _key.size(), _nonce.constData(), TAU);
	_ciphertext = QByteArray(charCipher);
	return ret;
	
}

/*
Decrypts the message m using the EAX autenticated mode of operation, following the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
*/
bool PICNIC::Encrypt::EAXDecrypt(const QByteArray &_ciphertext, QByteArray &_plaintext, const QByteArray &_key, const QByteArray &_nonce){
	char charPlain[_ciphertext.size()- TAU];
	bool ret = EAXDecrypt(_ciphertext.constData(), _ciphertext.size(), charPlain, _key.constData(), _key.size(), _nonce.constData(), TAU);
	_plaintext = QByteArray(charPlain, _ciphertext.size()- TAU);
	return ret;
}
