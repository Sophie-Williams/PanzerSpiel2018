#include "stdafx.h"
#include "Camera.h"
#include "Math.h"
#include "Game.h"
#include "InputSystem.h"

Camera::Camera()
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	dirty = true;
}

Camera::~Camera()
{

}

void Camera::Update() 
{
	if (!dirty)
	{
		return;
	}


	XMVECTOR positionVector, lookAtVector, upVector;
	XMFLOAT3 lookAt;
	static XMMATRIX rotationMatrix;
	float yaw, pitch, roll;
	
	upVector = XMLoadFloat3(&up);

	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);
	
	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch	= DEG_TO_RAD(rotation.x);
	yaw		= DEG_TO_RAD(rotation.y);
	roll	= DEG_TO_RAD(rotation.z);

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	dirty = false;
}

void Camera::GetViewMatrix(XMMATRIX & vm)
{
	vm = viewMatrix;
}
