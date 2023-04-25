#include <windows.h>
#include <stdio.h>

void displayFileInfo(LPWIN32_FIND_DATAA data);

int main()
{
    printf("%-30s", "Name");
    printf("%-13s", "Kind");
    printf("%-10s", "Type");
    printf("%-12s", "Size");
    printf("%-10s", "Date");
    printf("\n------------------------------------------------------------------------------------\n");

    LPCSTR filename = ".\\*";
    LPWIN32_FIND_DATAA data;

    HANDLE find = FindFirstFileA(filename, data);
    do
    {
        displayFileInfo(data);
    } while (FindNextFileA(find, data));

    FindClose(find);
    return 0;
}

void displayFileInfo(LPWIN32_FIND_DATAA data)
{
    printf("%-30s", data->cFileName);

    if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        printf("%-13s", "directory");
    }
    else
    {
        printf("%-13s", "file");
    }

    HANDLE file = CreateFile(data->cFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    GetFileType(file);
    switch (GetFileType(file))
    {
    case FILE_TYPE_CHAR:
        printf("%-10s", "character");
        break;

    case FILE_TYPE_DISK:
        printf("%-10s", "disk");
        break;

    case FILE_TYPE_PIPE:
        printf("%-10s", "socket");
        break;

    case FILE_TYPE_REMOTE:
        printf("%-10s", "remote");
        break;

    case FILE_TYPE_UNKNOWN:
        printf("%-10s", "unknown");
        break;

    default:
        break;
    }

    DWORD fileSize;
    fileSize = GetFileSize(file, data->nFileSizeHigh);
    if (fileSize != 4294967295) {
        printf("%-12d", fileSize);
    } else {
        printf("%-12s", "-");
    }

    FILETIME time = data->ftLastWriteTime;
    SYSTEMTIME systime;
    
    if (FileTimeToSystemTime(&time, &systime))
    {
        printf("%02d.%02d.%04d %02d:%02d:%02d", systime.wDay, systime.wMonth, systime.wYear, systime.wHour, systime.wMinute, systime.wSecond);
    }
    
    printf("\n");
    return;
}