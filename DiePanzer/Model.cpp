#include "stdafx.h"
#include "Model.h"
#include "Eigen\Dense"

using namespace Eigen;

Model::Model()
{
	vertexBuffer = 0;
	indexBuffer = 0;
}

Model::~Model()
{

}

bool Model::Initialize(ID3D11Device* device)
{
	bool result;

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void Model::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();
}

void Model::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);
}

int Model::GetIndexCount()
{
	return m_indexCount;
}

bool Model::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 8;

	// Set the number of indices in the index array.
	m_indexCount = 36;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = Vector3f(-1.0f, -1.0f, -1.0f); 
	vertices[0].texcoord = Vector2f(0.0f, 0.0f);

	vertices[1].position = Vector3f(-1.0f, +1.0f, -1.0f);  
	vertices[1].texcoord = Vector2f(0.0f, 1.0f);

	vertices[2].position = Vector3f(+1.0f, +1.0f, -1.0f); 
	vertices[2].texcoord = Vector2f(0.0f, 0.0f);

	vertices[3].position = Vector3f(+1.0f, -1.0f, -1.0f); 
	vertices[3].texcoord = Vector2f(0.0f, 0.0f);

	vertices[4].position = Vector3f(-1.0f, -1.0f, +1.0f); 
	vertices[4].texcoord = Vector2f(0.0f, 1.0f);

	vertices[5].position = Vector3f(-1.0f, +1.0f, +1.0f); 
	vertices[5].texcoord = Vector2f(0.0f, 0.0f);

	vertices[6].position = Vector3f(+1.0f, +1.0f, +1.0f); 
	vertices[6].texcoord = Vector2f(0.0f, 1.0f);

	vertices[7].position = Vector3f(+1.0f, -1.0f, +1.0f); 
	vertices[7].texcoord = Vector2f(0.0f, 0.0f);


	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.
	indices[3] = 0;  // Bottom left.
	indices[4] = 2;  // Top middle.
	indices[5] = 3;  // Bottom right.

	indices[6] = 4;  // Bottom left.
	indices[7] = 6;  // Top middle.
	indices[8] = 5;  // Bottom right.
	indices[9] = 4;  // Bottom left.
	indices[10] = 7;  // Top middle.
	indices[11] = 6;  // Bottom right.

	indices[12] = 4;  // Bottom left.
	indices[13] = 5;  // Top middle.
	indices[14] = 1;  // Bottom right.
	indices[15] = 4;  // Bottom left.
	indices[16] = 1;  // Top middle.
	indices[17] = 0;  // Bottom right.

	indices[18] = 3;  // Bottom left.
	indices[19] = 2;  // Top middle.
	indices[20] = 6;  // Bottom right.
	indices[21] = 3;  // Bottom left.
	indices[22] = 6;  // Top middle.
	indices[23] = 7;  // Bottom right.


	indices[24] = 1;  // Bottom left.
	indices[25] = 5;  // Top middle.
	indices[26] = 6;  // Bottom right.
	indices[27] = 1;  // Bottom left.
	indices[28] = 6;  // Top middle.
	indices[29] = 2;  // Bottom right.


	indices[30] = 4;  // Bottom left.
	indices[31] = 0;  // Top middle.
	indices[32] = 3;  // Bottom right.
	indices[33] = 4;  // Bottom left.
	indices[34] = 3;  // Top middle.
	indices[35] = 7;  // Bottom right.

	 // Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void Model::ShutdownBuffers()
{
	// Release the index buffer.
	if (indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (vertexBuffer)
	{
		vertexBuffer->Release();
		vertexBuffer = 0;
	}
}

void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}