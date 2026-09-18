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

#include "wrench/utils/vector/vec3.hpp"
#include "wrench/utils/vector/vec2.hpp"
#include <vector>

namespace Wrench::Renderer {

struct Vertex {
	Math::Vec3 position;
	Math::Vec3 normal;
	Math::Vec2 uv;
};

struct MeshData {
    std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

class Mesh {
public:
	Mesh(const MeshData& data);
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	void upload(const MeshData& data);
	void draw();

protected:

private:
	unsigned int indexCount_ = 0;

	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
	unsigned int ebo_ = 0;
};

}

namespace Wrench::Renderer::Primitives {

MeshData Quad();
MeshData Cube();
MeshData Sphere(unsigned int widthSegments = 32, unsigned int heightSegments = 16);
MeshData Cone(unsigned int radialSegments = 32);
MeshData Cylinder(unsigned int radialSegments = 32);

}
