#include <stdio.h>
#include <windows.h>

void displayInfo(PROCESS_INFORMATION processInfo)
{
    printf("Process ID: %d\n", processInfo.dwProcessId);
    printf("Thread ID: %d\n", processInfo.dwThreadId);
    printf("Process handle: 0x%X\n", processInfo.hProcess);
    printf("Thread handle: 0x%X\n", processInfo.hThread);
    printf("---------------------\n");
}

int main()
{
    STARTUPINFO info = {sizeof(info)};
    PROCESS_INFORMATION processInfo[3];
    printf("---------------------\n");
    if (CreateProcess(NULL, "notepad.exe", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo[0]))
    {
        displayInfo(processInfo[0]);
        Sleep(1500);
    }
    if (CreateProcess(NULL, "C:\\Utilities\\WinBox\\winbox64.exe", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo[1]))
    {
        displayInfo(processInfo[1]);
        Sleep(1500);
    }
    if (CreateProcess(NULL, "C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo[2]))
    {
        displayInfo(processInfo[2]);
        Sleep(3000); 
    }

    TerminateProcess(processInfo[2].hProcess, 0);
    Sleep(500);
    TerminateProcess(processInfo[1].hProcess, 0);
    Sleep(500);
    TerminateProcess(processInfo[0].hProcess, 0);
    Sleep(500);

    return 0;
}