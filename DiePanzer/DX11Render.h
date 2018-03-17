#pragma once
#include <windows.h>
#include "D3D.h"

class DX11Renderer
{
public:
	DX11Renderer(HWND hostwindow);
	~DX11Renderer();

	void RenderFrame();
	bool Initialize(unsigned int width, unsigned int height);
	void Shutdown();

private:
	IDXGISwapChain *swapchain;             
	ID3D11Device *dev;                     
	ID3D11DeviceContext *devcon;          
	ID3D11RenderTargetView *backbuffer;    
	HWND m_Window;
};