#include "pch.h"
#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>
#include "FSReader.h"
#include <string>


FileSystem* getDiskFS(const char* diskName) {
	char NameBuffer[MAX_PATH];
	char _SysBuffer[MAX_PATH];
	DWORD VSNumber;
	DWORD MCLength;
	DWORD FileSF;

	std::string _diskName = diskName;
	std::string forVolumeInf = _diskName + ":\\";
	std::string diskNameFormated = "\\\\.\\" + _diskName + ":";


	if (GetVolumeInformationA(forVolumeInf.c_str(), NameBuffer, sizeof(NameBuffer),
		&VSNumber, &MCLength, &FileSF, _SysBuffer, sizeof(_SysBuffer)))
	{
		std::cout << "Detected file system is " << _SysBuffer << std::endl << std::endl;
		std::string SysName = _SysBuffer;
		if (SysName.find("NTFS") != std::string::npos)
		{
			return new NTFSFileSystem(_diskName.c_str());
		}
		else
		{
			throw "This Fs in not supported yet";
		}



	}
	else throw "Unable to get the info about specified disk, are you sure you are not trying to shoot yourself in the knee?";

}
