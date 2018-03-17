#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	m_Renderer = 0;
	m_Window = 0;
	m_windowhandle = 0;
}

Graphics::~Graphics()
{
}

void Graphics::Frame()
{
	m_Renderer->RenderFrame();
}

bool Graphics::Initialize()
{
	m_Window = new Window(window_width, window_height);
	
	if (!m_Window->Setup(m_windowhandle))
	{
		MessageBoxW(NULL, L"Failed to Create Window", L"Panzerspiel", MB_OK | MB_TOPMOST);
		return false;
	}		

	m_Renderer = new DX11Renderer(m_windowhandle);
	//TODO inno2: set Window size to something > 800x600, so the ClientSize is exactly 800x600
	if (!m_Renderer->Initialize(m_Window->GetClientSizeWidth(), m_Window->GetClientSizeHeight()))
	{
		MessageBoxW(NULL, L"Failed to Create DX11", L"Panzerspiel", MB_OK | MB_TOPMOST);
		return false;
	}

	return true;
}

HWND Graphics::GetWindowHandle()
{
	return m_windowhandle;
}
