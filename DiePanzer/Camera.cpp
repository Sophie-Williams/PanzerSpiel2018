#include "stdafx.h"
#include "Camera.h"
#include "Math.h"
#include "Game.h"
#include "InputSystem.h"
#include <math.h>

void  CreateRotationMatrix(float pitch, float yaw, float roll, Matrix3f& rm)
{
	AngleAxisf rollAngle(roll,Vector3f::UnitZ());
	AngleAxisf yawAngle(yaw, Vector3f::UnitY());
	AngleAxisf pitchAngle(pitch, Vector3f::UnitX());	 

	rm = rollAngle * yawAngle * pitchAngle;
}

void Camera::CreateViewMatrix(const Vector3f& eye, const  Vector3f& target, const Vector3f& up, bool leftHanded, Matrix4f& vm)
{
	Vector3f zaxis = ((leftHanded) ? target - eye : eye - target).normalized();		// The "forward" Vector3f.
	Vector3f xaxis = up.cross(zaxis).normalized();		// The "right" Vector3f.	
	Vector3f yaxis = zaxis.cross(xaxis).normalized();	// The "up" Vector3f.
	
	// Create a 4x4 view matrix from the right, up, forward and eye position Vector3fs
	vm <<  xaxis.x(),			yaxis.x(),		zaxis.x(),		0.0f,
		   xaxis.y(),			yaxis.y(),		zaxis.y(),		0.0f,
		   xaxis.z(),			yaxis.z(),		zaxis.z(),		0.0f,
		  -xaxis.dot(eye),	   -yaxis.dot(eye), -zaxis.dot(eye), 1.0f;
}

Camera::Camera()
{
	m_up		= Vector3f{ 0.0f, 1.0f, 0.0f };
	m_position  = Vector3f{ 0.0f, 0.0f, -20.f};
	m_lookAt	= Vector3f{ 0.0f, 0.0f, 1.0f };

	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;

	m_dirty = true;
}

Camera::~Camera()
{

}

void Camera::SetPosition(Vector3f pos)
{
	m_position = pos;
}

float Camera::GetPitch()
{
	return m_pitch;
}

float Camera::GetYaw()
{
	return m_yaw;
}

float Camera::GetRoll()
{
	return m_roll;
}

void Camera::SetPitch(float radians)
{
	if (m_pitch != radians)
	{
		m_pitch = radians;
		m_dirty = true;
	}
	
}

void Camera::SetYaw(float radians)
{
	if (m_yaw != radians)
	{
		m_yaw = radians;
		m_dirty = true;
	}
}

void Camera::SetRoll(float radians)
{
	if (m_roll != radians)
	{
		m_roll = radians;
		m_dirty = true;
	}
}

void Camera::MoveForward(float amount)
{
	if (amount != 0.0f)
	{
		m_position += m_lookAt * amount;
		m_dirty = true;
	}
}

void Camera::MoveBackward(float amount)
{
	if (amount != 0.0f)
	{
		m_position += -m_lookAt * amount;
		m_dirty = true;
	}
}

void Camera::MoveUp(float amount)
{
	if (amount != 0.0f)
	{
		m_position += m_up * amount;
		m_dirty = true;
	}
}

void Camera::MoveDown(float amount)
{
	if (amount != 0.0f)
	{
		m_position += -m_up * amount;
		m_dirty = true;
	}
}

void Camera::StrafeLeft(float amount)
{
	if (amount != 0.0f)
	{
		Vector3f left = m_lookAt.cross(m_up);
		m_position += left * amount;
		m_dirty = true;
	}
}

void Camera::StrafeRight(float amount)
{
	if (amount != 0.0f)
	{
		Vector3f right = -m_lookAt.cross(m_up);
		m_position += right * amount;
		m_dirty = true;
	}
}

void Camera::Update() 
{
	if (!m_dirty)
		return;
	
	static Matrix3f rotationMatrix;
	static Vector3f lookAt, up;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	CreateRotationMatrix(m_pitch, m_yaw, m_roll, rotationMatrix);

	// Transform the lookAt and up Vector3f by the rotation matrix so the view is correctly rotated at the origin.
	m_lookAt = rotationMatrix * Vector3f{ 0.0f, 0.0f, 1.f };
	m_up = rotationMatrix * Vector3f{ 0.0f, 1.0f, 0.0f };

	m_lookAt.normalize();
	m_up.normalize();


	lookAt = m_lookAt;
	up = m_up;

	lookAt += m_position;

	m_dirty = false;

	// Finally create the view matrix from the three updated Vector3fs.
	CreateViewMatrix(m_position, lookAt, up, true, m_viewMatrix);
}

void Camera::GetViewMatrix(Matrix4f & vm)
{
	vm = m_viewMatrix;
}
