// CPPConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "System\CreateProcessHelper.h"
int _tmain(int argc, _TCHAR* argv[])
{
	System::CreateMProcess(_T("C:\\Program Files (x86)\\Tencent\\weiyundisk\\Bin\\wydrive.exe"));
	return 0;
}

