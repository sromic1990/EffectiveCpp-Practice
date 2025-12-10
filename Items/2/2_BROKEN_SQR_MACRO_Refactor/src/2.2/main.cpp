/*
You must reuse this macro:
#define CLAMP01(x) (x < 0 ? 0 : (x > 1 ? 1 : x))

🎯 Tasks:
Use it like this:

float t = 0.9f;
float y = CLAMP01(t++);

Print:
initial t (before macro)
final t (after macro call)
y

In a comment, explain:
- How many times t is evaluated
- Why that’s a problem
- Replace CLAMP01 with a safe version:
    constexpr inline float Clamp01(float x);
Bonus: templated version that works with float and double
Show that the fixed version:
- Produces the expected result
- Only increments t once
*/

#include <iostream>

#define CLAMP01(x) (x < 0 ? 0 : (x > 1 ? 1 : x))

namespace SafeClamp
{
	constexpr inline float Clamp01(float x)
	{
		return (x < 0) ? 0 : (x > 1) ? 1 : x;
	}

    template<typename T>
    constexpr inline T Clamp01T(T x)
    {
        const T zero = static_cast<T>(0);
        const T one = static_cast<T>(1);
        return (x < zero) ? zero : (x > one) ? one : x;
    }
}

int main()
{
    float t = 0.9f;
    float tBefore = t;
    float y = CLAMP01(t++);

    std::cout << "Initial t (before macro): " << tBefore << std::endl;
    std::cout << "Final t (after macro call): " << t << std::endl;
    std::cout << "y: " << y << std::endl;

    // Explanation:
    // CLAMP01(x) uses 'x' up to three times in its expansion.
	// With side-effectful arguments like t++, that can mean multiple increments.
	// In this particular call, 't' is incremented twice, but the key bug is that
	// the macro may evaluate its argument more than once.


    float safeT = 0.9f;
	float safeY = SafeClamp::Clamp01(safeT++);
	std::cout << "Using safe Clamp01: t: " << safeT << " y :" << safeY << std::endl;

    float  sf = 1.2f;
    double sd = -0.5;

    auto cf = SafeClamp::Clamp01T(sf);
    auto cd = SafeClamp::Clamp01T(sd);
	std::cout << "Templated Clamp01T with float: input: " << sf << " output: " << cf << std::endl;
	std::cout << "Templated Clamp01T with double: input: " << sd << " output: " << cd << std::endl;

    return 0;
}
#undef CLAMP01