#include "stdafx.h"
#include "Callback.h"
#include <chrono>
#include "World.h"

#define TICKRATE 60
#define MS_PER_TICK 1.0f / TICKRATE


void Game::Setup()
{
	// Setup Window
	Window::GetInstance().Setup();

	// Add Players?
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
			InvalidateRect(Window::GetInstance().GetHandle(), NULL, false); // force repaint
			Sleep(start.count() + MS_PER_TICK - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		}
	}
}