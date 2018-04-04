#pragma once
#include "D3D.h"
#include "Eigen/Dense"

using namespace Eigen;

class ShaderManager
{
private:
	struct MatrixBufferType
	{
		Matrix4f world;
		Matrix4f view;
		Matrix4f projection;
	};
	struct ShaderBlob
	{
		byte* bytes;
		size_t length;
	};


public:
	ShaderManager();
	~ShaderManager();

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext * deviceContext, int indexCount, Matrix4f worldMatrix, Matrix4f viewMatrix, Matrix4f projectionMatrix, ID3D11ShaderResourceView * texture);
	bool Render(ID3D11DeviceContext*, int, Matrix4f, Matrix4f, Matrix4f);

private:
	bool LoadShaderFile(const WCHAR * filepath, ShaderBlob & shaderblob);
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();

	bool SetShaderParameters(ID3D11DeviceContext * deviceContext, const Matrix4f & world, const Matrix4f & view, const Matrix4f & projection, ID3D11ShaderResourceView * texture);

	bool SetShaderParameters(ID3D11DeviceContext * deviceContext, const Matrix4f & world, const Matrix4f & view, const Matrix4f & projection);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* m_sampleState;
};