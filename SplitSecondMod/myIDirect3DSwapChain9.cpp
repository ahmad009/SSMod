//	===========================================================
//            Split Second Velocity - MOD BY Ahmad009
//	===========================================================

#include "StdInc.h"

bool isDeviceResetState = false;
myIDirect3DSwapChain9::myIDirect3DSwapChain9(IDirect3DSwapChain9* pOriginal, IDirect3DDevice9* pDevice)
{
	isDeviceResetState = true;
	m_pIDirect3DSwapChain9 = pOriginal;
	m_pIDirect3DDevice9 = pDevice; 
}

myIDirect3DSwapChain9::~myIDirect3DSwapChain9(void)
{
	m_pIDirect3DSwapChain9 = NULL;
}

HRESULT myIDirect3DSwapChain9::QueryInterface (REFIID riid, void** ppvObj)
{
	*ppvObj = NULL;

	HRESULT hRes = m_pIDirect3DSwapChain9->QueryInterface(riid, ppvObj); 

	if (hRes == NOERROR)
	{
		*ppvObj = this;
	}
	
	return hRes;
}

ULONG myIDirect3DSwapChain9::AddRef(void)
{
	return(m_pIDirect3DSwapChain9->AddRef());
}

ULONG myIDirect3DSwapChain9::Release(void)
{
	extern myIDirect3DSwapChain9*  gl_pmyIDirect3DSwapChain9;
	ULONG count = m_pIDirect3DSwapChain9->Release();
		
    if (count == 0)
	{
		gl_pmyIDirect3DSwapChain9 = NULL;
		delete(this);
	}

	return (count);
}

HRESULT myIDirect3DSwapChain9::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags)
{	

	HRESULT hres = m_pIDirect3DSwapChain9->Present(pSourceRect,pDestRect,hDestWindowOverride,pDirtyRegion,dwFlags);
	return (hres);
}

HRESULT myIDirect3DSwapChain9::GetFrontBufferData(IDirect3DSurface9* pDestSurface)
{
	return(m_pIDirect3DSwapChain9->GetFrontBufferData(pDestSurface));
}

HRESULT myIDirect3DSwapChain9::GetBackBuffer(UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{
	return(m_pIDirect3DSwapChain9->GetBackBuffer(iBackBuffer,Type,ppBackBuffer));
}

HRESULT myIDirect3DSwapChain9::GetRasterStatus(D3DRASTER_STATUS* pRasterStatus)
{
	return(m_pIDirect3DSwapChain9->GetRasterStatus(pRasterStatus));
}

HRESULT myIDirect3DSwapChain9::GetDisplayMode(D3DDISPLAYMODE* pMode)
{
	return(m_pIDirect3DSwapChain9->GetDisplayMode(pMode));
}

HRESULT myIDirect3DSwapChain9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return(m_pIDirect3DSwapChain9->GetDevice(ppDevice));
}

HRESULT myIDirect3DSwapChain9::GetPresentParameters(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return(m_pIDirect3DSwapChain9->GetPresentParameters(pPresentationParameters));
}
LRESULT CALLBACK WndProc_2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return false;
}