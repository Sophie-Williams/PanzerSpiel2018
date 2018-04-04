#include "stdafx.h"
#include "InputSystem.h"
#include "Camera.h"
#include "Game.h"
#include <windowsx.h>

void InputSystem::TrapMouse(HWND hwnd, POINT window_center)
{
	ShowCursor(false);
	SetCursorPos(window_center.x, window_center.y);
	trapped_mouse = true;
}

void InputSystem::ReleaseMouse()
{
	ShowCursor(true);
	ClipCursor(nullptr);
	trapped_mouse = false;
}

// TODO:: add all mousedeltas that are in the same tick
void InputSystem::CaptureMouseMovement(LPARAM mouse)
{
	// check if the window ha trapped the mouse
	if (!trapped_mouse)	return;
	
	Graphics* graphics = application->GetGraphicsInterface();
	POINT currentPos, window_position, window_center;

	window_center = graphics->GetWindowCenter();

	currentPos.x = GET_X_LPARAM(mouse);
	currentPos.y = GET_Y_LPARAM(mouse);

	ClientToScreen(graphics->GetWindowHandle(), &currentPos);


	// add all mousedeltas of the same tick, in case we get multiple WM_MOUSEMOVE in one tick
	static uint32_t previous_tick = 0;
	uint32_t current_tick = application->GetCurrentTick();

	if (previous_tick == current_tick)
	{
		// accumulate
		mouseDelta.x += currentPos.x - window_center.x;
		mouseDelta.y += currentPos.y - window_center.y;
	}
	else
	{
		// overwrite
		mouseDelta.x = currentPos.x - window_center.x;
		mouseDelta.y = currentPos.y - window_center.y;
		previous_tick = current_tick;
	}
	SetCursorPos(window_center.x, window_center.y);
}
	
void InputSystem::Tick()
{
	mouseDelta_output = mouseDelta;
	mouseDelta = {0, 0};
}

POINT InputSystem::GetMouseDelta()
{	
	return mouseDelta_output;
}

void InputSystem::SetKeystate(uint32_t vkey, keystate state)
{
	if (vkey > 0 && vkey < 255)
	{
		keys[vkey] = state;
	
		if (state == keystate::clicked)
		{
			auto& hotkey_callback = hotkeys[vkey];

			if (hotkey_callback)
				hotkey_callback();

		}		

	}
		
}

bool InputSystem::WasKeyClicked(uint32_t vkey)
{
	if (keys[vkey] == keystate::clicked)
	{
		keys[vkey] = keystate::up;
		return true;
	}
	return false;
}

bool InputSystem::IsKeyPressed(uint32_t vkey)
{
	return keys[vkey] == keystate::down;
}

void InputSystem::RegisterHotkey(uint32_t vkey, std::function<void(void)> func)
{
	hotkeys[vkey] = func;
}

void InputSystem::RemoveHotkey(std::uint32_t vkey)
{
	hotkeys[vkey] = nullptr;
}

void InputSystem::RegisterMouseHook(std::function<void(POINT)> func)
{
	mousehooks.push_back(func);
}
