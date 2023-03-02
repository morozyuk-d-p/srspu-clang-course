#include <windows.h>
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    DWORD drives = GetLogicalDrives();
    printf("Drives list:\n");
    
    for (int i = 0; i < 26; i++)
    {
        if (drives & (1 << i)) {
            printf("%c\n", i + 65);
        }
    }
    
    return 0;
}