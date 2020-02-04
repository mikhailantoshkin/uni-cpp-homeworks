﻿// FSReader.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
    //BPB _bpb;
    string diskName;
       

    
    // TODO: validation
    while (1){
        cout << "Please specify volume name. Should be like \"C\", \"D\", and so on" << endl;
        diskName = cin.get();
        if (diskName.length() == 1 ) {
            break;
        }
    }

    
    string diskNameFormated = "\\\\.\\" + diskName + ":";

    
    string SysName = FindFSName(diskName);
    if (SysName.find("NTFS") == std::string::npos) {
        cout << "Sorry, " << SysName << " is not supported yet!" << endl;
        getchar();
        exit(0);
    }


    HANDLE hDisk = CreateFileA(diskNameFormated.c_str(),
        GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, 0, NULL);
    if (hDisk == INVALID_HANDLE_VALUE)
    {
        wprintf(L"CreateFile() failed! You'll rrobably need to run the app as administrator\n");
        wprintf(L" %u \n", GetLastError());
        if (CloseHandle(hDisk) != 0)
            wprintf(L"hVolume handle was closed successfully!\n");
        else
        {
            wprintf(L"Failed to close hVolume handle!\n");
        }
        exit(1);
    }
     
    if (!ReadFile(hDisk, bBootSector, 512, &dwBytesRead, NULL))
    {
        printf("Error in reading the disk\n");
    }
    else
    {
        CloseHandle(hDisk);
        //memcpy(&_bpb, bBootSector, 512);
        NTFS_BootRecord *_bpb = reinterpret_cast<NTFS_BootRecord*>(bBootSector);
        PrintBootSectInfo(*_bpb);
        cout << "Press Enter to exit";
        cin.get();
        exit(0);
    }
}
