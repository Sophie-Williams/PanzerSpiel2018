#include "stdafx.h"
#include "Graphics.h"
#include "WindowsProcedure.h"
#include "InputSystem.h"

LRESULT WINAPI WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static InputSystem& input = InputSystem::GetInstance();
	static Graphics& graphics = Graphics::GetInstance();

	switch (msg)
	{
	case WM_PAINT:
		graphics.Frame();

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
	case WM_SIZE:
		break;

	// Inputs
	case WM_LBUTTONDOWN:
	case WM_KEYDOWN:
		input.SetKeystate(wParam, keystate::down);
		break;
	case WM_LBUTTONUP: // for some reason wParam isnt the vk code in this case
		input.SetKeystate(VK_LBUTTON, keystate::clicked);
		break;
	case WM_KEYUP:
		input.SetKeystate(wParam, keystate::clicked);
		break;


	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


