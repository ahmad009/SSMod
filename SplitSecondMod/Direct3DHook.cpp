//	===========================================================
//            Split Second Velocity - MOD BY Ahmad009
//	===========================================================

#include "StdInc.h"

// global variables
#pragma data_seg (".d3d9_shared")
myIDirect3DSwapChain9*  gl_pmyIDirect3DSwapChain9;
myIDirect3DDevice9*		gl_pmyIDirect3DDevice9;
myIDirect3D9*			gl_pmyIDirect3D9;
HINSTANCE				gl_hOriginalDll;
HINSTANCE				gl_hThisInstance;
#pragma data_seg ()

void LoadOriginalDll(void)
{
    char buffer[MAX_PATH];
    
    // Getting path to system dir and to d3d8.dll
	::GetSystemDirectory(buffer,MAX_PATH);

	// Append dll name
	strcat(buffer,"\\d3d9.dll");
	
	// try to load the system's d3d9.dll, if pointer empty
	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer);

	// Debug
	if (!gl_hOriginalDll)
	{
		MessageBoxA(NULL, "Original d3d9.dll not loaded.", "Error", MB_OK);
		TerminateProcess(GetCurrentProcess(), 0);
	}
}

// exported function faking d3d9.dll's one-and-only export
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right d3d9.dll"
	
	// Hooking IDirect3D Object from Original Library
	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type) GetProcAddress(gl_hOriginalDll, "Direct3DCreate9");
    
    // Debug
	if (!D3DCreate9_fn) 
    {
		MessageBoxA(NULL, "Pointer to original Direct3DCreate9 function not recieved.", "Error", MB_OK);
        TerminateProcess(GetCurrentProcess(), 0);
    }
	
	// request pointer from original dll
	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);
	
	// Create my IDirect3D8 object and store pointer to original object there.
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	gl_pmyIDirect3D9 = new myIDirect3D9(pIDirect3D9_orig);
	
	// Return pointer to hooking Object instead of "real one"
	return (gl_pmyIDirect3D9);
}

extern "C"
{
	__declspec( dllexport ) IDirect3D9 * WINAPI My_Direct3DCreate9(UINT SDKVersion)
	{
		return Direct3DCreate9(SDKVersion);
	}
}