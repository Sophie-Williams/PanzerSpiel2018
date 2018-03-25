#include "stdafx.h"
#include "GameObserver.h"
#include "Vector.h"
#include "InputSystem.h"
#include "Game.h"
#include <windows.h>

GameObserver::GameObserver()
{
	camera = 0;
}

bool GameObserver::Initialize(Vector starting_position, Camera* camera)
{
	this->camera = camera;
	coordinates = starting_position;	
	mouse_sensitivity = 0.1f;

	return true;
}

void GameObserver::Update()
{
	// Update rotation
	InputSystem* input = application->GetInputSystem();
	POINT mouse = input->GetMouseDelta();

	mouse.x *= mouse_sensitivity;
	mouse.y *= mouse_sensitivity;

	camera->rotation.x += mouse.y;
	camera->rotation.y += mouse.x;
	// we dont rotate the camera around z 
	camera->rotation.z = 0;

	// TODO:
	// Update Postition
	if (input->IsKeyPressed(0x57))
	{
		// forward movement
	}

	if (input->IsKeyPressed(0x53))
	{
		// backward movement
	}
	if (input->IsKeyPressed(0x41))
	{
		// strafe left
	}
	if (input->IsKeyPressed(0x44))
	{
		// strafe right
	}

	camera->dirty = true;

}
