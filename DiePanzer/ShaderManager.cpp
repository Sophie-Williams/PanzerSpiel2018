#include "stdafx.h"
#include "ShaderManager.h"
#include <fstream>
#include <string>
#include <array>
#include <fstream>
#include <filesystem>

ShaderManager::ShaderManager()
{
	vertexShader = 0;
	pixelShader = 0;
	layout = 0;
	matrixBuffer = 0;
	m_sampleState = 0;
}

ShaderManager::~ShaderManager()
{

}

bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, hwnd, L"C:\\Users\\Robin\\Documents\\Github\\PanzerSpiel2018\\x64\\Debug\\VSTexture.cso", L"C:\\Users\\Robin\\Documents\\Github\\PanzerSpiel2018\\x64\\Debug\\PSTexture.cso");
	if (!result)
	{
		return false;
	}

	return true;
}

void ShaderManager::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}

bool ShaderManager::Render(ID3D11DeviceContext* deviceContext, int indexCount, Matrix4f worldMatrix, Matrix4f viewMatrix, Matrix4f projectionMatrix, ID3D11ShaderResourceView* texture)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}

// this function loads a file into an Array
bool ShaderManager::LoadShaderFile(const WCHAR* filepath, ShaderBlob& shaderblob)
{
    // open the file
    std::ifstream VertexFile(filepath, std::ios::in | std::ios::binary | std::ios::ate);

    // if open was successful
    if(VertexFile.is_open())
    {
        // find the length of the file
		shaderblob.length = (size_t)VertexFile.tellg();
		shaderblob.bytes = new byte[shaderblob.length];

        // collect the file data		
        VertexFile.seekg(0, std::ios::beg);
        VertexFile.read(reinterpret_cast<char*>(shaderblob.bytes), shaderblob.length);
        VertexFile.close();
		return true;
    }
	else
	{
		return false;
	}
}

bool ShaderManager::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	ShaderBlob vertexShaderBlob;
	ShaderBlob pixelShaderBlob;

	if (!LoadShaderFile(vsFilename, vertexShaderBlob))
	{
		return false;
	}

	if (!LoadShaderFile(psFilename, pixelShaderBlob))
	{
		return false;
	}

	result = device->CreateVertexShader(vertexShaderBlob.bytes, vertexShaderBlob.length, NULL, &vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBlob.bytes, pixelShaderBlob.length, NULL, &pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;
	
	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBlob.bytes, vertexShaderBlob.length, &layout);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Create a texture sampler state description
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 1;
	samplerDesc.BorderColor[1] = 1;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 1;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ShaderManager::ShutdownShader()
{
	//Release the sampler state
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	// Release the matrix constant buffer.
	if (matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}

	// Release the layout.
	if (layout)
	{
		layout->Release();
		layout = 0;
	}

	// Release the pixel shader.
	if (pixelShader)
	{
		pixelShader->Release();
		pixelShader = 0;
	}

	// Release the vertex shader.
	if (vertexShader)
	{
		vertexShader->Release();
		vertexShader = 0;
	}

	return;
}

bool ShaderManager::SetShaderParameters(ID3D11DeviceContext* deviceContext, const Matrix4f& world, const Matrix4f& view, const Matrix4f& projection, ID3D11ShaderResourceView* texture)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = world;
	dataPtr->view = view;
	dataPtr->projection = projection;

	// Unlock the constant buffer.
	deviceContext->Unmap(matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &matrixBuffer);

	// Set shader texture resource in the pixel shader
	deviceContext->PSSetShaderResources(0, 1, &texture);

	return true;
}

void ShaderManager::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(layout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);

	// Set the sampler state in the pixel shader
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	// Render the triangle.
	deviceContext->DrawIndexed(indexCount, 0, 0);
}
