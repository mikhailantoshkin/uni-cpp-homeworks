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
    string diskName;
       
    char NameBuffer[MAX_PATH];
    char SysNameBuffer[MAX_PATH];
    DWORD VSNumber;
    DWORD MCLength;
    DWORD FileSF;
    
    // TODO: validation
    while (1){
        cout << "Please specify volume name. Should be like \"C\", \"D\", and so on" << endl;
        diskName = cin.get();
        if (diskName.length() == 1 ) {
            break;
        }
    }

    
    string diskNameFormated = "\\\\.\\" + diskName + ":";
    string forVolumeInf = diskName + ":\\";
    

    if (GetVolumeInformationA(forVolumeInf.c_str(), NameBuffer, sizeof(NameBuffer),
        &VSNumber, &MCLength, &FileSF, SysNameBuffer, sizeof(SysNameBuffer)))
    {
        cout << "Detected file system is " << SysNameBuffer << endl;
    }
    string SysName = SysNameBuffer;

    if (SysName.find("NTFS") == string::npos) {
        cout << "Sorry, but "<< SysName << " is not supported yet!" << endl;
        cout << "Press any key to exit" << endl;
        //needs to be called twice for some reason
        cin.get();
        cin.get();
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
        memcpy(&_bpb, bBootSector, 512);
        PrintBootSectInfo(_bpb);
        cout << "Press Enter to exit";
        getchar();
    }
}
