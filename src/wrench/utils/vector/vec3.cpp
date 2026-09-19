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

#include "wrench/utils/vector/vec3.hpp"
#include "wrench/utils/vector/vec2.hpp"
#include <cmath>

namespace Wrench {

Vec3 Vec3::operator+(const Vec3& other) const {
	Vec3 result;

	result.x = x + other.x;
	result.y = y + other.y;
	result.z = z + other.z;

	return result;
}

Vec3 Vec3::operator-(const Vec3& other) const {
	Vec3 result;

	result.x = x - other.x;
	result.y = y - other.y;
	result.z = z - other.z;

	return result;
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator*(const Vec3& other) const {
	Vec3 result;

	result.x = x * other.x;
	result.y = y * other.y;
	result.z = z * other.z;

	return result;
}

Vec3 Vec3::operator/(const Vec3& other) const {
	Vec3 result;

	result.x = x / other.x;
	result.y = y / other.y;
	result.z = z / other.z;

	return result;
}

Vec3& Vec3::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vec3& Vec3::operator*=(const Vec3& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

Vec3& Vec3::operator/=(const Vec3& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;

    return *this;
}

Vec3 Vec3::operator*(float scalar) const {
    Vec3 result;

    result.x = x * scalar;
	result.y = y * scalar;
	result.z = z * scalar;

    return result;
}

Vec3 Vec3::operator/(float scalar) const {
    Vec3 result;

    result.x = x / scalar;
	result.y = y / scalar;
	result.z = z / scalar;

    return result;
}

Vec3 operator*(float scalar, const Vec3& v) {
    return v * scalar;
}

Vec3 operator/(float scalar, const Vec3& v) {
    return v / scalar;
}

float Vec3::length() const {
	return std::sqrt(
		(x * x) +
		(y * y) +
		(z * z)
	);
}

Vec3 Vec3::normalize() const {
	Vec3 result;

	float len = length();

	result.x = x / len;
	result.y = y / len;
	result.z = z / len;

	return result;
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
	Vec3 result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);

	return result;
}

Vec3 Vec3::cross(const Vec3& other) const {
    Vec3 result;

    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;

    return result;
}

float Vec3::dot(const Vec3& a, const Vec3& b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec2 Vec3::toVec2() const {
    return Vec2(x, y);
}

}
