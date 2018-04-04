#pragma once
#include "Eigen/Dense"

using namespace Eigen;

class Camera
{
friend class GameObserver;

public:
	
	Camera();
	~Camera();

	void SetPosition(Vector3f pos);

	float GetPitch();
	float GetYaw();
	float GetRoll();

	void SetPitch(float radians);
	void SetYaw(float radians);
	void SetRoll(float radians);
	void MoveForward(float amount);
	void MoveBackward(float amount);
	void MoveUp(float amount);
	void MoveDown(float amount);
	void StrafeLeft(float amount);
	void StrafeRight(float amount);
	void Update();

	void CreateViewMatrix(const Vector3f & eye, const Vector3f & target, const Vector3f & up, bool leftHanded, Matrix4f & vm);
	void GetViewMatrix(Matrix4f& vm);

private:
	float m_pitch, m_yaw, m_roll;
	Vector3f m_lookAt, m_right, m_position, m_up;
	bool m_dirty;
	Matrix4f m_viewMatrix;
};