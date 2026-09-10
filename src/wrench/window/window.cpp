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

#include "wrench/window/window.hpp"
#include "wrench/utils/log.hpp"
#include <GLFW/glfw3.h>

namespace Wrench {

Window::~Window() {
	if (raw_ == nullptr) return;

	Log(
		LogLevel::Debug,
		LogCategory::Window,
		"Destroying window."
	);

	glfwDestroyWindow(raw_);
	raw_ = nullptr;

	Log(
		LogLevel::Info,
		LogCategory::Window,
		"Window destroyed."
	);
}

void Window::create(void) {
	Log(
		LogLevel::Debug,
		LogCategory::Window,
		"Creating window (Size: {}x{}, Title: '{}').",
		DEFAULT_WINDOW_SIZE.x,
		DEFAULT_WINDOW_SIZE.y,
		DEFAULT_WINDOW_TITLE
	);

	GLFWwindow* window = glfwCreateWindow(
		static_cast<int>(DEFAULT_WINDOW_SIZE.x),
		static_cast<int>(DEFAULT_WINDOW_SIZE.y),
		DEFAULT_WINDOW_TITLE.c_str(),
		NULL, NULL
	);

	if(window == nullptr) {
		Log(
			LogLevel::Error,
			LogCategory::Window,
			"Failed to create window."
		);

		return;
	}

	size_ = DEFAULT_WINDOW_SIZE;
	raw_ = window;

	Log(
		LogLevel::Info,
		LogCategory::Window,
		"Window created successfully."
	);
}

GLFWwindow* Window::nativeHandle(void) const {
	return raw_;
}

bool Window::shouldClose(void) const {
	if (raw_ != nullptr) {
		bool close = glfwWindowShouldClose(raw_);

		if(close) {
			Log(
				LogLevel::Debug,
				LogCategory::Window,
				"Window close requested."
			);
		}

		return close;
	}

	Log(
		LogLevel::Warning,
		LogCategory::Window,
		"Checking close state on invalid window."
	);

	return false;
}

void Window::pollEvents(void) {
	glfwPollEvents();
}

void Window::swapBuffers(void) {
	if (raw_ != nullptr) {
		glfwSwapBuffers(raw_);
	}
}

void Window::makeContextCurrent(void) {
	if (raw_ != nullptr) {
		Log(
			LogLevel::Debug,
			LogCategory::Window,
			"Making window context current."
		);

		glfwMakeContextCurrent(raw_);
	} else {
		Log(
			LogLevel::Warning,
			LogCategory::Window,
			"Cannot make context current: invalid window."
		);
	}
}

void Window::setTitle(const std::string& title) {
	Log(
		LogLevel::Debug,
		LogCategory::Window,
		"Changing window title to '{}'.",
		title
	);

	title_ = title;

	if (raw_ != nullptr) {
		glfwSetWindowTitle(
			raw_,
			title.c_str()
		);
	} else {
		Log(
			LogLevel::Warning,
			LogCategory::Window,
			"Cannot set title: invalid window."
		);
	}
}

void Window::setSize(Vec2 size) {
	Log(
		LogLevel::Debug,
		LogCategory::Window,
		"Changing window size to {}x{}.",
		size.x,
		size.y
	);

	size_ = size;

	if (raw_ != nullptr) {
		glfwSetWindowSize(
			raw_,
			static_cast<int>(size.x),
			static_cast<int>(size.y)
		);
	} else {
		Log(
			LogLevel::Warning,
			LogCategory::Window,
			"Cannot set size: invalid window."
		);
	}
}

const std::string& Window::getTitle(void) const {
	return title_;
}

Vec2 Window::getSize(void) const {
	return size_;
}

}