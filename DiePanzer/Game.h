#pragma once
#include <Windows.h>
#include <cstdint>
#include "Callback.h"


//forward declarations
class World;



class Game
{	
private:
	Game();
	~Game();
	static Game* instance;
	uint32_t tick;	
	HWND hWindow;
	ULONG_PTR gdiplusToken;
	World* world;

public:
	const static uint32_t mapsize_x = 800;
	const static uint32_t mapsize_y = 600;

public:
	static Game& GetInstance();
	Callback<uint32_t> CreateMove;	
	bool SetupWindow();
	void Setup();
	void MainLoop();
	ULONG_PTR Get_GDIPLUSTOKEN();
	HWND GetWindowHandle();
};

LRESULT WINAPI WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);