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

	Vec3 operator*(const Vec3& v) const {
	    Vec3 q(x, y, z);

	    Vec3 t = 2.0f * q.cross(v);

	    return v + w * t + q.cross(t);
	}

	static Quaternion identity() {
		Quaternion result;

		result.x = 0.0f;
		result.y = 0.0f;
		result.z = 0.0f;
		result.w = 1.0f;

		return result;
	}

	Quaternion normalized() const {
		Quaternion result = identity();

	    float len = lenght();
	    if (len == 0.0f) return Quaternion::identity();

	    result.x = x / len;
	    result.y = y / len;
	    result.z = z / len;
	    result.w = w / len;

	    return result;
	}

	void normalize() {
	    float len = lenght();
	    if (len == 0.0f) return;

	    x /= len;
	    y /= len;
	    z /= len;
	    w /= len;
	}

	float lenght() const {
		return std::sqrt(x*x + y*y + z*z + w*w);
	}

	Quaternion operator*(const Quaternion& other) const {
		Quaternion result = identity();

		Quaternion a = *this;
		Quaternion b = other;

		result.x = (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y);
		result.y = (a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x);
		result.z = (a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w);
		result.w = (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z);

		return result;
	}

	static Quaternion fromAxisAngle(const Vec3& axis, float degrees) {
		Quaternion result = identity();

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

	Quaternion fromEuler(const Vec3& euler) {
		Quaternion result = identity();

		result = (
    		Quaternion::fromAxisAngle(Vec3(1,0,0), euler.x) *
    		Quaternion::fromAxisAngle(Vec3(0,1,0), euler.y) *
			Quaternion::fromAxisAngle(Vec3(0,0,1), euler.z)
		);

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

	static Quaternion lookRotation(const Vec3& forward, const Vec3& up)	{
	    Vec3 f = forward.normalize();
	    Vec3 r = Vec3::cross(up, f).normalize();
	    Vec3 u = Vec3::cross(f, r);

	    Quaternion result;

	    float trace = r.x + u.y + f.z;

	    if (trace > 0) {
	        float s = std::sqrt(trace + 1.0f) * 2.0f;

	        result.w = 0.25f * s;
	        result.x = (u.z - f.y) / s;
	        result.y = (f.x - r.z) / s;
	        result.z = (r.y - u.x) / s;
	    } else if (r.x > u.y && r.x > f.z) {
	        float s = std::sqrt(1.0f + r.x - u.y - f.z) * 2.0f;

	        result.w = (u.z - f.y) / s;
	        result.x = 0.25f * s;
	        result.y = (u.x + r.y) / s;
	        result.z = (f.x + r.z) / s;
	    } else if (u.y > f.z) {
	        float s = std::sqrt(1.0f + u.y - r.x - f.z) * 2.0f;

	        result.w = (f.x - r.z) / s;
	        result.x = (u.x + r.y) / s;
	        result.y = 0.25f * s;
	        result.z = (f.y + u.z) / s;
	    } else {
	        float s = std::sqrt(1.0f + f.z - r.x - u.y) * 2.0f;

	        result.w = (r.y - u.x) / s;
	        result.x = (f.x + r.z) / s;
	        result.y = (f.y + u.z) / s;
	        result.z = 0.25f * s;
	    }

	    return result.normalized();
	}

	float x, y, z, w;
private:

};

}