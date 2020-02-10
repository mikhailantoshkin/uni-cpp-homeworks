#pragma once

#ifdef FSREADER_EXPORTS
#define FSREADER_API __declspec(dllexport)
#else
#define FSREADER_API __declspec(dllimport)
#endif

#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>
#include <stdio.h>

int Offsets[] = { 0x00,0x03, 0x0B,0x0D, 0x0E ,0x10,0x13,0x15,0x16,0x18,0x1A,0x1C,0x20,0x24,0x28,0x30,0x38,0x40,0x44,0x45,0x48,0x50,0x54,0x01FE };

#pragma pack(1)
typedef struct
{
    BYTE jumpCode[3];
    BYTE oemID[8];
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
    ULONGLONG totalSectors;
    ULONGLONG lcnForSMFT;
    ULONGLONG lcnForSMFTMirr;
    DWORD clusterPerFileRecordSegm;
    BYTE clusterPerIndexBuff;
    BYTE notUsed4[3];
    ULONGLONG volumeSerialNumber;
    DWORD checksum;
    BYTE bootstrap[426];
    WORD endMarker;
} NTFS_BootRecord;
#pragma pack()

extern "C++" FSREADER_API void PrintBootSectInfo(NTFS_BootRecord _bpb);
extern "C++" FSREADER_API std::string FindFSName(std::string diskName);
extern "C++" FSREADER_API bool fsIsSupported(std::string SysName);
extern "C++" FSREADER_API bool getFsInfo(std::string diskNameFormated, NTFS_BootRecord * _bpb);