#include "stdafx.h"

#include "CreateProcessHelper.h"
#include <Sddl.h>

namespace System
{
	BOOL SetIntegrity(HANDLE hToken, LPCTSTR level)
	{
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
		return TRUE;
	}
}

