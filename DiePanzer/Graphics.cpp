#include "stdafx.h"
#include "Graphics.h"
#include <Dwmapi.h> 
#pragma comment(lib, "Dwmapi.lib")
#include "Color.h"

Graphics::Graphics()
{
	renderer = 0;
	hWindow = 0;
	is_initialized = false;

	// window settings
	client_size = RECT{ 0, 0, 800, 600 };
	window_style = WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_DLGFRAME;
}

Graphics::~Graphics()
{
	if (hWindow)
	{
		DestroyWindow(hWindow);
		UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
	}
		
}

void Graphics::Frame()
{
	if (!is_initialized)
		return;

	renderer->BeginScene(Color{0.2f,0.2f,0.2f,1.0f});

	// render map
	// for each IRenderObject -> Render 

	renderer->EndScene();
}



HWND Graphics::InitWindow(const RECT& size, const DWORD style)
{	
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(wndClass);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = L"PanzerWindowClass";
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);


	if (!RegisterClassEx(&wndClass))
	{
		MessageBoxW(NULL, L"RegisterClassEx Failed!", L"Fatal Error", MB_OK);
		return nullptr;
	}
	
	// Open the Window in the middle of the screen
	int pos_x = (GetSystemMetrics(SM_CXSCREEN) - GetClientSizeWidth()) / 2;
	int pos_y = (GetSystemMetrics(SM_CYSCREEN) - GetClientSizeHeight()) / 2;

	//hWindow = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, Class.lpszClassName, Class.lpszClassName, WS_OVERLAPPED |WS_CAPTION | WS_SYSMENU, x, y, width, height, NULL, NULL, Class.hInstance, NULL);
	hWindow = CreateWindowEx(WS_EX_APPWINDOW, wndClass.lpszClassName, wndClass.lpszClassName, style, pos_x, pos_y, GetClientSizeWidth(), GetClientSizeHeight(), NULL, NULL, wndClass.hInstance, NULL);

	if (!hWindow)
	{
		MessageBoxW(NULL, L"CreateWindowEx Failed!", L"Fatal Error", MB_OK);
		UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
		return nullptr;		
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(hWindow, SW_SHOW);
	SetForegroundWindow(hWindow);
	SetFocus(hWindow);
	
	return hWindow;

}

bool Graphics::Initialize()
{
	RECT window_size = client_size;
	//DONE inno2: set Window size to something > 800x600, so the ClientSize is exactly 800x600
	AdjustWindowRect(&window_size, window_style, false);

	hWindow = InitWindow(window_size, window_style);
	if (!hWindow)
	{
		MessageBoxW(NULL, L"Failed to Create Window", L"Panzerspiel", MB_OK | MB_TOPMOST);
		return false;
	}		

	renderer = new DX11Renderer();
	if (!renderer->Initialize(hWindow,GetClientSizeWidth(), GetClientSizeHeight(),true,false,0.1f,1000.0f))
	{
		MessageBoxW(NULL, L"Failed to Create DX11", L"Panzerspiel", MB_OK | MB_TOPMOST);
		return false;
	}

	// now we can start to render
	is_initialized = true;
	return true;
}

HWND Graphics::GetWindowHandle()
{
	return hWindow;
}
