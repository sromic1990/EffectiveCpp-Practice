/*
Broken Square
Legacy:
#define SQR(x) x * x

Usage:

int a = 5;
int b = SQR(a + 1);

🎯 Your task:
Print the actual wrong result
Explain in a comment why
Fix using:
constexpr
template

Show the correct result
*/

#include <iostream>

//Wrong implementation
#define SQR(x) x * x

namespace SqrMacroRefactor
{
    template <typename T>
    constexpr inline T Sqr(T x)
    {
        return x * x;
    }
}

int main()
{
    int a = 5;
    int b = SQR(a + 1);
    std::cout << "Broken macro result: " << b << std::endl;
    std::cout << "Explanation: The macro expands to a + 1 * a + 1, which is interpreted as a + (1 * a) + 1 due to operator precedence, resulting in 5 + 5 + 1 = 11 instead of the expected (5 + 1) * (5 + 1) = 36." << std::endl;
#undef

    b = SqrMacroRefactor::Sqr(a + 1);
    std::cout << "Fixed constexpr result: " << b << std::endl;

	float f = 5.0f;
	float fSqr = SqrMacroRefactor::Sqr(f + 1.0f);
	std::cout << "Fixed template result (float): " << fSqr << std::endl;

    return 0;
}