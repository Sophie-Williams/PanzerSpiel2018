#include "stdafx.h"
#include "Callback.h"
#include <chrono>
#include "World.h"
#include "Game.h"
#include "Graphics.h"
#include "InputSystem.h"

#define TICKRATE (60)
#define MS_PER_TICK (1.0f / TICKRATE)

Game* application = nullptr;

void beep()
{
	Beep(500, 200);
}

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the game class.
	default:	
		return application->MessageHandler(hwnd, msg, wParam, lParam);	
	}
}



LRESULT Game::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		graphics->Frame();
		break;
	case WM_CREATE:
		break;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_SIZE:
		break;

		// Inputs
	case WM_LBUTTONDOWN:
	case WM_KEYDOWN:
		inputsystem->SetKeystate(wParam, keystate::down);
		break;
	case WM_LBUTTONUP: // for some reason wParam isnt the vk code in this case
		inputsystem->SetKeystate(VK_LBUTTON, keystate::clicked);
		break;
	case WM_KEYUP:
		inputsystem->SetKeystate(wParam, keystate::clicked);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void Game::Setup()
{
	// Setup Graphics
	graphics = new Graphics();
	graphics->Initialize();

	// Add Players?
	inputsystem = new InputSystem();
	inputsystem->RegisterHotkey(VK_LBUTTON, beep);

	// Start Loop
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
			InvalidateRect(graphics->GetWindowHandle(), NULL, false); // force repaint
			Sleep(start.count() + (DWORD)(MS_PER_TICK + 0.5f) - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		}
	}
}
