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
#include "wrench/utils/log.hpp"
#include <cstdlib>
#include <glad.h>
#include <string>

namespace Wrench {

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
	if(vertexSource.empty()) {
		Log(
			LogLevel::Error,
			LogCategory::Renderer,
			"Cannot create shader: empty vertex source."
		);

		return;
	}

	if(fragmentSource.empty()) {
		Log(
			LogLevel::Error,
			LogCategory::Renderer,
			"Cannot create shader: empty fragment source."
		);

		return;
	}

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Creating shader program."
	);

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Shader source sizes (Vertex: {} bytes, Fragment: {} bytes).",
		vertexSource.size(),
		fragmentSource.size()
	);

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
	std::string log_shader = "";

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Created shader objects (Vertex: {}, Fragment: {}, Program: {}).",
		vertexShader,
		fragmentShader,
		shaderProgram
	);

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

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Compiling shaders."
	);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertex);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fragment);

	if(success_vertex == false) {
	    GLint length = 0;

		glGetShaderiv(
			vertexShader,
			GL_INFO_LOG_LENGTH,
			&length
		);

		log_vertex.resize(static_cast<size_t>(length));

		glGetShaderInfoLog(
			vertexShader,
			length,
			nullptr,
			log_vertex.data()
		);

	    Log(
			LogLevel::Error,
			LogCategory::Renderer,
			"Vertex shader compilation failed:\n{}",
			log_vertex
		);

	    glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);

	    return;
	}

	if(success_fragment == false) {
	    GLint length = 0;

		glGetShaderiv(
			fragmentShader,
			GL_INFO_LOG_LENGTH,
			&length
		);

		log_fragment.resize(static_cast<size_t>(length));

		glGetShaderInfoLog(
			fragmentShader,
			length,
			nullptr,
			log_fragment.data()
		);

	    Log(
			LogLevel::Error,
			LogCategory::Renderer,
			"Fragment shader compilation failed:\n{}",
			log_fragment
		);

	    glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);

	    return;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Linking shader program {}.",
		shaderProgram
	);

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_link);

	if(success_link == false) {
	    GLint length = 0;

		glGetProgramiv(
			shaderProgram,
			GL_INFO_LOG_LENGTH,
			&length
		);

		log_shader.resize(static_cast<size_t>(length));

		glGetProgramInfoLog(
			shaderProgram,
			length,
			nullptr,
			log_shader.data()
		);

	    Log(
			LogLevel::Error,
			LogCategory::Renderer,
			"Shader program linking failed:\n{}",
			log_shader
		);

	    glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);

	    return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	program_ = shaderProgram;

	Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"Shader program created (ID: {}).",
		program_
	);
}

Shader::~Shader() {
	if (program_ == 0) return;

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Destroying shader program {}.",
		program_
	);

	glDeleteProgram(program_);
	program_ = 0;
}

Shader::Shader(Shader&& other) noexcept {
	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Moving shader program {}.",
		other.program_
	);

	this->program_ = other.program_;
	other.program_ = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
	if (this == &other) return *this;

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Moving shader program {}.",
		other.program_
	);

	if (this->program_ != 0) glDeleteProgram(this->program_);

	this->program_ = other.program_;
	other.program_ = 0;

	return *this;
}

void Shader::use(void) {
	Log(
		LogLevel::Trace,
		LogCategory::Renderer,
		"Using shader program {}.",
		program_
	);

	glUseProgram(this->program_);
}

void Shader::setUniformVec2(const std::string& name, const Vec2& value) const {
	int loc = get_uniform_location_(name);
	if (loc == -1) return;
	glProgramUniform2f(program_, loc, value.x, value.y);
}

void Shader::setUniformVec3(const std::string& name, const Vec3& value) const {
	int loc = get_uniform_location_(name);
	if (loc == -1) return;
	glProgramUniform3f(program_, loc, value.x, value.y, value.z);
}

void Shader::setUniformMat4(const std::string& name, const Mat4& value) const {
	int loc = get_uniform_location_(name);
	if (loc == -1) return;
	glProgramUniformMatrix4fv(program_, loc, 1, GL_FALSE, value.data());
}

void Shader::setUniformFloat(const std::string& name, float value) const {
	int loc = get_uniform_location_(name);
	if (loc == -1) return;
	glProgramUniform1f(program_, loc, value);
}

void Shader::setUniformInt(const std::string& name, int value) const {
	int loc = get_uniform_location_(name);
	if (loc == -1) return;
	glProgramUniform1i(program_, loc, value);
}

int Shader::get_uniform_location_(const std::string& name) const {
	auto it = cache_.find(name);
	if (it != cache_.end()) return it->second;

	int location = glGetUniformLocation(this->program_, name.c_str());

	if (location == -1) {
		Log(
			LogLevel::Warning,
			LogCategory::Renderer,
			"Uniform '{}' not found in shader program {}.",
			name,
			program_
		);
	}

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Caching uniform '{}' at location {}.",
		name,
		location
	);

	cache_[name] = location;

	return location;
}

}