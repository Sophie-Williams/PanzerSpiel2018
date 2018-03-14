#include "stdafx.h"
#include "Window.h"
#include <Dwmapi.h> 
#pragma comment(lib, "Dwmapi.lib")

#include "WindowProcedure.h"

bool Window::Setup()
{
	ZeroMemory(&Class, sizeof(Class));
	Class.cbSize = sizeof(Class);
	Class.hInstance = GetModuleHandle(NULL);
	Class.lpfnWndProc = WindowProcedure;
	Class.lpszClassName = L"PanzerWindowClass";
	Class.style = CS_HREDRAW | CS_VREDRAW;
	Class.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	if (RegisterClassEx(&Class))
	{
		//hWindow = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, Class.lpszClassName, Class.lpszClassName, WS_OVERLAPPED |WS_CAPTION | WS_SYSMENU, x, y, width, height, NULL, NULL, Class.hInstance, NULL);
		hWindow = CreateWindowEx(WS_EX_LAYERED, Class.lpszClassName, Class.lpszClassName,  WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_DLGFRAME, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH_DEFAULT, WINDOW_HEIGTH_DEFUALT, NULL, NULL, Class.hInstance, NULL);

		if (hWindow)
		{
			SetLayeredWindowAttributes(hWindow, RGB(0, 0, 0), 255, LWA_ALPHA);
			ShowWindow(hWindow, SW_SHOW);
			MARGINS Margins = { -1, -1, -1, -1 };
			DwmExtendFrameIntoClientArea(hWindow, &Margins);
			return true;
		}
		else
		{
			MessageBoxW(NULL, L"CreateWindowEx Failed!", L"Fatal Error", MB_OK);
			UnregisterClass(Class.lpszClassName, Class.hInstance);
			return false;
		}
	}
	else
	{
		MessageBoxW(NULL, L"RegisterClassEx Failed!", L"Fatal Error", MB_OK);
		return false;
	}
}

Window::~Window()
{
	DestroyWindow(hWindow);
	UnregisterClass(Class.lpszClassName, Class.hInstance);
}

HWND Window::GetHandle()
{
	return hWindow;
}

