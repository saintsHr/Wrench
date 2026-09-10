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

#include "wrench/renderer/renderer.hpp"
#include "wrench/utils/log.hpp"
#include "wrench/window/window.hpp"
#include <glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <sys/cdefs.h>

static void framebuffer_size_callback(
	GLFWwindow* window,
	int width, int height
) {
	static_cast<void>(window);
    glViewport(0, 0, width, height);

    Log(
		Wrench::LogLevel::Debug,
		Wrench::LogCategory::Window,
		"Framebuffer resized: {}x{}.",
		width,
		height
	);
}

namespace Wrench {

void Renderer::init(Window& window) {
	Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"Initializing renderer..."
	);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		Log(
			LogLevel::Fatal,
			LogCategory::Renderer,
			"Failed to initialize GLAD."
		);
	}

	Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"OpenGL initialized."
	);

	Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"OpenGL version: {}.",
		reinterpret_cast<const char*>(glGetString(GL_VERSION))
	);
	Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"GLSL version: {}.",
		reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION))
	);
	Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"GPU: {}.",
		reinterpret_cast<const char*>(glGetString(GL_RENDERER))
	);
	Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"Vendor: {}.",
		reinterpret_cast<const char*>(glGetString(GL_VENDOR))
	);

	glfwSetFramebufferSizeCallback(window.nativeHandle(), framebuffer_size_callback);

	glViewport(
		0, 0,
		static_cast<int>(window.getSize().x),
		static_cast<int>(window.getSize().y)
	);

	Log(
		LogLevel::Debug,
		LogCategory::Renderer,
		"Viewport initialized: {}x{}.",
		window.getSize().x,
		window.getSize().y
	);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_STENCIL_TEST);

	Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"Renderer initialized.",
		nullptr
	);
}

void Renderer::beginFrame(void) {
	glClear(
		GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT |
		GL_STENCIL_BUFFER_BIT
	);
}

void Renderer::endFrame(void) {

}

}