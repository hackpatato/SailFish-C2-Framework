#include "base64Xor.h"
#include <stddef.h>
#include <stdlib.h>

static const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// ı hate crypto things
void Xorcipher(char *data, size_t dataLen, char key) {
    for (size_t i = 0; i < dataLen; i++) {
        data[i] = data[i] ^ key;
    }
}
char* base64Encode(const unsigned char *data, size_t inputLen) {
    size_t outputLen = 4 * ((inputLen + 2) / 3);
    char *encodedData =(char *)malloc(outputLen + 1);
    if (encodedData == NULL) return NULL;

    size_t i, j ;
    for (i = 0, j = 0; i < inputLen;) {
        unsigned int octet_a = i < inputLen ? data[i++] : 0;
        unsigned int octet_b = i < inputLen ? data[i++] : 0;
        unsigned int octet_c = i < inputLen ? data[i++] : 0;
        unsigned int triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encodedData[j++] = base64Table[(triple >> 18) & 0x3F];
        encodedData[j++] = base64Table[(triple >> 12) & 0x3F];
        encodedData[j++] = base64Table[(triple >> 6) & 0x3F];
        encodedData[j++] = base64Table[triple & 0x3F];
    }
    int mod = inputLen % 3;
    if (mod == 1) {
        encodedData[j - 1] = '=';
        encodedData[j - 2] = '=';
    } else if (mod == 2) {
        encodedData[j - 1] = '=';
    }
    encodedData[j] = '\0';
    return encodedData;
}