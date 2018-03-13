#include "stdafx.h"
#include "Callback.h"
#include <chrono>
#include "World.h"

//GDI+ STUFF
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


#define TICKRATE 60
#define MS_PER_TICK 1.0f /TICKRATE

Game* Game::instance = nullptr;

Game::Game()
{

}

void OnPaint(HDC hdc)
{

}

LRESULT WINAPI WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(Game::GetInstance().GetWindowHandle(), &ps);
		// paint
		OnPaint(hdc);

		EndPaint(Game::GetInstance().GetWindowHandle(), &ps);
		break;
	case WM_CREATE:

		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		return TRUE;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

Game & Game::GetInstance()
{	
	if (!instance)
		instance = new Game();

	return *instance;	
}

bool Game::SetupWindow()
{
	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//Registering the Window Class
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Die Panzer";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	//Creating the Window
	hWindow = CreateWindowEx(WS_EX_CLIENTEDGE, wc.lpszClassName, L"Die Panzer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, NULL, NULL);

	if (hWindow == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	ShowWindow(hWindow, NULL);

	if (!UpdateWindow(hWindow))
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	return true;
}

void Game::Setup()
{

}

void Game::MainLoop()
{

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break; 
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			std::chrono::milliseconds start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			// Collect input			
			CreateMove.Call(tick);

			// do something with the input


			// Draw
			InvalidateRect(hWindow, NULL, false); // force repaint
			Sleep(start.count() + MS_PER_TICK - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		}
	}

	GdiplusShutdown(Game::GetInstance().Get_GDIPLUSTOKEN());
}

ULONG_PTR Game::Get_GDIPLUSTOKEN()
{
	return gdiplusToken;
}

HWND Game::GetWindowHandle()
{
	return hWindow;
}

