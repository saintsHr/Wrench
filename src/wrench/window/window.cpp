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
#include "wrench/utils/vector/vec2.hpp"
#include "wrench/input/input.hpp"
#include <GLFW/glfw3.h>

namespace Wrench::Input {
    enum class Key;
}

namespace {

static Wrench::Input::Key translate_key(int glfw_key) {
    switch (glfw_key) {
        case GLFW_KEY_A: return Wrench::Input::Key::A;
        case GLFW_KEY_B: return Wrench::Input::Key::B;
        case GLFW_KEY_C: return Wrench::Input::Key::C;
        case GLFW_KEY_D: return Wrench::Input::Key::D;
        case GLFW_KEY_E: return Wrench::Input::Key::E;
        case GLFW_KEY_F: return Wrench::Input::Key::F;
        case GLFW_KEY_G: return Wrench::Input::Key::G;
        case GLFW_KEY_H: return Wrench::Input::Key::H;
        case GLFW_KEY_I: return Wrench::Input::Key::I;
        case GLFW_KEY_J: return Wrench::Input::Key::J;
        case GLFW_KEY_K: return Wrench::Input::Key::K;
        case GLFW_KEY_L: return Wrench::Input::Key::L;
        case GLFW_KEY_M: return Wrench::Input::Key::M;
        case GLFW_KEY_N: return Wrench::Input::Key::N;
        case GLFW_KEY_O: return Wrench::Input::Key::O;
        case GLFW_KEY_P: return Wrench::Input::Key::P;
        case GLFW_KEY_Q: return Wrench::Input::Key::Q;
        case GLFW_KEY_R: return Wrench::Input::Key::R;
        case GLFW_KEY_S: return Wrench::Input::Key::S;
        case GLFW_KEY_T: return Wrench::Input::Key::T;
        case GLFW_KEY_U: return Wrench::Input::Key::U;
        case GLFW_KEY_V: return Wrench::Input::Key::V;
        case GLFW_KEY_W: return Wrench::Input::Key::W;
        case GLFW_KEY_X: return Wrench::Input::Key::X;
        case GLFW_KEY_Y: return Wrench::Input::Key::Y;
        case GLFW_KEY_Z: return Wrench::Input::Key::Z;

        case GLFW_KEY_0: return Wrench::Input::Key::Num0;
        case GLFW_KEY_1: return Wrench::Input::Key::Num1;
        case GLFW_KEY_2: return Wrench::Input::Key::Num2;
        case GLFW_KEY_3: return Wrench::Input::Key::Num3;
        case GLFW_KEY_4: return Wrench::Input::Key::Num4;
        case GLFW_KEY_5: return Wrench::Input::Key::Num5;
        case GLFW_KEY_6: return Wrench::Input::Key::Num6;
        case GLFW_KEY_7: return Wrench::Input::Key::Num7;
        case GLFW_KEY_8: return Wrench::Input::Key::Num8;
        case GLFW_KEY_9: return Wrench::Input::Key::Num9;

        case GLFW_KEY_F1:  return Wrench::Input::Key::F1;
        case GLFW_KEY_F2:  return Wrench::Input::Key::F2;
        case GLFW_KEY_F3:  return Wrench::Input::Key::F3;
        case GLFW_KEY_F4:  return Wrench::Input::Key::F4;
        case GLFW_KEY_F5:  return Wrench::Input::Key::F5;
        case GLFW_KEY_F6:  return Wrench::Input::Key::F6;
        case GLFW_KEY_F7:  return Wrench::Input::Key::F7;
        case GLFW_KEY_F8:  return Wrench::Input::Key::F8;
        case GLFW_KEY_F9:  return Wrench::Input::Key::F9;
        case GLFW_KEY_F10: return Wrench::Input::Key::F10;
        case GLFW_KEY_F11: return Wrench::Input::Key::F11;
        case GLFW_KEY_F12: return Wrench::Input::Key::F12;
        case GLFW_KEY_F13: return Wrench::Input::Key::F13;
        case GLFW_KEY_F14: return Wrench::Input::Key::F14;
        case GLFW_KEY_F15: return Wrench::Input::Key::F15;
        case GLFW_KEY_F16: return Wrench::Input::Key::F16;
        case GLFW_KEY_F17: return Wrench::Input::Key::F17;
        case GLFW_KEY_F18: return Wrench::Input::Key::F18;
        case GLFW_KEY_F19: return Wrench::Input::Key::F19;
        case GLFW_KEY_F20: return Wrench::Input::Key::F20;
        case GLFW_KEY_F21: return Wrench::Input::Key::F21;
        case GLFW_KEY_F22: return Wrench::Input::Key::F22;
        case GLFW_KEY_F23: return Wrench::Input::Key::F23;
        case GLFW_KEY_F24: return Wrench::Input::Key::F24;
        case GLFW_KEY_F25: return Wrench::Input::Key::F25;

        case GLFW_KEY_UP:        return Wrench::Input::Key::Up;
        case GLFW_KEY_DOWN:      return Wrench::Input::Key::Down;
        case GLFW_KEY_LEFT:      return Wrench::Input::Key::Left;
        case GLFW_KEY_RIGHT:     return Wrench::Input::Key::Right;
        case GLFW_KEY_HOME:      return Wrench::Input::Key::Home;
        case GLFW_KEY_END:       return Wrench::Input::Key::End;
        case GLFW_KEY_PAGE_UP:   return Wrench::Input::Key::PageUp;
        case GLFW_KEY_PAGE_DOWN: return Wrench::Input::Key::PageDown;

        case GLFW_KEY_LEFT_SHIFT:    return Wrench::Input::Key::LeftShift;
        case GLFW_KEY_RIGHT_SHIFT:   return Wrench::Input::Key::RightShift;
        case GLFW_KEY_LEFT_CONTROL:  return Wrench::Input::Key::LeftControl;
        case GLFW_KEY_RIGHT_CONTROL: return Wrench::Input::Key::RightControl;
        case GLFW_KEY_LEFT_ALT:      return Wrench::Input::Key::LeftAlt;
        case GLFW_KEY_RIGHT_ALT:     return Wrench::Input::Key::RightAlt;
        case GLFW_KEY_LEFT_SUPER:    return Wrench::Input::Key::LeftSuper;
        case GLFW_KEY_RIGHT_SUPER:   return Wrench::Input::Key::RightSuper;

        case GLFW_KEY_ESCAPE:       return Wrench::Input::Key::Escape;
        case GLFW_KEY_ENTER:        return Wrench::Input::Key::Enter;
        case GLFW_KEY_TAB:          return Wrench::Input::Key::Tab;
        case GLFW_KEY_BACKSPACE:    return Wrench::Input::Key::Backspace;
        case GLFW_KEY_SPACE:        return Wrench::Input::Key::Space;
        case GLFW_KEY_CAPS_LOCK:    return Wrench::Input::Key::CapsLock;
        case GLFW_KEY_DELETE:       return Wrench::Input::Key::Delete;
        case GLFW_KEY_INSERT:       return Wrench::Input::Key::Insert;
        case GLFW_KEY_PRINT_SCREEN: return Wrench::Input::Key::PrintScreen;
        case GLFW_KEY_SCROLL_LOCK:  return Wrench::Input::Key::ScrollLock;
        case GLFW_KEY_NUM_LOCK:     return Wrench::Input::Key::NumLock;
        case GLFW_KEY_PAUSE:        return Wrench::Input::Key::Pause;
        case GLFW_KEY_MENU:         return Wrench::Input::Key::Menu;

        case GLFW_KEY_COMMA:         return Wrench::Input::Key::Comma;
        case GLFW_KEY_PERIOD:        return Wrench::Input::Key::Period;
        case GLFW_KEY_SLASH:         return Wrench::Input::Key::Slash;
        case GLFW_KEY_SEMICOLON:     return Wrench::Input::Key::Semicolon;
        case GLFW_KEY_APOSTROPHE:    return Wrench::Input::Key::Apostrophe;
        case GLFW_KEY_GRAVE_ACCENT:  return Wrench::Input::Key::GraveAccent;
        case GLFW_KEY_EQUAL:         return Wrench::Input::Key::Equal;
        case GLFW_KEY_MINUS:         return Wrench::Input::Key::Minus;
        case GLFW_KEY_LEFT_BRACKET:  return Wrench::Input::Key::LeftBracket;
        case GLFW_KEY_RIGHT_BRACKET: return Wrench::Input::Key::RightBracket;
        case GLFW_KEY_BACKSLASH:     return Wrench::Input::Key::Backslash;

        case GLFW_KEY_WORLD_1: return Wrench::Input::Key::World1;
        case GLFW_KEY_WORLD_2: return Wrench::Input::Key::World2;

        case GLFW_KEY_KP_0:        return Wrench::Input::Key::KeypadNum0;
        case GLFW_KEY_KP_1:        return Wrench::Input::Key::KeypadNum1;
        case GLFW_KEY_KP_2:        return Wrench::Input::Key::KeypadNum2;
        case GLFW_KEY_KP_3:        return Wrench::Input::Key::KeypadNum3;
        case GLFW_KEY_KP_4:        return Wrench::Input::Key::KeypadNum4;
        case GLFW_KEY_KP_5:        return Wrench::Input::Key::KeypadNum5;
        case GLFW_KEY_KP_6:        return Wrench::Input::Key::KeypadNum6;
        case GLFW_KEY_KP_7:        return Wrench::Input::Key::KeypadNum7;
        case GLFW_KEY_KP_8:        return Wrench::Input::Key::KeypadNum8;
        case GLFW_KEY_KP_9:        return Wrench::Input::Key::KeypadNum9;
        case GLFW_KEY_KP_DECIMAL:  return Wrench::Input::Key::KeypadDecimal;
        case GLFW_KEY_KP_DIVIDE:   return Wrench::Input::Key::KeypadDivide;
        case GLFW_KEY_KP_MULTIPLY: return Wrench::Input::Key::KeypadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return Wrench::Input::Key::KeypadSubtract;
        case GLFW_KEY_KP_ADD:      return Wrench::Input::Key::KeypadAdd;
        case GLFW_KEY_KP_ENTER:    return Wrench::Input::Key::KeypadEnter;
        case GLFW_KEY_KP_EQUAL:    return Wrench::Input::Key::KeypadEqual;

        default: return Wrench::Input::Key::Unknown;
    }
}

static Wrench::Input::MouseButton translate_mouse_button(int glfw_button) {
    switch (glfw_button) {
        case GLFW_MOUSE_BUTTON_LEFT:   return Wrench::Input::MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT:  return Wrench::Input::MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return Wrench::Input::MouseButton::Middle;
        case GLFW_MOUSE_BUTTON_4:      return Wrench::Input::MouseButton::Button4;
        case GLFW_MOUSE_BUTTON_5:      return Wrench::Input::MouseButton::Button5;
        case GLFW_MOUSE_BUTTON_6:      return Wrench::Input::MouseButton::Button6;
        case GLFW_MOUSE_BUTTON_7:      return Wrench::Input::MouseButton::Button7;
        case GLFW_MOUSE_BUTTON_8:      return Wrench::Input::MouseButton::Button8;

        default: return Wrench::Input::MouseButton::Unknown;
    }
}

}

namespace Wrench::Window {

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
	glfwSetWindowUserPointer(raw_, this);

	glfwSetWindowSizeCallback(raw_, window_size_callback_);
	glfwSetMouseButtonCallback(raw_, mouse_button_callback_);
	glfwSetCursorPosCallback(raw_, mouse_position_callback_);
	glfwSetScrollCallback(raw_, mouse_scroll_callback_);
	glfwSetKeyCallback(raw_, key_callback_);

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
	size_ = size;

	if (raw_ != nullptr) {
		glfwSetWindowSize(
			raw_,
			static_cast<int>(size.x),
			static_cast<int>(size.y)
		);

		Log(
			LogLevel::Debug,
			LogCategory::Window,
			"Window resized: {}x{}.",
			size.x,
			size.y
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

void Window::setKeyboard(Wrench::Input::Keyboard* keyboard) {
    keyboard_ = keyboard;
    keyboard_->window_ = raw_;

    Log(
		LogLevel::Debug,
		LogCategory::Window,
		"Connected keyboard to window."
	);
}

void Window::setMouse(Wrench::Input::Mouse* mouse) {
    mouse_ = mouse;
    mouse_->window_ = raw_;

    Log(
		LogLevel::Debug,
		LogCategory::Window,
		"Connected mouse to window."
	);
}

void Window::window_size_callback_(GLFWwindow* window, int width, int height) {
    Wrench::Window::Window* self = static_cast<Wrench::Window::Window*>(
    	glfwGetWindowUserPointer(window)
    ); if (!self) return;

    self->setSize(
        Wrench::Vec2(
           	static_cast<float>(width),
           	static_cast<float>(height)
        )
    );
}

void Window::key_callback_(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Wrench::Window::Window* self = static_cast<Wrench::Window::Window*>(
    	glfwGetWindowUserPointer(window)
    ); if (!self) return;

    static_cast<void>(scancode);
    static_cast<void>(mods);

    if (!self->keyboard_) return;

    Wrench::Input::Key translated_key = translate_key(key);
    bool pressed = (action != GLFW_RELEASE);

    self->keyboard_->on_key_event(translated_key, pressed);
}

void Window::mouse_button_callback_(GLFWwindow* window, int button, int action, int mods) {
    Wrench::Window::Window* self = static_cast<Wrench::Window::Window*>(
    	glfwGetWindowUserPointer(window)
    ); if (!self) return;

    static_cast<void>(mods);

    if(!self->mouse_) return;

    Wrench::Input::MouseButton translated_button = translate_mouse_button(button);
    bool pressed = (action != GLFW_RELEASE);

    self->mouse_->on_button_event(translated_button, pressed);
}

void Window::mouse_position_callback_(GLFWwindow* window, double xpos, double ypos) {
    Wrench::Window::Window* self = static_cast<Wrench::Window::Window*>(
    	glfwGetWindowUserPointer(window)
    ); if (!self) return;

    if(!self->mouse_) return;

    self->mouse_->on_move_event(Vec2(static_cast<float>(xpos), static_cast<float>(ypos)));
}

void Window::mouse_scroll_callback_(GLFWwindow* window, double xoffset, double yoffset) {
    Wrench::Window::Window* self = static_cast<Wrench::Window::Window*>(
    	glfwGetWindowUserPointer(window)
    ); if (!self) return;

    static_cast<void>(xoffset);
    static_cast<void>(yoffset);
}

}
