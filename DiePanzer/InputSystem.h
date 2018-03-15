#pragma once
#include "windows.h"
#include <cstdint>
#include <functional>
#include "Singleton.h"

enum keystate
{
	up = 0,
	down,
	clicked
};

class InputSystem : public Singleton<InputSystem>
{
private:
	HWND hWindow;
	WNDPROC pOriginalWndproc;
	keystate keys[0xFE];
	std::function<void(void)> hotkeys[256];

public:
	void SetKeystate(uint32_t vkey, keystate state);
	bool WasKeyClicked(uint32_t vkey);
	bool IsKeyPressed(uint32_t vkey);
	void RegisterHotkey(uint32_t vkey, std::function<void(void)> func);
	void RemoveHotkey(std::uint32_t vkey);
};
