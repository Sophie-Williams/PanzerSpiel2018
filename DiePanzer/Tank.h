#pragma once
#include <cstdint>
#include "GameObject.h"
#include "Move.h"
#include "IRenderable.h"


class Tank :public IRenderable, public GameObject 
{
	friend class World;
	friend class TankControl;

private:
	float turret_orientation;	///0..2pi; 0 is forward in relation to the chassis; clockwise
	float chassis_orientation;	///0...2pi; 0 is towards the top of the screen; clockwise
	float speed;	///in maptiles/tick
	uint32_t ammo;
	bool cannon_loaded;
	uint32_t remaining_reload_time;
	Move nextMove;

public:
	Tank(Eigen::Vector3f position);
	virtual void Render(DX11Renderer * renderer, Eigen::Matrix4f& world);
	virtual int GetIdentity() { return  ObjectIdentity::ICollideable | ObjectIdentity::IRenderable | ObjectIdentity::Tank; }
	Move Get_move() { return nextMove; }	

};