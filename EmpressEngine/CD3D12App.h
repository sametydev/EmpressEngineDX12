#pragma once
#include "DXConfig.h"

class CD3D12App
{
public:
	CD3D12App();
	~CD3D12App();

	void InitD3D();
	ComPtr<IDXGIAdapter1> p_dxgiAdapter;
	ComPtr<ID3D12Device> p_d3dDevice;
};

