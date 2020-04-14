#include <iostream>
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

	try
	{
		FileSystem* fs = getDiskFS(diskName.c_str());
		fs->readBootRecord();
	}catch (const char* msg)
	{
		cerr << msg << endl;
	}
	
	cout << "Press Enter to exit";
	cin.get();
	cin.get();
	exit(0);
}
