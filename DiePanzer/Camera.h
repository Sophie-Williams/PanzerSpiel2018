#pragma once
#include "D3D.h"

class Camera
{
friend class GameObserver;

public:
	Camera();
	~Camera();	

	void Update();

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();
	
	void GetViewMatrix(XMMATRIX& vm);

private:
	XMFLOAT3 up;
	XMFLOAT3 rotation, position;
	bool dirty;
	XMMATRIX viewMatrix;
};