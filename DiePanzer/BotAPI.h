#pragma once
#include <vector>
#include "TankControl.h"
#include <cstdint>

class BotAPI
{
private:
	std::vector<TankControl> mytanks;
	uint32_t tank_amount;
	uint32_t faction;

public:
	void GetEnemyTankInfo(uint32_t tanknr, Tank& tankinfo); 
	uint32_t GetEnemyTankAmount();
};

/*

// clear out the struct for use
ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

// fill the swap chain description struct
scd.BufferCount = 1;                                    // one back buffer
scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
scd.OutputWindow = m_Window;                            // the window to be used
scd.SampleDesc.Count = 4;                               // how many multisamples
scd.Windowed = TRUE;                                    // windowed/full-screen mode	
														// create a device, device context and swap chain using the information in the scd struct
if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &swapchain, &dev, NULL, &devcon) != S_OK)
{
	return false;
}


// get the address of the back buffer
ID3D11Texture2D *pBackBuffer;
swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

// use the back buffer address to create the render target
if (dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer) != S_OK)
{
	return false;
}

pBackBuffer->Release();

// set the render target as the back buffer
devcon->OMSetRenderTargets(1, &backbuffer, NULL);

// Set the viewport
D3D11_VIEWPORT viewport;
ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

viewport.TopLeftX = 0;
viewport.TopLeftY = 0;
viewport.Width = (float)width;
viewport.Height = (float)height;

devcon->RSSetViewports(1, &viewport);

*/