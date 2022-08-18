#pragma once
#include <cmath>
#include <corecrt_math_defines.h>

// Credit of Weather Vane, for use in math_helper::sqrt() https://stackoverflow.com/questions/29018864/any-way-to-obtain-square-root-of-a-number-without-using-math-h-and-sqrt
//#define MINDIFF 2.2250738585072014e-308   // smallest positive float
#define MINDIFF 2.25e-308                   // use for convergence check
constexpr float DEPSILON = 0.001;
#define PI M_PI
#define DEG2_RAD(deg) deg * (PI / 180)
#define IS_LESS_THAN_EQUAL_ERROR(a) (std::abs(a) <= DEPSILON)
#define IS_RELATIVELY_EQUAL(a, b) (std::abs((a) - (b)) <= DEPSILON)
