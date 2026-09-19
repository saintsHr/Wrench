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

#pragma once

#include "wrench/utils/vector/vec2.hpp"
#include <string>

struct GLFWwindow;

namespace Wrench::Input {
    class Mouse;
    class Keyboard;
}

namespace Wrench::Window {

inline const Vec2 DEFAULT_WINDOW_SIZE(800, 600);
inline const std::string DEFAULT_WINDOW_TITLE("Untitled Window");

class Window {
public:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window() = default;
	~Window();

	void create(void);

	void setTitle(const std::string& title);
	void setSize(Vec2 size);

	const std::string& getTitle(void) const;
	Vec2 getSize(void) const;

	void setMouse(Wrench::Input::Mouse* mouse);
	void setKeyboard(Wrench::Input::Keyboard* keyboard);

	bool shouldClose(void) const;

	void pollEvents(void);
	void swapBuffers(void);

	void makeContextCurrent(void);

	GLFWwindow* nativeHandle(void) const;

protected:

private:
	GLFWwindow* raw_ = nullptr;
	std::string title_ = "Untitled Window";
	Vec2 size_ = {0, 0};

	Wrench::Input::Keyboard* keyboard_ = nullptr;
	Wrench::Input::Mouse* mouse_ = nullptr;

	static void window_size_callback_(GLFWwindow* window, int width, int height);
	static void key_callback_(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback_(GLFWwindow* window, int button, int action, int mods);
	static void mouse_position_callback_(GLFWwindow* window, double xpos, double ypos);
	static void mouse_scroll_callback_(GLFWwindow* window, double xoffset, double yoffset);
};

}
