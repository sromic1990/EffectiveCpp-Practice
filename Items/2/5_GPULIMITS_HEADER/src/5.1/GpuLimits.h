#pragma once

namespace GpuLimits
{
    inline constexpr int MaxTexturesPerMaterial = 16;
    inline constexpr int MaxLightsPerPass = 64;
    inline constexpr int MaxUniformBufferSize = 16 * 1024; //bytes
    inline constexpr int ComputeTileSizeX = 8;
    inline constexpr int ComputeTileSizeY = 8;
}