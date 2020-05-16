#pragma once
#include <cmath>

inline bool areDoubleSame(double dFirstVal, double dSecondVal, double epsilon)
{
   return std::fabs(dFirstVal - dSecondVal) < epsilon;
}
