// GetMyUacLevel.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

BOOL IsAdmin(void)
{
	HANDLE                   hAccessToken;
	BYTE                     *InfoBuffer;
	PTOKEN_GROUPS            ptgGroups;
	DWORD                    dwInfoBufferSize;
	PSID                     psidAdministrators;
	SID_IDENTIFIER_AUTHORITY siaNtAuthority = SECURITY_NT_AUTHORITY;
	UINT                     i;
	BOOL                     bRet = FALSE;

	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hAccessToken))
		goto cleanup;

	InfoBuffer = new BYTE[1024];
	if(!InfoBuffer)
		goto cleanup;

	bRet = GetTokenInformation(hAccessToken,
		TokenGroups,
		InfoBuffer,
		1024,
		&dwInfoBufferSize);

	CloseHandle( hAccessToken );

	if(!bRet)
		goto cleanup;

	if(!AllocateAndInitializeSid(&siaNtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0,0,0,0,0,0,
		&psidAdministrators))
		goto cleanup;

	bRet = FALSE;

	ptgGroups = (PTOKEN_GROUPS)InfoBuffer;

	for(i=0;i<ptgGroups->GroupCount;i++)
	{
		if(EqualSid(psidAdministrators,ptgGroups->Groups[i].Sid))
		{
			bRet = TRUE;
			if (ptgGroups->Groups[i].Attributes>>2&1)
			{
				MessageBoxA(0,"TRUE","UAC",0);				
			}
			else
			{
				MessageBoxA(0,"FALSE","UAC",0);				
			}
			break;
		}
	}

	FreeSid(psidAdministrators);

cleanup:

	if (InfoBuffer)
		delete []InfoBuffer;

	return bRet;
}


int _tmain(int argc, _TCHAR* argv[])
{

	if (IsAdmin())
		MessageBoxA(0,"TRUE","IsAdmin",0);
	else
		MessageBoxA(0,"FALSE","IsAdmin",0);


	system("pause");
	return 0;
}

