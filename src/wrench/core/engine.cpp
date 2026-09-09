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
#include "wrench/utils/log.hpp"

#include <cstdlib>
#include <glad.h>
#include <GLFW/glfw3.h>

namespace Wrench {

Engine::Engine() {
	startup_timer_.Reset();

	logger_.Log(
		LogLevel::Info,
		LogCategory::Core,
		"Initializing engine...",
		nullptr
	);

	if (!glfwInit()) {
		logger_.Log(
			LogLevel::Fatal,
			LogCategory::Window,
			"Failed to initialize GLFW.",
			nullptr
		);
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);

	glfwWindowHint(GLFW_RED_BITS,   8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS,  8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    logger_.Log(
		LogLevel::Info,
		LogCategory::Window,
		"Initializing window...",
		nullptr
	);
    window_.create();
    window_.makeContextCurrent();
    logger_.Log(
		LogLevel::Info,
		LogCategory::Window,
		"Window initialized.",
		nullptr
	);

    logger_.Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"Initializing renderer...",
		nullptr
	);
    renderer_.init(window_);
    logger_.Log(
		LogLevel::Info,
		LogCategory::Renderer,
		"Renderer initialized.",
		nullptr
	);

    logger_.Log(
		LogLevel::Info,
		LogCategory::Core,
		"Engine initialized in {} ms.",
		startup_timer_.ElapsedMilliseconds()
	);

	startup_timer_.Reset();
}

void Engine::run(Application& app) {
	app.engine_ = this;

	logger_.Log(
		LogLevel::Info,
		LogCategory::Core,
		"Initializing application...",
		nullptr
	);

	app.onInitialize();

	logger_.Log(
		LogLevel::Info,
		LogCategory::Core,
		"Application initialized.",
		nullptr
	);

	running_ = true;

	while (running_) {
		window_.pollEvents();

		app.onUpdate();

		renderer_.beginFrame();
		app.onRender();
		renderer_.endFrame();

		window_.swapBuffers();

		if (window_.shouldClose()) {
			logger_.Log(
				LogLevel::Info,
				LogCategory::Window,
				"Window close requested.",
				nullptr
			);

			running_ = false;
		}
	}

	logger_.Log(
		LogLevel::Info,
		LogCategory::Core,
		"Shutting down application...",
		nullptr
	);

	app.onShutdown();

	logger_.Log(
		LogLevel::Info,
		LogCategory::Core,
		"Application shutdown complete.",
		nullptr
	);
}

Engine::~Engine() {
	logger_.Log(
		LogLevel::Info,
		LogCategory::Core,
		"Shutting down engine...",
		nullptr
	);

	logger_.Log(
		LogLevel::Info,
		LogCategory::Window,
		"Shutting down GLFW...",
		nullptr
	);
	glfwTerminate();
	logger_.Log(
		LogLevel::Info,
		LogCategory::Window,
		"GLFW shutdown complete.",
		nullptr
	);

	logger_.Log(
		LogLevel::Info,
		LogCategory::Core,
		"Engine shutdown complete.",
		nullptr
	);
}

Window& Engine::window(void) {
	return window_;
}

const Window& Engine::window(void) const {
	return window_;
}

Renderer& Engine::renderer(void) {
	return renderer_;
}

const Renderer& Engine::renderer(void) const {
	return renderer_;
}

Logger& Engine::logger(void) {
	return logger_;
}

const Logger& Engine::logger(void) const {
	return logger_;
}

}