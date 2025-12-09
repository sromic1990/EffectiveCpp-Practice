//You are given this legacy header:
//
//#define MAX_LIGHTS 16
//#define PI 3.1415926535
//#define SHADOW_MAP_SIZE 2048
//
//
//✅ Your task:
//Refactor this using:
//
//constexpr
//
//Proper types
//
//No global namespace pollution
//
//👉 Bonus: Make SHADOW_MAP_SIZE usable for array sizes at compile time.

#pragma once

namespace GpuConfig
{
    inline constexpr int MaxLights = 16;
    inline constexpr double Pi = 3.1415926535;
    inline constexpr int ShadowMapSize = 2048;
}