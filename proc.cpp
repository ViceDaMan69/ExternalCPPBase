#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include "proc.h"

DWORD GetProcID(const wchar_t* procName)
{
	DWORD ProcID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{

			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					ProcID = procEntry.th32ProcessID;
					break;
				}
			}

			while (Process32Next(hSnap, &procEntry));


		}
	}
	CloseHandle(hSnap);

	return ProcID;
}

uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;

		modEntry.dwSize = sizeof(modEntry);

		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName));
				{
					modBaseAddr = (uintptr_t )modEntry.modBaseAddr;
					break;
				}

			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);

	return modBaseAddr;

}

uintptr_t FinDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;

	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;

}