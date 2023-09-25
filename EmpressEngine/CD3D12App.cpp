#include "CD3D12App.h"

CD3D12App::CD3D12App()
{
}

CD3D12App::~CD3D12App()
{
}

bool CD3D12App::InitD3D()
{
	CheckDXDebug();

	HR(CreateDXGIFactory1(IID_PPV_ARGS(&p_dxgiFactory4)));
	HRESULT _HR = (D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&p_d3dDevice)));
	if (FAILED(_HR)) {
		HR(p_dxgiFactory4->EnumWarpAdapter(IID_PPV_ARGS(&p_warpAdapter)));

		HR(D3D12CreateDevice(p_warpAdapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&p_d3dDevice)));
	}
	return _HR == S_OK;
}

void CD3D12App::CheckDXDebug()
{
#if defined (DEBUG)  || defined(_DEBUG) 
	{
		ComPtr<ID3D12Debug> debugLayer;
		HR(D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer)));
		debugLayer->EnableDebugLayer();
	}
#endif
}
