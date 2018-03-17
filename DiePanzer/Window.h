#pragma once

class Window
{
private:
	HWND hWindow;
	WNDCLASSEX Class;

	int width;
	int height;
	int pos_x;
	int pos_y;

public:
	Window(unsigned int width, unsigned int height);
	~Window();
	
	bool Setup(HWND& window);
	unsigned int GetClientSizeWidth();
	unsigned int GetClientSizeHeight();
};
