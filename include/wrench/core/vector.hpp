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

namespace Wrench {

class Vec2 {
public:
	Vec2(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) {};
	float x, y;
};

class Vec3 {
public:
	Vec3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f) : x(x_), y(y_), z(z_) {};
	float x, y, z;
};

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

	const float* data() const {
		return &m_[0][0];
	}
private:
	float m_[4][4];
};

}