#pragma once
#include <Windows.h>

namespace System
{
	namespace Integrity_Level
	{
		static TCHAR const * const Low = _T("S-1-16-4096");
		static TCHAR const * const Medium = _T("S-1-16-8192");
		static TCHAR const * const High = _T("S-1-16-12288");
		static TCHAR const * const System = _T("S-1-16-16384");
	}
	BOOL SetIntegrity(HANDLE hToken, LPCTSTR level);
	BOOL CreateMProcess(LPCWSTR lpCmdLine);

	BOOL CreateMProcess(LPCWSTR lpCmdLine);
}