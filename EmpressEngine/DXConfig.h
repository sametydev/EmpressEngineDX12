#pragma once
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"DXGI.lib")
#ifdef _DEBUG
#pragma comment(lib,"dxguid.lib")
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#define _XM_NO_INTRINSICS_
#include <wrl/client.h>
#include <stdio.h>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw std::exception();
    }
}

#define HR(x)\
{ \
HRESULT hr = (x); \
if(FAILED(hr)) \
{ \
std::cout << "\033[1;31m**************************\n" <<"Error on this file : \n " << __FILE__ << "\n In This Line : " <<(DWORD)__LINE__ << "  HR Code : "<< hr << "\n**************************\n\033[0m\n"<< std::endl; \
} \
}