#pragma once
#include "GameObject.h"

// forward declarations
class Camera;

// controls the camera and other stuff
// not colldiable and not renderable
class GameObserver : public GameObject
{
public:
	GameObserver();
	~GameObserver();
	
	bool Initialize(Vector starting_position, Camera* camera);
	void Update();

	ClassID Get_type() { return ClassID::observer; }

private:
	float mouse_sensitivity;
	Camera* camera;
};