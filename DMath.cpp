#include "DMath.h"

#include "MathDefines.h"

bool DMath::IsEqual(const double Lhs, const double Rhs) { return Lhs - Rhs <= DEPSILON; }
