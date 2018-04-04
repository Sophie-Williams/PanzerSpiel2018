#include "stdafx.h"
#include "Tank.h"
#include "Eigen\Dense"


Tank::Tank(Vector3f position)
{	
	coordinates = position;
	identity = ObjectIdentity::ICollideable | ObjectIdentity::IRenderable | ObjectIdentity::Tank;
}

void Tank::Render(DX11Renderer* renderer, Matrix4f& world)
{
	model.Render(renderer->GetDeviceContext());	
	world = this->world;
}
