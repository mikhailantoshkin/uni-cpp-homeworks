#include "pch.h"
#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>
#include "FSReader.h"
#include <string>

void PrintBootSectInfo(NTFS_BootRecord _bpb) {
    printf("NTFS Disk Information: \n");
    printf("===========================\n");
    printf("Assembly Instruction to jump to Boot code: 0x%X\n",
        _bpb.jumpCode);
    printf("OEM Name: %s\n", _bpb.oemID);
    printf("Bytes per sector: %d\n", _bpb.bytesPerSector);
    printf("Sector per cluster: %d\n", 0x01 << _bpb.sectorPerCluster);
    printf("Reserved Sectors: %d\n", _bpb.reservedSectors);
    printf("Media Descriptor: 0x%X\n", _bpb.mediaDiscr);
    printf("Sectors Per Track: %d\n", _bpb.sectorperTrack);
    printf("Number Of Heads: %d\n", _bpb.numOfHeaders);
    printf("Hidden Sectors: %d\n", _bpb.hiddenSectors);
    printf("Total Sectors: %dl\n", _bpb.totalSectors);
    printf("Logical Cluster Number for the file $MFT: %dl\n", _bpb.lcnForSMFT);
    printf("Logical Cluster Number for the file $MFTMirr: %dl\n", _bpb.lcnForSMFTMirr);
    printf("Clusters Per File Record Segment: %d\n", _bpb.clusterPerFileRecordSegm);
    printf("Clusters Per Index Buffer: %d\n", _bpb.clusterPerIndexBuff);
    printf("Volume Serial Number: %d\n", _bpb.volumeSerialNumber);
    printf("Checksum: %d\n", _bpb.checksum);
    printf("End of Sector Marker: 0x%X\n", _bpb.endMarker);
}

std::string FindFSName(std::string diskName) {
    char NameBuffer[MAX_PATH];
    char _SysBuffer[MAX_PATH];
    DWORD VSNumber;
    DWORD MCLength;
    DWORD FileSF;

    std::string forVolumeInf = diskName + ":\\";


    if (GetVolumeInformationA(forVolumeInf.c_str(), NameBuffer, sizeof(NameBuffer),
        &VSNumber, &MCLength, &FileSF, _SysBuffer, sizeof(_SysBuffer)))
    {
        std::cout << "Detected file system is " << _SysBuffer << std::endl << std::endl;
        std::string SysName = _SysBuffer;

        return SysName;
    }
    
    return std::string("");
}