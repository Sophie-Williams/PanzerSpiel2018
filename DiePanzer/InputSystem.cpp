#include "stdafx.h"
#include "InputSystem.h"

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
