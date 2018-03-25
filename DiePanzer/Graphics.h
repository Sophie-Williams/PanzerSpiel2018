#pragma once
#include "DX11Render.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "IRenderable.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void Frame();
	bool Initialize();
	HWND GetWindowHandle();

	// for observer 
	Camera* GetCamera();

	POINT GetWindowCenter();
	POINT GetWindowPos();
	unsigned int GetClientSizeWidth();
	unsigned int GetClientSizeHeight();

private:
	HWND InitWindow(const RECT & size, const DWORD style);

private:
	bool is_initialized;
	DWORD window_style;
	WNDCLASSEX wndClass;
	RECT client_size;
	HWND hWindow;
	DX11Renderer* renderer;
	ShaderManager* shaders;
	Camera* camera;
	IRenderable* model;
};