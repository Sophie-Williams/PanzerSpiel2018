#pragma once
#include "D3D.h"
#include "Eigen\Dense"
#include "Color.h"

class Model
{
private:
	struct VertexType
	{
		Eigen::Vector3f position;
		Eigen::Vector2f texcoord;
	};

public:
	Model();
	~Model();

public:
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	
	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:

	ID3D11Buffer *vertexBuffer, *indexBuffer;
	int m_vertexCount, m_indexCount;

};