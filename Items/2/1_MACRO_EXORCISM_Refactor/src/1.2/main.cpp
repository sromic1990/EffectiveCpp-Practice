/*Legacy:

#define MAX_BONES 128

class SkinnedMesh {
public:
    float boneMatrices[MAX_BONES][16];
};

🎯 Your task:
Remove macro
Keep compile-time array sizing
Prevent global pollution

Add:
static_assert(MAX_BONES % 16 == 0)*/

#include <cstddef>
#include <iostream>
#include <array>

struct Mat4
{
    std::array<float, 16> m;
};

class SkinnedMesh
{
	public:
        static constexpr std::size_t MaxBones = 128;
        static_assert(MaxBones % 16 == 0, "MaxBones must be a multiple of 16");
        std::array<Mat4, MaxBones> boneMatrices;
};

int main()
{
    SkinnedMesh mesh;
    std::cout << "SkinnedMesh created with MaxBones: " << mesh.boneMatrices.size() << std::endl;

    return 0;
}