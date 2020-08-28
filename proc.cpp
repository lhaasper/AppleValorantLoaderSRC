#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

DWORD retrieve_pid_via_name(const char *name)
{
	PROCESSENTRY32 entry;
	HANDLE ss;
	DWORD pid = 0;

	entry.dwSize = sizeof(PROCESSENTRY32);
	ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	Process32First(ss, &entry);

	while(Process32Next(ss, &entry))
	{
		if(!_stricmp(entry.szExeFile, name))
			pid = entry.th32ProcessID;
	}

	CloseHandle(ss);

	return pid;
}