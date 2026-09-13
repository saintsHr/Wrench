#pragma once

#include "wrench/utils/vector/vec3.hpp"
#include "wrench/utils/vector/vec2.hpp"
#include <vector>

namespace Wrench::Renderer {

struct Vertex {
	Math::Vec3 position;
	Math::Vec3 normal;
	Math::Vec2 uv;
};

class Mesh {
public:
	Mesh(
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices
	);
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	void upload(
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices
	);

	void draw();

protected:
	
private:
	unsigned int indexCount_ = 0;

	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
	unsigned int ebo_ = 0;
};

}