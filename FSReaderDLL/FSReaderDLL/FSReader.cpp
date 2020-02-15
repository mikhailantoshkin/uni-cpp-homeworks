#include "pch.h"
#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>
#include "FSReader.h"
#include <string>

void PrintBootSectInfo(NTFS_BootRecord _bpb)
{
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
	printf("Total Sectors: %dll\n", _bpb.totalSectors);
	printf("Logical Cluster Number for the file $MFT: %dl\n", _bpb.lcnForSMFT);
	printf("Logical Cluster Number for the file $MFTMirr: %dl\n", _bpb.lcnForSMFTMirr);
	printf("Clusters Per File Record Segment: %d\n", _bpb.clusterPerFileRecordSegm);
	printf("Clusters Per Index Buffer: %d\n", _bpb.clusterPerIndexBuff);
	printf("Volume Serial Number: %dl\n", _bpb.volumeSerialNumber);
	printf("Checksum: %d\n", _bpb.checksum);
	printf("End of Sector Marker: 0x%X\n", _bpb.endMarker);
}

std::string FindFSName(std::string diskName)
{
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

bool fsIsSupported(std::string SysName)
{
	if (SysName.find("NTFS") == std::string::npos)
	{
		return false;
	}
	return true;
}

bool getFsInfo(std::string diskNameFormated, NTFS_BootRecord* _bpb)
{
	//TODO: handle errors in the way, that make sense
	BYTE bBootSector[512];
	memset(bBootSector, 0, 512);
	DWORD dwBytesRead(0);

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
		return false;
	}

	if (!ReadFile(hDisk, bBootSector, 512, &dwBytesRead, NULL))
	{
		printf("Error in reading the disk\n");
		CloseHandle(hDisk);
		return false;
	}

	CloseHandle(hDisk);
	*_bpb = *reinterpret_cast<NTFS_BootRecord*>(bBootSector);
	return true;
}
