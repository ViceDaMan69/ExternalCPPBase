// SuperTux2 Trainer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include "proc.h"


int main()
{

    DWORD ProcID = GetProcID(L"supertux2.exe");

    uintptr_t moduleBase = GetModuleBaseAddress(ProcID, L"supertux2.exe");

    HANDLE hProcess = 0;

    uintptr_t dynamicPtrBaseAddr = moduleBase + 0x00256AA8;

    std::vector<unsigned int> coinOffsets = {0xF8, 0x20, 0x0};



    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcID);
        
    std::cout << "[!] Welcome to SuperTux2 Trainer\n";
    std::cout << " ";
    std::cout << "[?] Dynamic Base Address: " << "0x" << std::hex << dynamicPtrBaseAddr << "\n";
    std::cout << " ";
    uintptr_t coinAddr = FinDMAAddy(hProcess, dynamicPtrBaseAddr, coinOffsets);

    int newCoins = 9999;

    while (true)
    {
        Sleep(1000);
        WriteProcessMemory(hProcess, (BYTE*)coinAddr, &newCoins, sizeof(newCoins), nullptr);
        std::cout << "[!] Writing to Memory Successful" << "\n";
        std::cout << " " << "\n";
    }

}

