﻿#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>
#include "FSReader.h"


using namespace std;


int main()
{
	string diskName;

	// TODO: validation
	while (1)
	{
		cout << "Please specify volume name. Should be like \"C\", \"D\", and so on" << endl;
		diskName = cin.get();
		if (diskName.length() == 1)
		{
			break;
		}
	}


	string diskNameFormated = "\\\\.\\" + diskName + ":";

	string SysName = FindFSName(diskName);
	if (!fsIsSupported(SysName))
	{
		cout << "Sorry, " << SysName << " is not supported yet!" << endl;
		cin.get();
		cin.get();
		exit(0);
	}


	NTFS_BootRecord _bpb;
	if (getFsInfo(diskNameFormated, &_bpb))
	{
		PrintBootSectInfo(_bpb);
	}
	cout << "Press Enter to exit";
	cin.get();
	cin.get();
	exit(0);
}
