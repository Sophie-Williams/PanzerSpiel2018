#pragma once
#include <Windows.h>
#include <cstdint>
#include "Callback.h"

//forward declarations
class World;
class Graphics;
class InputSystem;


class Game
{	
private:
	uint32_t tick;	
	World* world;
	Graphics* graphics;
	InputSystem* inputsystem;

public:
	LRESULT WINAPI MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	Callback<uint32_t> CreateMove;	
	void Setup();
	void MainLoop();
};

extern Game* application;

// Window Message Handler
LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



