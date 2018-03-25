#pragma once
#include "windows.h"
#include <cstdint>
#include <functional>

enum keystate
{
	up = 0,
	down,
	clicked
};

class InputSystem
{
private:
	HWND hWindow;
	WNDPROC pOriginalWndproc;
	keystate keys[0xFE];
	std::function<void(void)> hotkeys[256];
	std::vector<std::function<void(POINT delta)>> mousehooks;
	POINT mouseDelta;
	bool trapped_mouse;

public:
	void TrapMouse(HWND hwnd, POINT window_center);
	void ReleaseMouse();
	void CaptureMouseMovement(LPARAM mouse);
	POINT GetMouseDelta();
	void SetKeystate(uint32_t vkey, keystate state);
	bool WasKeyClicked(uint32_t vkey);
	bool IsKeyPressed(uint32_t vkey);
	void RegisterHotkey(uint32_t vkey, std::function<void(void)> func);
	void RemoveHotkey(std::uint32_t vkey);
	void RegisterMouseHook(std::function<void(POINT)> func);
};
