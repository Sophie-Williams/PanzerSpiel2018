#pragma once
#include <cstdint>
#include "Eigen/Dense"


class ObjectIdentity
{
public:
	static const int Tank = 1 << 0;
	static const int Bullet = 1 << 1;
	static const int ICollideable = 1 << 3;
	static const int IRenderable = 1 << 4;
};

enum class ClassID 
{ 
	tank_standart = 0, 
	bullet_standart,
	observer
};

class GameObject
{
protected:
	Eigen::Vector3f coordinates;	///element 0: x, element 1: y
	uint32_t id;
	uint32_t faction;
	int identity;
public:
	virtual int GetIdentity() = 0;

};