#ifndef SM4_AESNI_X4_H
#define SM4_AESNI_X4_H

#include"sm4.h"

void SM4_AESNI_Encrypt_x4(uint8_t* plaintext, uint8_t* ciphertext, SM4_Key* sm4_key);

void SM4_AESNI_Decrypt_x4(uint8_t* ciphertext, uint8_t* plaintext, SM4_Key* sm4_key);

#endif // !SM4_AESNI_X4_H
