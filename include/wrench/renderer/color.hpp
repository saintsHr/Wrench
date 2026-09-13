#pragma once

namespace Wrench::Renderer {

class Color {
public:
	Color(
		float r_ = 1.0f,
		float g_ = 1.0f,
		float b_ = 1.0f
	) : r(r_), g(g_), b(b_) {}

	float r, g, b;
protected:
	
private:
	
};

}