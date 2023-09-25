#include <iostream>
#include "CD3D12App.h"

int main()
{
    CD3D12App* app = new CD3D12App();

    if (!app->InitD3D()) {
        std::cout << "Init of D3D is not sucessful \n";
        return -1;
    }

    std::cout << "EngineInit\n";

    return 0;
}