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

class Color {
public:
	constexpr Color(
		float r_ = 1.0f,
		float g_ = 1.0f,
		float b_ = 1.0f
	) : r(r_), g(g_), b(b_) {}

	float r, g, b;
protected:

private:

};

}

namespace Wrench::Colors {

constexpr Color White     = {1.0f,  1.0f,  1.0f };
constexpr Color Black     = {0.0f,  0.0f,  0.0f };
constexpr Color Gray      = {0.5f,  0.5f,  0.5f };
constexpr Color LightGray = {0.75f, 0.75f, 0.75f};
constexpr Color DarkGray  = {0.25f, 0.25f, 0.25f};
constexpr Color Red       = {1.0f,  0.0f,  0.0f };
constexpr Color Green     = {0.0f,  1.0f,  0.0f };
constexpr Color Blue      = {0.0f,  0.0f,  1.0f };
constexpr Color Yellow    = {1.0f,  1.0f,  0.0f };
constexpr Color Cyan      = {0.0f,  1.0f,  1.0f };
constexpr Color Magenta   = {1.0f,  0.0f,  1.0f };
constexpr Color Orange    = {1.0f,  0.5f,  0.0f };
constexpr Color Purple    = {0.5f,  0.0f,  0.5f };
constexpr Color Pink      = {1.0f,  0.4f,  0.7f };
constexpr Color Brown     = {0.4f,  0.26f, 0.13f};

}
