#pragma once

#include "wrench/utils/vector.hpp"
#include <vector>

namespace Wrench {

struct Vertex {
	Wrench::Vec3 position;
	Wrench::Vec3 normal;
	Wrench::Vec2 uv;
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
private:
	unsigned int indexCount_ = 0;

	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
	unsigned int ebo_ = 0;
};

}