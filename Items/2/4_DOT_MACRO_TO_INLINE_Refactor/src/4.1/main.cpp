/*
Goal: stop using a macro for a math op that touches literally everything in graphics.

Legacy macro (you start with this):
#define DOT(a, b) (a.x * b.x + a.y * b.y + a.z * b.z)

Your tasks
- Define a simple vector type:
struct Vec3
{
    float x, y, z;
};

- Demo the macro (and why it’s dangerous):

- In main():
Create two Vec3:
Vec3 a{1.0f, 2.0f, 3.0f};
Vec3 b{4.0f, 5.0f, 6.0f};

- Compute:
float d = DOT(a, b);
std::cout << "Macro DOT result: " << d << '\n';

- Add a comment explaining how this macro could break if you pass expressions like DOT(a, {1,2,3}) or something involving side effects.

- Replace macro with a safe function:
constexpr inline float Dot(const Vec3& a, const Vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

- Call it in main() and print:
float dFunc = Dot(a, b);

- Generalize to templated vector:
Define:
template<typename T>
struct TVec3
{
    T x, y, z;
};

template<typename T>
constexpr inline T Dot(const TVec3<T>& a, const TVec3<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

In main():
Make TVec3<float> and TVec3<double>:

TVec3<float>  fa{1.0f, 2.0f, 3.0f};
TVec3<float>  fb{4.0f, 5.0f, 6.0f};

TVec3<double> da{1.0, 2.0, 3.0};
TVec3<double> db{4.0, 5.0, 6.0};

- Compute and print:
auto fd = Dot(fa, fb);
auto dd = Dot(da, db);

- Clean up the macro:
After you’re done demonstrating it:
#undef DOT
*/

#include <iostream>

#define DOT(a,b) (a.x * b.x + a.y * b.y + a.z * b.z)


namespace Math
{
    struct Vec3
    {
        float x, y, z;
    };

    std::ostream& operator<<(std::ostream& os, const Vec3& v)
    {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }

	constexpr inline float Dot(const Vec3& a, const Vec3& b)
	{
        return a.x * b.x + a.y * b.y + a.z * b.z;
	}

    template<typename T>
    struct TVec3
    {
        T x, y, z;
    };

    template<typename T>
    constexpr inline T Dot(const TVec3<T>& a, const TVec3<T>& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const TVec3<T>& v)
    {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }
}

int main()
{
    Math::Vec3 a{1.0f, 2.0f, 3.0f};
    Math::Vec3 b{4.0f, 5.0f, 6.0f};

    float macroDot = DOT(a, b);
    std::cout << "MACRO DOT result: " << macroDot << "\n";

    // Won't work: auto sideEffectDot = DOT(a, { 1.0f, 2.0f, 3.0f });
	// This fails because the macro blindly pastes `.x/.y/.z` onto `{...}`, which is an
	// initializer list, not a Vec3. Macros don't understand types or create real objects.
    // Example of how a macro like DOT could be dangerous with side effects:
	// Math::Vec3 c{1.0f, 2.0f, 3.0f};
	// Math::Vec3 d{4.0f, 5.0f, 6.0f};
	//
	// auto macroDotSideEffect = DOT(c, d);     // OK
	// auto macroDotSideEffect2 = DOT(c, d);    // still OK
	//
	// But if DOT was something like SQR(x) x*x, then SQR(i++) would increment i twice.

    float dFunc = Math::Dot(a, {1.0f, 2.0f, 3.0f});
    std::cout << "Function Dot: " << dFunc << "\n";

    dFunc = Math::Dot(a, b);
    std::cout << "Function Dot with : " << a << " and " << b << " is " << dFunc << "\n";

    Math::TVec3<float>  fa{ 1.0f, 2.0f, 3.0f };
    Math::TVec3<float>  fb{ 4.0f, 5.0f, 6.0f };

    Math::TVec3<double> da{ 1.0, 2.0, 3.0 };
    Math::TVec3<double> db{ 4.0, 5.0, 6.0 };

    auto fd = Math::Dot(fa, fb);
    auto dd = Math::Dot(da, db);

    std::cout << "Template Dot of " << fa << " and " << fb << " : " << fd << "\n";
    std::cout << "Template Dot of " << da << " and " << db << " : " << dd << "\n";

    return 0;
}

#undef DOT