#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Eigen\Dense"
#include "D3D.h"

class DX11Renderer;

class IRenderable
{
protected:
	IRenderable()
	{
		world = Eigen::Matrix4f::Identity();
	}
	~IRenderable()
	{

	}
protected:
	Model model;
	Eigen::Matrix4f world;

public:
	bool Initialize(ID3D11Device* device) { return model.Initialize(device); }
	const Eigen::Matrix4f& GetWorldMatrix() { return world; }
	int GetIndexCount() { return model.GetIndexCount(); }
	virtual void Render(DX11Renderer*, Eigen::Matrix4f& world) = 0;
};


