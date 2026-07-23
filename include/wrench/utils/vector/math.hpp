/*
MIT License

Copyright (c) 2026 saintsHr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <cfloat>
#include <climits>

namespace Wrench::Math {

namespace Max {
    constexpr int                Int     = INT_MAX;
    constexpr unsigned int       UInt    = UINT_MAX;
    constexpr long               Long    = LONG_MAX;
    constexpr unsigned long      ULong   = ULONG_MAX;
    constexpr long long          LLong   = LLONG_MAX;
    constexpr unsigned long long ULLong  = ULLONG_MAX;
    constexpr short              Short   = SHRT_MAX;
    constexpr unsigned short     UShort  = USHRT_MAX;
    constexpr char               Char    = CHAR_MAX;
    constexpr unsigned char      UChar   = UCHAR_MAX;
    constexpr float              Float   = FLT_MAX;
    constexpr double             Double  = DBL_MAX;
    constexpr long double        LDouble = LDBL_MAX;
}

namespace Min {
    constexpr int                Int     = INT_MIN;
    constexpr unsigned int       UInt    = 0;
    constexpr long               Long    = LONG_MIN;
    constexpr unsigned long      ULong   = 0;
    constexpr long long          LLong   = LLONG_MIN;
    constexpr unsigned long long ULLong  = 0;
    constexpr short              Short   = SHRT_MIN;
    constexpr unsigned short     UShort  = 0;
    constexpr char               Char    = CHAR_MIN;
    constexpr unsigned char      UChar   = 0;
    constexpr float              Float   = -FLT_MIN;
    constexpr double             Double  = -DBL_MIN;
    constexpr long double        LDouble = -LDBL_MIN;
}

constexpr float PI = 3.1415926535f;

static inline float degreesToRadians(float degrees) {
    return degrees * Wrench::Math::PI / 180.0f;
}

static inline float radiansToDegrees(float radians) {
    return radians * 180.0f / Wrench::Math::PI;
}

}