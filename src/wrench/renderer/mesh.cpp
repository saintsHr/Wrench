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

#include "wrench/renderer/mesh.hpp"
#include "wrench/utils/log.hpp"
#include "wrench/utils/vector/math.hpp"
#include <glad.h>

namespace Wrench::Renderer {

Mesh::Mesh(const MeshData& data) {
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	glCreateBuffers(1, &ebo_);

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Creating mesh (VAO: {}, VBO: {}, EBO: {}).",
		vao_,
		vbo_,
		ebo_
	);

	upload(data);

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Mesh created with {} vertices and {} indices.",
		data.vertices.size(),
		data.indices.size()
	);
}

Mesh::~Mesh() {
	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Destroying mesh (VAO: {}, VBO: {}, EBO: {}).",
		vao_,
		vbo_,
		ebo_
	);

	glDeleteBuffers(1, &ebo_);
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);

	ebo_ = 0;
	vbo_ = 0;
	vao_ = 0;
}

Mesh::Mesh(Mesh&& other) noexcept {
	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Moving mesh handles from VAO: {}, VBO: {}, EBO: {}.",
		other.vao_,
		other.vbo_,
		other.ebo_
	);

	this->ebo_ = other.ebo_;
	this->vbo_ = other.vbo_;
	this->vao_ = other.vao_;

	other.ebo_ = 0;
	other.vbo_ = 0;
	other.vao_ = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
	if (this == &other) return *this;

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Moving mesh handles (VAO: {}, VBO: {}, EBO: {}).",
		other.vao_,
		other.vbo_,
		other.ebo_
	);

 	glDeleteBuffers(1, &this->ebo_);
	glDeleteBuffers(1, &this->vbo_);
	glDeleteVertexArrays(1, &this->vao_);

	this->ebo_ = other.ebo_;
	this->vbo_ = other.vbo_;
	this->vao_ = other.vao_;

	other.ebo_ = 0;
	other.vbo_ = 0;
	other.vao_ = 0;

	return *this;
}

void Mesh::upload(const MeshData& data) {
	indexCount_ = static_cast<unsigned int>(data.indices.size());

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Uploading mesh data (vertices {}, indices: {}).",
		data.vertices.size(),
		data.indices.size()
	);

	glNamedBufferData(
		vbo_,
		static_cast<GLsizeiptr>(data.vertices.size() * sizeof(Vertex)),
		data.vertices.data(), GL_STATIC_DRAW
	);

	glNamedBufferData(
		ebo_,
		indexCount_ * sizeof(unsigned int),
		data.indices.data(), GL_STATIC_DRAW
	);

	glVertexArrayVertexBuffer(
		vao_, 0, vbo_, 0,
		sizeof(Vertex)
	);

	glVertexArrayElementBuffer(vao_, ebo_);

	glEnableVertexArrayAttrib(vao_, 0);
	glVertexArrayAttribFormat(
		vao_, 0, 3,
		GL_FLOAT, GL_FALSE,
		offsetof(Vertex, position)
	);
	glVertexArrayAttribBinding(vao_, 0, 0);

	glEnableVertexArrayAttrib(vao_, 1);
	glVertexArrayAttribFormat(
		vao_, 1, 3,
		GL_FLOAT, GL_FALSE,
		offsetof(Vertex, normal)
	);
	glVertexArrayAttribBinding(vao_, 1, 0);

	glEnableVertexArrayAttrib(vao_, 2);
	glVertexArrayAttribFormat(
		vao_, 2, 2,
		GL_FLOAT, GL_FALSE,
		offsetof(Vertex, uv)
	);
	glVertexArrayAttribBinding(vao_, 2, 0);

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Mesh upload complete (VAO: {}, index count: {}).",
		vao_,
		indexCount_
	);
}

void Mesh::draw() {
	glBindVertexArray(vao_);
	glDrawElements(
		GL_TRIANGLES,
		static_cast<GLsizei>(indexCount_),
		GL_UNSIGNED_INT,
		nullptr
	);
}

}

namespace Wrench::Renderer::Primitives {

MeshData Quad() {
    MeshData data;

    data.vertices = {
        Vertex({-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {-1.0f, -1.0f}),
        Vertex({ 0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, -1.0f}),
        Vertex({ 0.5f, 0.0f,  0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 1.0f}),
        Vertex({-0.5f, 0.0f,  0.5f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 1.0f}),
    };

    data.indices = {
        0, 1, 2,
        2, 3, 0,
    };

    return data;
}

MeshData Cube() {
	MeshData data;

	data.vertices = {
		Vertex({0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}),
		Vertex({0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}),
		Vertex({0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}),
		Vertex({0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}),

		Vertex({-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}),
		Vertex({-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}),
		Vertex({-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}),
		Vertex({-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}),

		Vertex({-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}),

		Vertex({-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}),
		Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}),
		Vertex({ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}),
		Vertex({ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}),

		Vertex({ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}),
		Vertex({ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}),
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}),

		Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}),
		Vertex({ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}),
	};

	data.indices.reserve(36);
	for (unsigned int face = 0; face < 6; ++face) {
		unsigned int base = face * 4;

		data.indices.push_back(base + 0);
		data.indices.push_back(base + 1);
		data.indices.push_back(base + 2);

		data.indices.push_back(base + 2);
		data.indices.push_back(base + 3);
		data.indices.push_back(base + 0);
	}

	return data;
}

MeshData Sphere(unsigned int widthSegments, unsigned int heightSegments) {
	MeshData data;

	const float radius = 0.5f;

	for (unsigned int i = 0; i <= heightSegments; ++i) {
		float stackAngle = Math::PI / 2.0f - static_cast<float>(i) * (Math::PI / static_cast<float>(heightSegments));
		float xy = radius * std::cos(stackAngle);
		float y = radius * std::sin(stackAngle);

		for (unsigned int j = 0; j <= widthSegments; ++j) {
			float sectorAngle = static_cast<float>(j) * (2.0f * Math::PI / static_cast<float>(widthSegments));

			float x = xy * std::cos(sectorAngle);
			float z = xy * std::sin(sectorAngle);

			Math::Vec3 normal(x / radius, y / radius, z / radius);
			float u = static_cast<float>(j) / static_cast<float>(widthSegments);
			float v = static_cast<float>(i) / static_cast<float>(heightSegments);

			data.vertices.push_back(Vertex({x, y, z}, normal, {u, v}));
		}
	}

	for (unsigned int i = 0; i < heightSegments; ++i) {
		unsigned int k1 = i * (widthSegments + 1);
		unsigned int k2 = k1 + widthSegments + 1;

		for (unsigned int j = 0; j < widthSegments; ++j, ++k1, ++k2) {
			if (i != 0) {
				data.indices.push_back(k1);
				data.indices.push_back(k2);
				data.indices.push_back(k1 + 1);
			}
			if (i != heightSegments - 1) {
				data.indices.push_back(k1 + 1);
				data.indices.push_back(k2);
				data.indices.push_back(k2 + 1);
			}
		}
	}

	return data;
}

MeshData Cone(unsigned int radialSegments) {
	MeshData data;

	const float radius = 0.5f;
	const float height = 1.0f;
	const float halfHeight = height / 2.0f;

	for (unsigned int j = 0; j <= radialSegments; ++j) {
		float angle = static_cast<float>(j) * (2.0f * Math::PI / static_cast<float>(radialSegments));
		float x = std::cos(angle);
		float z = std::sin(angle);
		float u = static_cast<float>(j) / static_cast<float>(radialSegments);

		Math::Vec3 normal(x, radius / height, z);
		float len = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal = Math::Vec3(normal.x / len, normal.y / len, normal.z / len);

		data.vertices.push_back(Vertex({x * radius, -halfHeight, z * radius}, normal, {u, 0.0f}));
	}

	for (unsigned int j = 0; j <= radialSegments; ++j) {
		float angle = (static_cast<float>(j) + 0.5f) * (2.0f * Math::PI / static_cast<float>(radialSegments));
		float x = std::cos(angle);
		float z = std::sin(angle);

		Math::Vec3 normal(x, radius / height, z);
		float len = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal = Math::Vec3(normal.x / len, normal.y / len, normal.z / len);

		float u = static_cast<float>(j) / static_cast<float>(radialSegments);
		data.vertices.push_back(Vertex({0.0f, halfHeight, 0.0f}, normal, {u, 1.0f}));
	}

	unsigned int apexStart = radialSegments + 1;
	for (unsigned int j = 0; j < radialSegments; ++j) {
		data.indices.push_back(j);
		data.indices.push_back(j + 1);
		data.indices.push_back(apexStart + j);
	}

	unsigned int baseCenterIndex = static_cast<unsigned int>(data.vertices.size());
	data.vertices.push_back(Vertex({0.0f, -halfHeight, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.5f, 0.5f}));

	unsigned int baseRingStart = static_cast<unsigned int>(data.vertices.size());
	for (unsigned int j = 0; j <= radialSegments; ++j) {
		float angle = static_cast<float>(j) * (2.0f * Math::PI / static_cast<float>(radialSegments));
		float x = std::cos(angle);
		float z = std::sin(angle);

		data.vertices.push_back(Vertex(
			{x * radius, -halfHeight, z * radius},
			{0.0f, -1.0f, 0.0f},
			{x * 0.5f + 0.5f, z * 0.5f + 0.5f}
		));
	}

	for (unsigned int j = 0; j < radialSegments; ++j) {
		data.indices.push_back(baseCenterIndex);
		data.indices.push_back(baseRingStart + j + 1);
		data.indices.push_back(baseRingStart + j);
	}

	return data;
}

MeshData Cylinder(unsigned int radialSegments) {
	MeshData data;

	const float radius = 0.5f;
	const float height = 1.0f;
	const float halfH = height / 2.0f;

	for (unsigned int j = 0; j <= radialSegments; ++j) {
		float angle = static_cast<float>(j) * (2.0f * Math::PI / static_cast<float>(radialSegments));
		float x = std::cos(angle);
		float z = std::sin(angle);
		float u = static_cast<float>(j) / static_cast<float>(radialSegments);

		data.vertices.push_back(Vertex({x * radius, halfH, z * radius}, {x, 0.0f, z}, {u, 1.0f}));
		data.vertices.push_back(Vertex({x * radius, -halfH, z * radius}, {x, 0.0f, z}, {u, 0.0f}));
	}

	for (unsigned int j = 0; j < radialSegments; ++j) {
		unsigned int top0 = j * 2;
		unsigned int bottom0 = top0 + 1;
		unsigned int top1 = (j + 1) * 2;
		unsigned int bottom1 = top1 + 1;

		data.indices.push_back(top0);
		data.indices.push_back(bottom0);
		data.indices.push_back(top1);

		data.indices.push_back(top1);
		data.indices.push_back(bottom0);
		data.indices.push_back(bottom1);
	}

	unsigned int topCenterIndex = static_cast<unsigned int>(data.vertices.size());
	data.vertices.push_back(Vertex({0.0f, halfH, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 0.5f}));

	unsigned int topRingStart = static_cast<unsigned int>(data.vertices.size());
	for (unsigned int j = 0; j <= radialSegments; ++j) {
		float angle = static_cast<float>(j) * (2.0f * Math::PI / static_cast<float>(radialSegments));
		float x = std::cos(angle);
		float z = std::sin(angle);

		data.vertices.push_back(Vertex(
			{x * radius, halfH, z * radius},
			{0.0f, 1.0f, 0.0f},
			{x * 0.5f + 0.5f, z * 0.5f + 0.5f}
		));
	}

	for (unsigned int j = 0; j < radialSegments; ++j) {
		data.indices.push_back(topCenterIndex);
		data.indices.push_back(topRingStart + j);
		data.indices.push_back(topRingStart + j + 1);
	}

	unsigned int bottomCenterIndex = static_cast<unsigned int>(data.vertices.size());
	data.vertices.push_back(Vertex({0.0f, -halfH, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.5f, 0.5f}));

	unsigned int bottomRingStart = static_cast<unsigned int>(data.vertices.size());
	for (unsigned int j = 0; j <= radialSegments; ++j) {
		float angle = static_cast<float>(j) * (2.0f * Math::PI / static_cast<float>(radialSegments));
		float x = std::cos(angle);
		float z = std::sin(angle);

		data.vertices.push_back(Vertex(
			{x * radius, -halfH, z * radius},
			{0.0f, -1.0f, 0.0f },
			{x * 0.5f + 0.5f, z * 0.5f + 0.5f}
		));
	}

	for (unsigned int j = 0; j < radialSegments; ++j) {
		data.indices.push_back(bottomCenterIndex);
		data.indices.push_back(bottomRingStart + j + 1);
		data.indices.push_back(bottomRingStart + j);
	}

	return data;
}

}
