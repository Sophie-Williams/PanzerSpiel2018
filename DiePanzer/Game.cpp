#include "stdafx.h"
#include "Callback.h"
#include <chrono>
#include "World.h"
#include "Game.h"
#define TICKRATE 60
#define MS_PER_TICK 1.0f / TICKRATE


// only visible in this file
static Graphics* graphics;

void beep()
{
	Beep(500, 200);
}

void Game::Setup()
{
	// Setup Window
	graphics = &Graphics::GetInstance();
	graphics->Initialize();

	// Add Players?
	InputSystem& input = InputSystem::GetInstance();
	input.RegisterHotkey(VK_LBUTTON, beep);

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
			Sleep(start.count() + MS_PER_TICK - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		}
	}
}