/*
🎯 Goal
Create a header that:
- Uses no #define
- Exposes compile-time constants
- Is scoped (no global pollution)
- Is used in:
- static_assert
- std::array size
- template parameters
*/

#include "GpuLimits.h"
#include <array>
#include <iostream>

static_assert(GpuLimits::MaxLightsPerPass <= 128, "Too many lights for this GPU!");

std::array<int, GpuLimits::MaxTexturesPerMaterial> textureIds{};

template<int TileX, int TileY>
struct ComputeTile
{
    static constexpr int SizeX = TileX;
    static constexpr int SizeY = TileY;
};

using DefaultTile = ComputeTile<GpuLimits::ComputeTileSizeX, GpuLimits::ComputeTileSizeY>;

constexpr int MaxThreadsPerTile()
{
    return GpuLimits::ComputeTileSizeX * GpuLimits::ComputeTileSizeY;
}
static_assert(MaxThreadsPerTile() <= 1024, "Tile too BIG for this GPU");

int main()
{
    std::cout << "Max Textures per material: " << GpuLimits::MaxTexturesPerMaterial << "\n";
    std::cout << "Max lights per pass: " << GpuLimits::MaxLightsPerPass << "\n";
    std::cout << "Uniform buffer size (bytes): " << GpuLimits::MaxUniformBufferSize << "\n";
    std::cout << "Compute Tile: " << DefaultTile::SizeX << " x " << DefaultTile::SizeY << "\n";
    std::cout << "Texture array size: " << textureIds.size() << "\n";

    return 0;
}