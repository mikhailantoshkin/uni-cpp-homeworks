﻿#include "pch.h"
#include "FSReader.h"
#include <string>


void NTFSFileSystem::readBootRecord()
{
	//TODO: handle errors in the way, that make sense
	BYTE bBootSector[512];
	memset(bBootSector, 0, 512);
	DWORD dwBytesRead(0);
	std::string normalizedDiskName = "\\\\.\\" + diskName + ":";

	HANDLE hDisk = CreateFileA(normalizedDiskName.c_str(),
		GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hDisk == INVALID_HANDLE_VALUE)
	{
		wprintf(L"CreateFile() failed! You'll probably need to run the app as administrator\n");
		wprintf(L" %u \n", GetLastError());
		if (CloseHandle(hDisk) != 0)
			wprintf(L"hVolume handle was closed successfully!\n");
		else
		{
			wprintf(L"Failed to close hVolume handle!\n");
		}
		throw "CreateFile() failed! You'll probably need to run the app as administrator\n";
	}

	if (!ReadFile(hDisk, bBootSector, 512, &dwBytesRead, NULL))
	{
		printf("Error in reading the disk\n");
		CloseHandle(hDisk);
		throw "Error in reading the disk\n";
	}

	CloseHandle(hDisk);
	bootRecord = *reinterpret_cast<NTFS_BootRecord*>(bBootSector);
	printf("NTFS Disk Information: \n");
	printf("===========================\n");
	printf("Assembly Instruction to jump to Boot code: 0x%X\n",
		bootRecord.jumpCode);
	printf("OEM Name: %s\n", bootRecord.oemID);
	printf("Bytes per sector: %d\n", bootRecord.bytesPerSector);
	printf("Sector per cluster: %d\n", 0x01 << bootRecord.sectorPerCluster);
	printf("Reserved Sectors: %d\n", bootRecord.reservedSectors);
	printf("Media Descriptor: 0x%X\n", bootRecord.mediaDiscr);
	printf("Sectors Per Track: %d\n", bootRecord.sectorperTrack);
	printf("Number Of Heads: %d\n", bootRecord.numOfHeaders);
	printf("Hidden Sectors: %d\n", bootRecord.hiddenSectors);
	printf("Total Sectors: %dll\n", bootRecord.totalSectors);
	printf("Logical Cluster Number for the file $MFT: %dl\n", bootRecord.lcnForSMFT);
	printf("Logical Cluster Number for the file $MFTMirr: %dl\n", bootRecord.lcnForSMFTMirr);
	printf("Clusters Per File Record Segment: %d\n", bootRecord.clusterPerFileRecordSegm);
	printf("Clusters Per Index Buffer: %d\n", bootRecord.clusterPerIndexBuff);
	printf("Volume Serial Number: %dl\n", bootRecord.volumeSerialNumber);
	printf("Checksum: %d\n", bootRecord.checksum);
	printf("End of Sector Marker: 0x%X\n", bootRecord.endMarker);
	
}

