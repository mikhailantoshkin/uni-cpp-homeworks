// FSReader.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>

using namespace std;



int Offsets[] = { 0x00,0x03, 0x0B,0x0D, 0x0E ,0x10,0x13,0x15,0x16,0x18,0x1A,0x1C,0x20,0x24,0x28,0x30,0x38,0x40,0x44,0x45,0x48,0x50,0x54,0x01FE};

#pragma pack(1)
typedef struct _BIOS_PARAM_BLOCK
{
    BYTE jumpCode[3];
    BYTE oemID[8];
    //BYTE bytesPerSector[2];
    WORD bytesPerSector;
    BYTE sectorPerCluster;
    WORD reservedSectors;
    BYTE always0[3];
    WORD notUsed;
    BYTE mediaDiscr;
    WORD always02;
    WORD sectorperTrack;
    WORD numOfHeaders;
    DWORD hiddenSectors;
    DWORD notUsed2;
    DWORD notused3;
    LONGLONG totalSectors;
    LONGLONG lcnForSMFT;
    LONGLONG lcnForSMFTMirr;
    DWORD clusterPerFileRecordSegm;
    BYTE clusterPerIndexBuff;
    BYTE notUsed4[3];
    LONGLONG volumeSerialNumber;
    DWORD checksum;
    BYTE bootstrap[426];
    WORD endMarker;
} BPB;
#pragma pack()

void PrintBootSectInfo(BPB _bpb) {
    printf("NTFS Disk Information: \n");
    printf("===========================\n");
    printf("Assembly Instruction to jump to Boot code: 0x%X\n",
        _bpb.jumpCode);
    printf("OEM Name: %s\n", _bpb.oemID);
    printf("Bytes per sector: %d\n", _bpb.bytesPerSector);
    printf("Sector per cluster: %d\n", _bpb.sectorPerCluster);
    printf("Reserved Sectors: %d\n", _bpb.reservedSectors);
    printf("Media Descriptor: 0x%X\n", _bpb.mediaDiscr);
    printf("Sectors Per Track: %d\n",_bpb.sectorperTrack);
    printf("Number Of Heads: %d\n", _bpb.numOfHeaders);
    printf("Hidden Sectors: %d\n", _bpb.hiddenSectors);
    printf("Total Sectors: %dl\n",_bpb.totalSectors);
    printf("Logical Cluster Number for the file $MFT: %dl\n", _bpb.lcnForSMFT);
    printf("Logical Cluster Number for the file $MFTMirr: %dl\n",_bpb.lcnForSMFTMirr);
    printf("Clusters Per File Record Segment: %d\n", _bpb.clusterPerFileRecordSegm);
    printf("Clusters Per Index Buffer: %d\n", _bpb.clusterPerIndexBuff);
    printf("Volume Serial Number: %d\n", _bpb.volumeSerialNumber);
    printf("Checksum: %d\n", _bpb.checksum);
    printf("End of Sector Marker: 0x%X\n", _bpb.endMarker);
}

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
        wprintf(L"CreateFile() failed!\n");
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
    }
}
