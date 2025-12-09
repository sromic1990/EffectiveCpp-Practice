#include "GpuConfig.h"
#include <array>
#include <iostream>

static_assert(GpuConfig::MaxLights <= 128, "Way too many lights for this demo!");

struct ShadowMap
{
    float data[GpuConfig::ShadowMapSize];
};

template <int NumLights>
struct LightArray
{
    std::array<int, NumLights> lights{};
};

void UseAddressOfConstant();

int main()
{
    LightArray<GpuConfig::MaxLights> lightArray;

    lightArray.lights[0] = 42;

    ShadowMap shadowMap;
    shadowMap.data[0] = 1.0f;

    std::cout << "MaxLights: " << GpuConfig::MaxLights << "\n";
    std::cout << "ShadowMapSize: " << GpuConfig::ShadowMapSize << "\n";
    std::cout << "shadowMap data: "<< shadowMap.data[0] << "\n";
    std::cout << "Pi: " << GpuConfig::Pi << "\n";

    UseAddressOfConstant();

    return 0;
}

void UseAddressOfConstant()
{
    const int* pml = &GpuConfig::MaxLights;
    std::cout << "Address of MaxLights: " << &pml << "\n";
}