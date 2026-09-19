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

#include "wrench/utils/vector/vec2.hpp"
#include "wrench/utils/vector/vec3.hpp"
#include <cmath>

namespace Wrench {

float Vec2::length() const {
	return std::sqrt(
		(x * x) +
		(y * y)
	);
}

Vec2 Vec2::operator+(const Vec2& other) const {
	Vec2 result;

	result.x = x + other.x;
	result.y = y + other.y;

	return result;
}

Vec2 Vec2::operator-(const Vec2& other) const {
	Vec2 result;

	result.x = x - other.x;
	result.y = y - other.y;

	return result;
}

Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}

Vec2 Vec2::operator*(const Vec2& other) const {
	Vec2 result;

	result.x = x * other.x;
	result.y = y * other.y;

	return result;
}

Vec2 Vec2::operator/(const Vec2& other) const {
	Vec2 result;

	result.x = x / other.x;
	result.y = y / other.y;

	return result;
}

Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;

    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;

    return *this;
}

Vec2& Vec2::operator*=(const Vec2& other) {
    x *= other.x;
    y *= other.y;

    return *this;
}

Vec2& Vec2::operator/=(const Vec2& other) {
    x /= other.x;
    y /= other.y;

    return *this;
}

Vec2 Vec2::operator*(float scalar) const {
    Vec2 result;

    result.x = x * scalar;
	result.y = y * scalar;

    return result;
}

Vec2 Vec2::operator/(float scalar) const {
    Vec2 result;

    result.x = x / scalar;
	result.y = y / scalar;

    return result;
}

Vec2 operator*(float scalar, const Vec2& v) {
    return v * scalar;
}

Vec2 operator/(float scalar, const Vec2& v) {
    return v / scalar;
}

Vec2 Vec2::normalize() const {
	Vec2 result;

	float len = length();

	result.x = x / len;
	result.y = y / len;

	return result;
}

float Vec2::dot(const Vec2& a, const Vec2& b) {
	return (a.x * b.x) + (a.y * b.y);
}

Vec3 Vec2::toVec3(float z) const {
    return Vec3(y, x, z);
}

}
