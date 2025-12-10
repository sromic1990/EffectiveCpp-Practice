/*
Start from this legacy style:
#define RENDER_SHADOWS     1
#define RENDER_REFLECTIONS 2
#define RENDER_SKYBOX      4

Your tasks
- Replace those macros with a strongly typed enum:
enum class RenderFlags : unsigned int
{
    None        = 0,
    Shadows     = 1 << 0,
    Reflections = 1 << 1,
    Skybox      = 1 << 2,
};


- Implement bitwise operators for RenderFlags:
RenderFlags operator|(RenderFlags a, RenderFlags b);
RenderFlags operator&(RenderFlags a, RenderFlags b);
RenderFlags& operator|=(RenderFlags& a, RenderFlags b);


- Use std::underlying_type_t<RenderFlags> inside to convert to/from the underlying unsigned int.
Implement:
bool HasFlag(RenderFlags value, RenderFlags flag);
Something like return (value & flag) == flag;

In main():
Create:
RenderFlags flags = RenderFlags::Shadows | RenderFlags::Skybox;

Print (with std::cout):
HasFlag(flags, RenderFlags::Shadows) → should be true
HasFlag(flags, RenderFlags::Reflections) → should be false
*/

#include <iostream>
#include <ostream>
#include <type_traits>

//Legacy style
#define RENDER_SHADOWS      1
#define RENDER_REFLECTIONS  2
#define RENDER_SKYBOX       4

namespace Render
{
    enum class Flags : unsigned int
    {
        None = 0,
        Shadows =  1 << 0,
        Reflections = 1 << 1,
        Skybox = 1 << 2,
    };

    using FlagsUT = std::underlying_type_t<Flags>;
    constexpr Flags operator|(Flags a, Flags b)
    {
        return static_cast<Flags>(
            static_cast<FlagsUT>(a) |
            static_cast<FlagsUT>(b)
        );
    }

    constexpr Flags operator&(Flags a, Flags b)
    {
        return static_cast<Flags>(
            static_cast<FlagsUT>(a) &
            static_cast<FlagsUT>(b)
        );
    }

    constexpr Flags& operator|=(Flags& a, Flags b)
    {
        a = a | b;
        return a;
    }

    constexpr Flags& operator&=(Flags& a, Flags b)
    {
        a = a & b;
        return a;
    }

    [[nodisregard]] constexpr bool HasFlag(Flags value, Flags flag)
    {
        return (value & flag) == flag;
    }

    std::ostream& operator<<(std::ostream& os, Flags f)
    {
        switch (f)
        {
            case Render::Flags::Shadows: return os << "Shadows";
            case Render::Flags::Reflections: return os << "Reflection";
            case Render::Flags::Skybox: return os << "Skybox";
            default: return os << "Multiple/Unknown";
        }
    }
}

int main()
{
    int oldFlags = RENDER_SHADOWS | RENDER_SKYBOX;

    bool oldHasShadows     = (oldFlags & RENDER_SHADOWS) != 0;
    bool oldHasReflections = (oldFlags & RENDER_REFLECTIONS) != 0;

    bool oldHasGarbage = (oldFlags & 123456) != 0;   // meaningless
    oldFlags |= 999;                                 // destroys flag set

    std::cout << "OLD FLAGS:\n";
    std::cout << "  Has Shadows:      " << oldHasShadows << "\n";
    std::cout << "  Has Reflections: " << oldHasReflections << "\n";
    std::cout << "  After |= 999:    " << oldFlags << "\n";

    Render::Flags flags = Render::Flags::Shadows | Render::Flags::Skybox;

    std::cout << std::boolalpha;
    std::cout << "Has Shadows? " << Render::HasFlag(flags, Render::Flags::Shadows) << "\n";
    std::cout << "Has Reflections? " << Render::HasFlag(flags, Render::Flags::Reflections) << "\n";

    return 0;
}

#undef RENDER_SHADOWS
#undef RENDER_REFLECTIONS
#undef RENDER_SKYBOX 