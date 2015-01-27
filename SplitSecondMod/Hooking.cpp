//	===========================================================
//            Split Second Velocity - MOD BY Ahmad009
//	===========================================================

#include "StdInc.h"
#pragma unmanaged

void CallHook::initialize(DWORD place, void* hookToInstall)
{
	pPlace = (PBYTE)place;
	memcpy(bOriginalCode, pPlace, sizeof(bOriginalCode));
	pOriginal = pPlace + sizeof(bOriginalCode) + *(ptrdiff_t*) (bOriginalCode + 1);
	hook = hookToInstall;
}

void CallHook::installHook(void *hookToInstall)
{
	if(hookToInstall) hook = hookToInstall;
	if(hook) {
		*(ptrdiff_t*) (pPlace + 1) = (PBYTE) hook - pPlace - 5;
	}
}

void CallHook::releaseHook()
{
	memcpy(pPlace + 1, bOriginalCode + 1, sizeof(bOriginalCode) - 1);
}

void StompHook::initialize(DWORD place, void *hookToInstall, BYTE countBytes, bool useJump)
{
        pPlace = (PBYTE)place;
        bCountBytes = countBytes < sizeof(bOriginalCode) ? countBytes : sizeof(bOriginalCode);
        memcpy(bOriginalCode, pPlace, bCountBytes);
        hook = hookToInstall;
        jump = useJump;
}

void StompHook::installHook(void *hookToInstall)
{
        if (hookToInstall) hook = hookToInstall;
        if (hook) {
                memset(pPlace, NOP, bCountBytes);
                pPlace[0] = jump ? JMP_NEAR32 : CALL_NEAR32;
                *(ptrdiff_t*) (pPlace + 1) = (PBYTE) hook - pPlace - 5;
        }
}

void StompHook::releaseHook()
{
        memcpy(pPlace, bOriginalCode, bCountBytes);
}