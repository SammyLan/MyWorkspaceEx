#include "stdafx.h"
#include "CreateProcessHelper.h"
#include <Sddl.h>
#include <atlsecurity.h>

namespace System
{
	BOOL SetIntegrity(HANDLE hToken, LPCTSTR level)
	{
		//https://support.microsoft.com/en-hk/kb/243330
		//http://forcemz.net/container/2015/06/12/AppContainer/
		PSID pIntegritySid = nullptr;
		BOOL bRet = ConvertStringSidToSid(level, &pIntegritySid);
		if (bRet)
		{
			TOKEN_MANDATORY_LABEL level = { 0 };
			level.Label.Attributes = SE_GROUP_INTEGRITY;
			level.Label.Sid = pIntegritySid;
			bRet = SetTokenInformation(hToken, TokenIntegrityLevel, &level, sizeof(TOKEN_MANDATORY_LABEL) + GetLengthSid(pIntegritySid));			
		}
		if (pIntegritySid != nullptr)
		{
			LocalFree(pIntegritySid);
		}
		return bRet;
	}

	BOOL CreateMProcess(LPCWSTR lpCmdLine)
	{
		CAccessToken hProcess;
		hProcess.GetProcessToken(TOKEN_DUPLICATE);
		CAccessToken hDupToken;
		HANDLE hTmp;
		DuplicateTokenEx(hProcess.GetHandle(), MAXIMUM_ALLOWED, 0, SecurityAnonymous, TokenPrimary,&hTmp);
		hDupToken.Attach(hTmp);

		SetIntegrity(hTmp, Integrity_Level::Medium);

		STARTUPINFO  si;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);

		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(pi));
		hDupToken.CreateProcessAsUser(lpCmdLine, NULL, &pi, &si, CREATE_UNICODE_ENVIRONMENT, false, NULL, NULL, TRUE);
		return TRUE;
	}
}

