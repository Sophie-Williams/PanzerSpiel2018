#include "stdafx.h"
#include "WindowProcedure.h"

LRESULT WINAPI WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:

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

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
