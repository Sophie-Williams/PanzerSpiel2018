#include "stdafx.h"
#include "GameObserver.h"
#include "InputSystem.h"
#include "Game.h"
#include <windows.h>
#include "Math.h"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
#include <algorithm>



GameObserver::GameObserver()
{
	m_camera = 0;
}

bool GameObserver::Initialize(Vector3f starting_position, Camera* camera)
{
	this->m_camera = camera;
	camera->SetPosition(starting_position);

	m_sensitivity = 0.1f;
	m_speed = 0.1f;

	return true;
}

inline void ClampInPlace(float& value, float minvalue, float maxvalue)
{
	value = std::max(minvalue, std::min(value, maxvalue));
}

void GameObserver::SetCameraAngles(float pitch, float yaw, float roll)
{
	// Normalize before setting
	pitch = std::remainderf(pitch, 2 * M_PI);
	yaw = std::remainderf(yaw, 2 * M_PI);
	roll = std::remainderf(roll, 2 * M_PI);
	
	m_camera->SetPitch(pitch);
	m_camera->SetYaw(yaw);
	m_camera->SetRoll(roll);
}

void GameObserver::Update()
{
	// Update rotation
	InputSystem* input = application->GetInputSystem();
	POINT mouse = input->GetMouseDelta();

	float pitch = DEG_TO_RAD((float)mouse.y * m_sensitivity) + m_camera->GetPitch();
	float yaw = DEG_TO_RAD((float)mouse.x * m_sensitivity) + m_camera->GetYaw();
	float roll = m_camera->GetRoll(); // Roll gets changed by keypress	

	if (input->IsKeyPressed('Q')) roll += 0.1f * m_sensitivity;
	if (input->IsKeyPressed('E')) roll -= 0.1f * m_sensitivity;
	
	SetCameraAngles(pitch, yaw, roll);


	// Update Postition
	if (input->IsKeyPressed('W'))// forward movement		
		m_camera->MoveForward(m_speed);

	if (input->IsKeyPressed('S'))// backward movement		
		m_camera->MoveBackward(m_speed);
	
	if (input->IsKeyPressed('A'))// strafe left		
		m_camera->StrafeLeft(m_speed);
	
	if (input->IsKeyPressed('D'))// strafe right		
		m_camera->StrafeRight(m_speed);

	if (input->IsKeyPressed(' '))// upward movement		
		m_camera->MoveUp(m_speed);

	if (input->IsKeyPressed('C'))// downward movement		
		m_camera->MoveDown(m_speed);
}
