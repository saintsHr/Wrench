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

#include "wrench/utils/vector/mat4.hpp"
#include "wrench/utils/vector/math.hpp"
#include "wrench/utils/vector/vec3.hpp"
#include <cmath>
namespace Wrench::Math {

class Quaternion {
public:
	Quaternion(
		float x_ = 0.0f,
		float y_ = 0.0f,
		float z_ = 0.0f,
		float w_ = 1.0f
	) : x(x_), y(y_), z(z_), w(w_) {};

	Quaternion operator*(const Quaternion& other) const {
		Quaternion result;

		Quaternion a = *this;
		Quaternion b = other;

		result.x = (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y);
		result.y = (a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x);
		result.z = (a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w);
		result.w = (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z);

		return result;
	}

	static Quaternion fromAxisAngle(const Vec3& axis, float degrees) {
		Quaternion result;

		Vec3 normalizedAxis = axis.normalize();
		float radians = Math::degreesToRadians(degrees);

		float sinHalfRad = std::sin(radians / 2);
		float cosHalfRad = std::cos(radians / 2);

		result.x = normalizedAxis.x * sinHalfRad;
		result.y = normalizedAxis.y * sinHalfRad;
		result.z = normalizedAxis.z * sinHalfRad;
		result.w = cosHalfRad;

		return result;
	}

	Mat4 toMat4() const {
		Mat4 result = Mat4::identity();

		result(0,0) = 1 - 2*(y*y + z*z);
		result(1,0) = 2*(x*y - z*w);
		result(2,0) = 2*(x*z + y*w);
		result(0,1) = 2*(x*y + z*w);
		result(1,1) = 1 - 2*(x*x + z*z);
		result(2,1) = 2*(y*z - x*w);
		result(0,2) = 2*(x*z - y*w);
		result(1,2) = 2*(y*z + x*w);
		result(2,2) = 1 - 2*(x*x + y*y);

		return result;
	}

	float x, y, z, w;
private:

};

}