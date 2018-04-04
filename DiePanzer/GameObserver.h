#pragma once
#include "GameObject.h"
#include "Eigen\Dense"

using namespace Eigen;

// forward declarations
class Camera;

// controls the camera and other stuff
// not colldiable and not renderable
class GameObserver
{
public:
	GameObserver();
	~GameObserver();
	
	bool Initialize(Vector3f starting_position, Camera* camera);
	void SetCameraAngles(float pitch, float yaw, float roll);
	void Update();

private:
	float m_sensitivity;
	float m_speed;
	Camera* m_camera;
};