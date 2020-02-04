#include "pch.h"
#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>
#include "FSReader.h"

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