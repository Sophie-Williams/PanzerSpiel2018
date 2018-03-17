#pragma once
#include "Singleton.h"
#include "DX11Render.h"
#include "Window.h"

class Graphics : public Singleton<Graphics>
{
private:
	const unsigned int window_width  = 800;
	const unsigned int window_height = 600;

public:
	Graphics();
	~Graphics();

	void Frame();
	bool Initialize();
	HWND GetWindowHandle();

private:
	HWND m_windowhandle;
	DX11Renderer* m_Renderer;
	Window* m_Window;
};