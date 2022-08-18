#include "DMath.h"

#include "MathDefines.h"

bool DMath::IsEqual(const float Lhs, const float Rhs) { return Lhs - Rhs <= DEPSILON; }
