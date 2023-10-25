#pragma once
#include "../../DXConfig.h"

class CD3D12App
{
public:
	CD3D12App();
	~CD3D12App();

	bool InitD3D();

	void CheckDXDebug();
	void CheckMSAASupport();
	void InitCmdObjects();
	void CreateSwapChain();

protected:
	ComPtr<IDXGIAdapter> p_warpAdapter;
	ComPtr<IDXGIFactory4> p_dxgiFactory4;
	ComPtr<ID3D12Device> p_d3dDevice;

	ComPtr<ID3D12Fence1> p_d3dFence;

	ComPtr<ID3D12CommandQueue> p_commandQueue;
	ComPtr<ID3D12CommandAllocator> p_commandListAlloc;
	ComPtr<ID3D12GraphicsCommandList> p_commandList;

private:
	UINT rtvDescSize, dsvDescSize, cbvDescSize;
};

