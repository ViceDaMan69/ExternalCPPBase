#pragma once
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcID(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName);

uintptr_t FinDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
