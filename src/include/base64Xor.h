#ifndef BASE64XOR_H
#define BASE64XOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void XorCipher(char *data, size_t dataLen, char key);

char* Base64Encode(const unsigned char *data, size_t inputLen);

#endif