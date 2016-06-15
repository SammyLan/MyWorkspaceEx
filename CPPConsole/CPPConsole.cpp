// CPPConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "System\CreateProcessHelper.h"
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 2)
	{
		System::CreateMProcess(argv[1]);
	}
	return 0;
}

