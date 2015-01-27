//	===========================================================
//            Split Second Velocity - MOD BY Ahmad009
//	===========================================================

#include "StdInc.h"

static BYTE originalCode[5];
static PBYTE originalEP = 0;

void Main_UnprotectModule(HMODULE hMod)
{
	PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)hMod;
	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD)hMod + header->e_lfanew);
	SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;
	DWORD oldProtect;
	VirtualProtect((LPVOID)hMod, size, PAGE_EXECUTE_READWRITE, &oldProtect);
}

void Main_DoInit()
{
	Sys_RunInit();


	memcpy(originalEP, &originalCode, sizeof(originalCode));

	//MessageBoxA(NULL, "Code has been initialized and EP restored. Safe(?) to attach debugger.", "Notice", MB_OK);
    __asm jmp originalEP
}

void Main_SetSafeInit()
{
	// find the entry point for the executable process, set page access, and replace the EP
	HMODULE hModule = GetModuleHandle(NULL); // passing NULL should be safe even with the loader lock being held (according to ReactOS ldr.c)

	if (hModule)
	{
		PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)hModule;
		PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD)hModule + header->e_lfanew);

		Main_UnprotectModule(hModule);

		// back up original code
		PBYTE ep = (PBYTE)((DWORD)hModule + ntHeader->OptionalHeader.AddressOfEntryPoint);
		memcpy(originalCode, ep, sizeof(originalCode));

		// patch to call our EP
		int newEP = (int)Main_DoInit - ((int)ep + 5);
		ep[0] = 0xE9; // for some reason this doesn't work properly when run under the debugger
		memcpy(&ep[1], &newEP, 4);

		originalEP = ep;
	}
}

bool __stdcall DllMain( HMODULE hModule, DWORD  dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Main_SetSafeInit();
	}

	return true;
}