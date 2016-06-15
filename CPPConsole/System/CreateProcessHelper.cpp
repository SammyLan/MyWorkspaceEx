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

	BOOL GetRemoveAdminToken(CAccessToken & hToken)
	{
		if (hToken.GetHandle() != NULL)
		{
			CloseHandle(hToken.Detach());
		}

		//获取当前进程的Token
		CAccessToken hProcessToken;
		hProcessToken.GetProcessToken(TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE |
			TOKEN_QUERY | TOKEN_ADJUST_DEFAULT);

		//PSID可变长度的数据结构
		BYTE sidBuffer[256] = { 0 };
		PSID pAdminSID = (PSID)sidBuffer;
		SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;
		if (!AllocateAndInitializeSid(&SIDAuth, 2,
			SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0, &pAdminSID))
		{
			printf("AllocateAndInitializeSid Error%u\n", GetLastError());
			return FALSE;
		}

		SID_AND_ATTRIBUTES SidToDisable[1] = { 0 };
		SidToDisable[0].Sid = pAdminSID;
		SidToDisable[0].Attributes = 0;

		HANDLE hNewToken = NULL;
		if (!CreateRestrictedToken(hProcessToken.GetHandle(),
			DISABLE_MAX_PRIVILEGE,
			1, SidToDisable,
			0, NULL,0, NULL,
			&hNewToken))
		{
			printf("CreateRestrictedToken failed(%lu)\n", GetLastError());
			return FALSE;
		}
		hToken.Attach(hNewToken);
		return hNewToken != NULL;
	}

	BOOL CreateMProcess(LPCWSTR lpCmdLine)
	{
		CAccessToken hToken;
		GetRemoveAdminToken(hToken);
		SetIntegrity(hToken.GetHandle(), Integrity_Level::Medium);

		STARTUPINFO  si;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);

		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(pi));		
		hToken.CreateProcessAsUser(lpCmdLine, NULL, &pi, &si, CREATE_UNICODE_ENVIRONMENT, false, NULL, NULL, TRUE);
		return TRUE;
	}
}

