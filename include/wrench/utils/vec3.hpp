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

class Vec3 {
public:
	Vec3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f) : x(x_), y(y_), z(z_) {};
	
	Vec3 operator+(const Vec3& other) const {
		Vec3 result;

		result.x = x + other.x;
		result.y = y + other.y;
		result.z = z + other.z;

		return result;
	}

	Vec3 operator-(const Vec3& other) const {
		Vec3 result;

		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;

		return result;
	}

	Vec3 operator*(const Vec3& other) const {
		Vec3 result;

		result.x = x * other.x;
		result.y = y * other.y;
		result.z = z * other.z;

		return result;
	}

	Vec3 operator/(const Vec3& other) const {
		Vec3 result;

		result.x = x / other.x;
		result.y = y / other.y;
		result.z = z / other.z;

		return result;
	}

	float length() const {
		return std::sqrt(
			(x * x) +
			(y * y) +
			(z * z)
		);
	}

	Vec3 normalize() const {
		Vec3 result;

		float len = length();

		result.x = x / len;
		result.y = y / len;
		result.z = z / len;

		return result;
	}

	static Vec3 cross(const Vec3& a, const Vec3& b) {
		Vec3 result;

		result.x = (a.y * b.z) - (a.z * b.y);
		result.y = (a.z * b.x) - (a.x * b.z);
		result.z = (a.x * b.y) - (a.y * b.x);

		return result;
	}

	static float dot(const Vec3& a, const Vec3& b) {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	float x, y, z;
};

}