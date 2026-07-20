#include "wrench/renderer/mesh.hpp"
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

	// upload data to GPU
	upload(vertices, indices);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &ebo_);
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);

	ebo_ = 0;
	vbo_ = 0;
	vao_ = 0;
}

Mesh::Mesh(Mesh&& other) noexcept {
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

	// fills VBO with vertices
	glNamedBufferData(
		vbo_,
		static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
		vertices.data(),
		GL_STATIC_DRAW
	);

	// fills EBO with indices
	glNamedBufferData(
		ebo_,
		indexCount_ * sizeof(unsigned int),
		indices.data(),
		GL_STATIC_DRAW
	);

	// binds VBO to VAO
	glVertexArrayVertexBuffer(
		vao_,
		0,
		vbo_,
		0,
		sizeof(Vertex)
	);

	// binds EBO to VAO
	glVertexArrayElementBuffer(
		vao_,
		ebo_
	);

	// configs position attribute in VAO
	glEnableVertexArrayAttrib(vao_, 0);
	glVertexArrayAttribFormat(
		vao_,
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		offsetof(Vertex, position)
	);
	glVertexArrayAttribBinding(vao_, 0, 0);

	// configs normal attribute in VAO
	glEnableVertexArrayAttrib(vao_, 1);
	glVertexArrayAttribFormat(
		vao_,
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		offsetof(Vertex, normal)
	);
	glVertexArrayAttribBinding(vao_, 1, 0);

	// configs UV attribute in VAO
	glEnableVertexArrayAttrib(vao_, 2);
	glVertexArrayAttribFormat(
		vao_,
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		offsetof(Vertex, uv)
	);
	glVertexArrayAttribBinding(vao_, 2, 0);
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