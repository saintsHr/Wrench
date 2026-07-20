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
#include "glad.h"
#include "wrench/window/window.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <sys/cdefs.h>

static void framebuffer_size_callback(__attribute__((unused)) GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

namespace Wrench {

void Renderer::init(Window& window) {
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	glfwSetFramebufferSizeCallback(window.nativeHandle(), framebuffer_size_callback);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(
		0, 0,
		static_cast<int>(window.getSize().x),
		static_cast<int>(window.getSize().y)
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