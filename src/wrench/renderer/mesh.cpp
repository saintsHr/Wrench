#include "wrench/renderer/mesh.hpp"
#include "wrench/utils/log.hpp"
#include <glad.h>

namespace Wrench {

Mesh::Mesh(
	const std::vector<Vertex>& vertices,
	const std::vector<unsigned int>& indices
) {
	// create mesh objects
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

	// upload data to GPU
	upload(vertices, indices);

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Mesh created with {} vertices and {} indices.",
		vertices.size(),
		indices.size()
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

	// moves "other" handles to "this"
	this->ebo_ = other.ebo_;
	this->vbo_ = other.vbo_;
	this->vao_ = other.vao_;

	// zeroes "other" handles
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

	// deletes "this" handles
 	glDeleteBuffers(1, &this->ebo_);
	glDeleteBuffers(1, &this->vbo_);
	glDeleteVertexArrays(1, &this->vao_);

	// moves "other" handles to "this"
	this->ebo_ = other.ebo_;
	this->vbo_ = other.vbo_;
	this->vao_ = other.vao_;

	// zeroes "other" handles
	other.ebo_ = 0;
	other.vbo_ = 0;
	other.vao_ = 0;

	return *this;
}

void Mesh::upload(
	const std::vector<Vertex>& vertices,
	const std::vector<unsigned int>& indices
) {
	indexCount_ = static_cast<unsigned int>(indices.size());

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Uploading mesh data (vertices: {}, indices: {}).",
		vertices.size(),
		indices.size()
	);

	// fills VBO with vertices
	glNamedBufferData(
		vbo_,
		static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
		vertices.data(), GL_STATIC_DRAW
	);

	// fills EBO with indices
	glNamedBufferData(
		ebo_,
		indexCount_ * sizeof(unsigned int),
		indices.data(), GL_STATIC_DRAW
	);

	// binds VBO to VAO
	glVertexArrayVertexBuffer(
		vao_, 0, vbo_, 0,
		sizeof(Vertex)
	);

	// binds EBO to VAO
	glVertexArrayElementBuffer(vao_, ebo_);

	// configs position attribute in VAO
	glEnableVertexArrayAttrib(vao_, 0);
	glVertexArrayAttribFormat(
		vao_, 0, 3,
		GL_FLOAT, GL_FALSE,
		offsetof(Vertex, position)
	);
	glVertexArrayAttribBinding(vao_, 0, 0);

	// configs normal attribute in VAO
	glEnableVertexArrayAttrib(vao_, 1);
	glVertexArrayAttribFormat(
		vao_, 1, 3,
		GL_FLOAT, GL_FALSE,
		offsetof(Vertex, normal)
	);
	glVertexArrayAttribBinding(vao_, 1, 0);

	// configs UV attribute in VAO
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