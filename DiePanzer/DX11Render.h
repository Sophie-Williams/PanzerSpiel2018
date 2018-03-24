#pragma once
#include <windows.h>
#include "D3D.h"
#include "Color.h"


struct Vertex
{
	float X, Y, Z;
};

class DX11Renderer
{
public:
	DX11Renderer();
	void BeginScene(Color background);
	void EndScene();
	~DX11Renderer();

	bool Initialize(HWND window, unsigned int screenWidth, unsigned int screenHeight, bool enable_vsync, bool fullscreen, float nearplane, float farplane);
	void Shutdown();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

private:
	bool vsync_enabled;

	size_t m_videoCardMemory;
	char m_videoCardDescription[128];

	IDXGISwapChain* swapChain;
	ID3D11Device* device;                     
	ID3D11DeviceContext* deviceContext;          
	ID3D11RenderTargetView* backbuffer;    
	HWND hWindow;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterState;
	XMMATRIX projectionMatrix;
	XMMATRIX worldMatrix;
	XMMATRIX orthoMatrix;
};