#include <stdio.h>
#include <windows.h>

void ShowDriveType(char DriveLetter);
void ShowVolumeInfo(char DriveLetter);
void ShowClustersInfo(char DriveLetter);
void ShowFreeSpaceInfo(char DriveLetter);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    DWORD drives = GetLogicalDrives();

    printf("Drives list:\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < 26; i++)
    {
        char DriveLetter = i + 65;
        if (drives & (1 << i))
        {
            printf("Detected %c drive\n", DriveLetter);
            ShowDriveType(DriveLetter);
            ShowVolumeInfo(DriveLetter);
            ShowClustersInfo(DriveLetter);
            ShowFreeSpaceInfo(DriveLetter);
            printf("----------------------------------------\n");
        }
    }

    return 0;
}

void ShowDriveType(char DriveLetter)
{
    // Showing drive type
    char PathToDriveRoot[] = "\0:\\";
    PathToDriveRoot[0] = DriveLetter;

    UINT DriveType = GetDriveType(PathToDriveRoot);
    char DriveTypeStr[20];
    switch (DriveType)
    {
    case 0:
        strcpy(DriveTypeStr, "unknown");
        break;

    case 1:
        strcpy(DriveTypeStr, "invalid root dir");
        break;

    case 2:
        strcpy(DriveTypeStr, "removable drive");
        break;

    case 3:
        strcpy(DriveTypeStr, "fixed drive");
        break;

    case 4:
        strcpy(DriveTypeStr, "remote drive");
        break;

    case 5:
        strcpy(DriveTypeStr, "optical drive");
        break;

    case 6:
        strcpy(DriveTypeStr, "ramdisk");
        break;

    default:
        strcpy(DriveTypeStr, "not set");
        break;
    }
    printf("- Drive type: %s\n", DriveTypeStr);
    return;
}

void ShowVolumeInfo(char DriveLetter)
{
    // Showing volume info
    char PathToDriveRoot[] = "\0:\\";
    PathToDriveRoot[0] = DriveLetter;

    char NameBuf[MAX_PATH];
    char SysNameBuf[MAX_PATH];
    DWORD VSNumber, MCLength, FileSF;

    if (GetVolumeInformation(PathToDriveRoot, NameBuf, sizeof(NameBuf), &VSNumber, &MCLength, &FileSF, SysNameBuf, sizeof(SysNameBuf)))
    {
        printf("- FS INFO\n");
        printf("  - File system: %s\n", SysNameBuf);
        printf("  - Partition label: %s\n", NameBuf);
    }

    return;
}

void ShowClustersInfo(char DriveLetter)
{
    char PathToDriveRoot[] = "\0:\\";
    PathToDriveRoot[0] = DriveLetter;

    DWORD SecPerCluster, BytesPerSector, NumberOfFreeClusters, TotalClusters;
    if (GetDiskFreeSpace(PathToDriveRoot, &SecPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalClusters))
    {
        printf("- SECTORS/CLUSTERS INFO\n");
        printf("  - Sectors per cluster: %d\n", SecPerCluster);
        printf("  - Bytes per sector: %d\n", BytesPerSector);
        printf("  - Total clusters: %d\n", TotalClusters);
    }

    return;
}

void ShowFreeSpaceInfo(char DriveLetter)
{
    char PathToDriveRoot[] = "\0:\\";
    PathToDriveRoot[0] = DriveLetter;

    ULARGE_INTEGER CallerFreeBytesAvailable, TotalBytes, TotalFreeBytes;

    if (GetDiskFreeSpaceEx(PathToDriveRoot, &CallerFreeBytesAvailable, &TotalBytes, &TotalFreeBytes))
    {
        printf("- FREE DRIVE SPACE INFO\n");
        printf("  - Total space on drive: %llu\n", TotalBytes);
        printf("  - Total free space on drive: %llu\n", TotalFreeBytes);
        printf("  - Space available for this thread: %llu\n", CallerFreeBytesAvailable);
    }
    return;
}