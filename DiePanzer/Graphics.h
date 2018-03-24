#pragma once
#include "DX11Render.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void Frame();
	bool Initialize();
	HWND GetWindowHandle();

	inline unsigned int GetClientSizeWidth()
	{
		return client_size.right -client_size.left;
	}
	inline unsigned int GetClientSizeHeight()
	{
		return client_size.bottom - client_size.top;
	}

private:
	HWND InitWindow(const RECT & size, const DWORD style);

private:
	bool is_initialized;
	DWORD window_style;
	WNDCLASSEX wndClass;
	RECT client_size;
	HWND hWindow;
	DX11Renderer* renderer;
};