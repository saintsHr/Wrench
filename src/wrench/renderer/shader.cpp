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

#include "wrench/renderer/shader.hpp"
#include <cstdlib>
#include <glad.h>
#include <iostream>
#include <string>

static constexpr int SHADER_LOG_SIZE = 1024;

namespace Wrench {

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;
	unsigned int shaderProgram = 0;

	const char* vertexStr = vertexSource.c_str();
	const char* fragmentStr = fragmentSource.c_str();

	int success_vertex = true;
	int success_fragment = true;
	int success_link = true;
	
	std::string log_vertex = "";
	std::string log_fragment = "";
	std::string log_link = "";

	log_vertex.resize(SHADER_LOG_SIZE);
	log_fragment.resize(SHADER_LOG_SIZE);
	log_link.resize(SHADER_LOG_SIZE);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	glShaderSource(
		vertexShader,
		1,
		&vertexStr,
		nullptr
	);

	glShaderSource(
		fragmentShader,
		1,
		&fragmentStr,
		nullptr
	);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertex);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fragment);

	if(success_vertex == false) {
	    glGetShaderInfoLog(vertexShader, log_vertex.size(), NULL, log_vertex.data());
	    std::cout << "Vertex shader failed to compile:\n" << log_vertex << std::endl;

	    glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);

	    return;
	}

	if(success_fragment == false) {
	    glGetShaderInfoLog(fragmentShader, log_fragment.size(), NULL, log_fragment.data());
	    std::cout << "Fragment shader failed to compile:\n" << log_fragment << std::endl;

	    glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);

	    return;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_link);

	if(success_link == false) {
	    glGetProgramInfoLog(shaderProgram, log_link.size(), NULL, log_link.data());
	    std::cout << "Shader failed to link:\n" << log_link << std::endl;

	    glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);

	    return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	program_ = shaderProgram;
}

Shader::~Shader() {
	glDeleteProgram(this->program_);
}

Shader::Shader(Shader&& other) noexcept {
	this->program_ = other.program_;
	other.program_ = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
	if (this == &other) return *this;

	glDeleteProgram(this->program_);
	this->program_ = other.program_;
	other.program_ = 0;

	return *this;
}

void Shader::use(void) {
	glUseProgram(this->program_);
}

}