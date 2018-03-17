#pragma once
#include <windows.h>


// include the Direct3D Library file
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#ifdef _WIN64

#include "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\um\\d3d11.h"
#pragma comment (lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.16299.0\\um\\x64\\d3d11.lib")

#else// _WIN64

#include <D3D11.h>
#pragma comment (lib, "d3d11.lib")

#endif



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