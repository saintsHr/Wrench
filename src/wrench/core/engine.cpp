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

#include "wrench/core/engine.hpp"
#include <GLFW/glfw3.h>

namespace Wrench {

void Engine::init(Application& app) {
	app_ = &app;

	glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_.create();
    window_.makeContextCurrent();

    app_->onInit(*this);
}

void Engine::run() {
	if (app_ == nullptr) return;

	running_ = true;

	while (running_) {
		window_.pollEvents();

		app_->onUpdate(*this);
		app_->onRender(*this);

		window_.swapBuffers();

		if (window_.shouldClose()) running_ = false;
	}
}

void Engine::shutdown() {
	if (app_ == nullptr) return;
	app_->onShutdown(*this);

	glfwTerminate();
}

Window& Engine::window(void) {
	return window_;
}

const Window& Engine::window(void) const {
	return window_;
}

}