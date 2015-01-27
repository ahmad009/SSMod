//	===========================================================
//            Split Second Velocity - MOD BY Ahmad009
//	===========================================================

#include "StdInc.h"

void Sys_RunInit()
{
	//DLC Cars Unlock
	*(BYTE*)0x4734F0 = 1;
	*(BYTE*)0x473501 = 1;

	//Version String stuff
	*(DWORD*)0xCF5004 = (DWORD)"Split Second Mod v1-beta";
}

