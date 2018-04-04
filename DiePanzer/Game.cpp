#include "stdafx.h"
#include "Callback.h"
#include <chrono>
#include "World.h"
#include "Game.h"
#include "Graphics.h"
#include "InputSystem.h"
#include "Camera.h"

#define TICKRATE (60)
#define MS_PER_TICK (1.0f / TICKRATE)

Game* application = nullptr;



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
		// this is necessary even if we dont use it
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);

		graphics->Frame();

		EndPaint(hwnd, &ps);
		break;
	case WM_CREATE:
		break;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_SIZE:
		break;

	case WM_MOUSEMOVE:
		inputsystem->CaptureMouseMovement(lParam);
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
	tick = 0;
	// Setup Graphics
	graphics = new Graphics();
	graphics->Initialize();

	world = new World();
	world->Initialize();

	// Add Players?
	inputsystem = new InputSystem();
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
			//CreateMove.Call(tick);
			inputsystem->Tick();


			// Capture and Release Mouse
			if (inputsystem->WasKeyClicked(VK_ESCAPE))
			{
				inputsystem->ReleaseMouse();
			}
			else if (inputsystem->WasKeyClicked(VK_LBUTTON))
			{
				inputsystem->TrapMouse(graphics->GetWindowHandle(), graphics->GetWindowCenter());				
			}
			// do something with the input


			// Draw
			InvalidateRect(graphics->GetWindowHandle(), NULL, false); // force repaint

		    // advance one tick
			tick++;

			long long sleepamount = start.count() + (long long)(MS_PER_TICK + 0.5f) - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			if (sleepamount < 0) sleepamount = 0;
			Sleep(sleepamount);
		}
	}
}

uint32_t Game::GetCurrentTick()
{
	return tick;
}

InputSystem * Game::GetInputSystem()
{
	return inputsystem;
}

Graphics * Game::GetGraphicsInterface()
{
	return graphics;
}

World * Game::GetWorld()
{
	return world;
}
