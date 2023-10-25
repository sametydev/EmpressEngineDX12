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

	HR(p_d3dDevice->CreateFence(
		0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&p_d3dFence)
	));

	rtvDescSize = p_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	dsvDescSize = p_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	cbvDescSize = p_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	CheckMSAASupport();

	InitCmdObjects();

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

void CD3D12App::CheckMSAASupport()
{
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msaaQualityLevels{};
	msaaQualityLevels.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	msaaQualityLevels.SampleCount = 4;
	msaaQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msaaQualityLevels.NumQualityLevels = NULL;

	HR(p_d3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaQualityLevels, sizeof(msaaQualityLevels)
	));

	assert(msaaQualityLevels.NumQualityLevels > 0 && "[Empress Engine] Problem on MSAA Level <DirectX_12>");
}

void CD3D12App::InitCmdObjects()
{
	D3D12_COMMAND_QUEUE_DESC qDesc{};

	qDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	qDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	HRESULT _hr;
	_hr = p_d3dDevice->CreateCommandQueue(&qDesc, IID_PPV_ARGS(p_commandQueue.GetAddressOf()));
	HR(_hr);

	_hr = p_d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(p_commandListAlloc.GetAddressOf()));
	HR(_hr);

	_hr = p_d3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, p_commandListAlloc.Get(), nullptr, IID_PPV_ARGS(p_commandList.GetAddressOf()));
	HR(_hr);

	p_commandList->Close();
}

void CD3D12App::CreateSwapChain()
{
	p_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC desc{};
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


}
