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

#include <cmath>

namespace Wrench {

class Vec2 {
public:
	Vec2(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) {};

	float length() const {
		return std::sqrt(
			(x * x) +
			(y * y)
		);
	}

	Vec2 operator+(const Vec2& other) const {
		Vec2 result;

		result.x = x + other.x;
		result.y = y + other.y;

		return result;
	}

	Vec2 operator-(const Vec2& other) const {
		Vec2 result;

		result.x = x - other.x;
		result.y = y - other.y;

		return result;
	}

	Vec2 operator*(const Vec2& other) const {
		Vec2 result;

		result.x = x * other.x;
		result.y = y * other.y;

		return result;
	}

	Vec2 operator/(const Vec2& other) const {
		Vec2 result;

		result.x = x / other.x;
		result.y = y / other.y;

		return result;
	}

	Vec2 normalize() const {
		Vec2 result;
		
		float len = length();

		result.x = x / len;
		result.y = y / len;

		return result;
	}

	static float dot(const Vec2& a, const Vec2& b) {
		return (a.x * b.x) + (a.y * b.y);
	}

	float x, y;
};

}