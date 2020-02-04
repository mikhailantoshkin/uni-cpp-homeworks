// FSReader.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>
#include "FSReader.h"

using namespace std;



int main()
{

    BYTE bBootSector[512];
    memset(bBootSector, 0, 512);
    DWORD dwBytesRead(0);
    BPB _bpb;
    LPWSTR lpDrive;
    // {0} ~ ZeroMemory()
    PNTFS_VOLUME_DATA_BUFFER ntfsVolData = { 0 };
    // NTFS_EXTENDED_VOLUME_DATA versionMajMin = {0};
    BOOL bDioControl = FALSE;
    DWORD dwWritten = 0;
    HANDLE hDisk = CreateFileA("\\\\.\\C:",
        GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, 0, NULL);
    if (hDisk == INVALID_HANDLE_VALUE)
    {
        wprintf(L"CreateFile() failed! Proboly run as administrator\n");
        wprintf(L" %u \n", GetLastError());
        if (CloseHandle(hDisk) != 0)
            wprintf(L"hVolume handle was closed successfully!\n");
        else
        {
            wprintf(L"Failed to close hVolume handle!\n");
        }
        exit(1);
    }
    else
        wprintf(L"CreateFile() is pretty fine!\n");
    if (!ReadFile(hDisk, bBootSector, 512, &dwBytesRead, NULL))
    {
        printf("Error in reading floppy disk\n");
    }
    else
    {
        // Print floppy information on Console.
        CloseHandle(hDisk);
     /*   BYTE temp;
        for (unsigned int a = 1; a < sizeof(Offsets) / sizeof(Offsets[0]); a = a + 1) {
            int revIndx  = Offsets[a - 1];
            int arrIndx = Offsets[a]-1;
            int section_len = arrIndx - arrIndx;
            while (revIndx < arrIndx) {
                temp = bBootSector[revIndx];
                bBootSector[revIndx] = bBootSector[arrIndx];
                bBootSector[arrIndx] = temp;

                revIndx++;
                arrIndx--;
                }

            BYTE* start = &bBootSector[Offsets[a - 1]];
            BYTE* end = &bBootSector[Offsets[a]-1];
            
        }*/
        memcpy(&_bpb, bBootSector, 512);
        
        PrintBootSectInfo(_bpb);
        cout << "Press any key to exit";
        getchar();
    }
}
