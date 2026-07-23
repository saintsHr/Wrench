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

#include "wrench/utils/vec3.hpp"
#include "wrench/utils/math.hpp"
#include <cmath>

namespace Wrench {

class Mat4 {
public:
	Mat4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m_[i][j] = (i == j) ? 1.0f : 0.0f;
			}
		}
	};

	float& operator()(int col, int row) {
		return m_[col][row];
	}

	const float& operator()(int col, int row) const {
		return m_[col][row];
	}

	Mat4 operator*(const Mat4& other) const {
		Mat4 result;

		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				float cell = 0;

				for (int k = 0; k < 4; k++) {
					cell += this->operator()(k, row) * other(col, k);
				}

				result(col, row) = cell;
			}
		}

		return result;
	}

	static Mat4 identity() {
		Mat4 result;

		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				row == col ? result(col, row) = 1 : result(col, row) = 0;
			}
		}

		return result;
	}

	static Mat4 zeroed() {
		Mat4 result;

		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				result(col, row) = 0;
			}
		}

		return result;
	}

	static Mat4 translate(const Vec3& offset) {
		Mat4 result;

		result(3, 0) = offset.x;
		result(3, 1) = offset.y;
		result(3, 2) = offset.z;

		return result;
	}

	static Mat4 scale(const Vec3& size) {
		Mat4 result;

		result(0, 0) = size.x;
		result(1, 1) = size.y;
		result(2, 2) = size.z;

		return result;
	}

	static Mat4 rotateX(float degrees) {
		Mat4 result;

		float rad = Math::degreesToRadians(degrees);

		result(1, 1) = std::cos(rad);
		result(1, 2) = -std::sin(rad);
		result(2, 1) = std::sin(rad);
		result(2, 2) = std::cos(rad);

		return result;
	}

	static Mat4 rotateY(float degrees) {
		Mat4 result;

		float rad = Math::degreesToRadians(degrees);

		result(0, 0) = std::cos(rad);
		result(2, 0) = std::sin(rad);
		result(0, 2) = -std::sin(rad);
		result(2, 2) = std::cos(rad);

		return result;
	}

	static Mat4 rotateZ(float degrees) {
		Mat4 result;

		float rad = Math::degreesToRadians(degrees);

		result(0, 0) = std::cos(rad);
		result(1, 0) = -std::sin(rad);
		result(0, 1) = std::sin(rad);
		result(1, 1) = std::cos(rad);

		return result;
	}

	static Mat4 perspective(float fov, float aspect, float near, float far) {
		Mat4 result = Mat4::zeroed();

		float fov_tan_rad = std::tan(Math::degreesToRadians(fov) / 2);

		result(0, 0) = 1 / (aspect * fov_tan_rad);
		result(1, 1) = 1 / fov_tan_rad;
		result(2, 2) = -(far + near) / (far - near);
		result(2, 3) = -1;
		result(3, 2) = -(2 * far * near) / (far - near);

		return result;
	}

	static Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
		Mat4 result;

		Vec3 zAxis = (eye - target).normalize();
		Vec3 xAxis = Vec3::cross(up, zAxis).normalize();
		Vec3 yAxis = Vec3::cross(zAxis, xAxis);

		result(0,0) = xAxis.x;  result(1,0) = xAxis.y;  result(2,0) = xAxis.z;
		result(0,1) = yAxis.x;  result(1,1) = yAxis.y;  result(2,1) = yAxis.z;
		result(0,2) = zAxis.x;  result(1,2) = zAxis.y;  result(2,2) = zAxis.z;
		result(3,0) = -Vec3::dot(xAxis, eye);
		result(3,1) = -Vec3::dot(yAxis, eye);
		result(3,2) = -Vec3::dot(zAxis, eye);

		return result;
	}

	const float* data() const {
		return &m_[0][0];
	}
private:
	float m_[4][4];
};

}