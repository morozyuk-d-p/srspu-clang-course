#include <windows.h>
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char num = 0;
    DWORD drives = GetLogicalDrives();
    printf("Drives list:\n");
    do
    {
        num++;
        if (drives % 2 == 1) {
            printf("%c\n", num + 64);
        }
        drives = drives / 2;
    } while (drives != 0);
    return 0;
}