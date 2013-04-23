#ifndef PICNIC_ENCRYPT_H
#define PICNIC_ENCRYPT_H
#include <gcrypt.h>
#include <QByteArray>
#include <iostream>
namespace PICNIC
{
class Encrypt
{
private:

/*
Encrypts or decrypts (depending on the last boolean) the input buffer over inputLength bytes and stores the result in outputBuffer. 
The encryption algorithm is "algo" using the mode of operation "mode". 
*/
static bool crypt(const char * inputBuffer, const size_t inputLength,  char * outputBuffer, const size_t outputLength,  const char * key, const size_t keyLength,  const char * iniVector, const int algo, const int mode, const unsigned int flags, bool encrypt);

/*
Computes the CBCMAC of the message using encryption algorithm "algo".
*/
static void CBCMAC(const char * message, const size_t messageLength, char * MACBuffer, const char * key, const size_t keyLength, const int algo);

/*
Multiplies by two a 128 bit word in GF(2^128)
*/
static void multByTwo(unsigned char k[]);

/*
Computes the OMAC for AES_128
*/
static void OMAC(const char * message, const size_t messageLength, char* MACBuffer, const char* key, const size_t keyLength);

/*
Computes the OMAC_T of the message. OMAC_T is defined in the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
I consists of the OMAC([t]||message), where [t] is the character representation of the integer t. 
*/
static void OMAC_T(const char * message, const size_t messageLength, char* MACBuffer, const char* key, const size_t keyLength, const char t);

/*
Encrypts the message m using the EAX autenticated mode of operation, following the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
*/ 
static bool EAXEncrypt(const char * message, const size_t messageLength, char* authCiphertext, const char* key, const size_t keyLength, const char* nonce, const unsigned int tau);

/*
Decrypts the message m using the EAX autenticated mode of operation, following the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
*/
static bool EAXDecrypt(const char * message, const size_t messageLength, char* plaintext, const char* key, const size_t keyLength, const char* nonce, const unsigned int tau);
public:
/*
Encrypts the message m using the EAX autenticated mode of operation, following the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
*/
static bool EAXEncrypt(const QByteArray& _plaintext, QByteArray& _ciphertext, const QByteArray& _key, const QByteArray& _nonce);

/*
Decrypts the message m using the EAX autenticated mode of operation, following the original EAX paper <http://www.cs.ucdavis.edu/~rogaway/papers/eax.pdf>.
*/
static bool EAXDecrypt(const QByteArray& _ciphertext, QByteArray& _plaintext, const QByteArray& _key, const QByteArray& _nonce); 
};
} //namespace PICNIC

#endif
