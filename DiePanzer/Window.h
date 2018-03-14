#pragma once

#define WINDOW_WIDTH_DEFAULT 800
#define WINDOW_HEIGTH_DEFUALT 600

class Window : public Singleton<Window>
{
private:
	HWND hWindow;
	WNDCLASSEX Class;

	int width;
	int height;
	int x;
	int y;

public:
	~Window();

	HWND GetHandle();
	bool Setup();
};
