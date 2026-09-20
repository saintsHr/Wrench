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

#include "wrench/input/input.hpp"
#include <GLFW/glfw3.h>

namespace Wrench::Input {

bool Keyboard::isKeyDown(Key key) const {
    return pressed_keys_.find(key) != pressed_keys_.end();
}

void Keyboard::on_key_event(Key key, bool pressed) {
    if (pressed) {
        pressed_keys_.insert(key);
    } else {
        pressed_keys_.erase(key);
    }
}

bool Mouse::isButtonDown(MouseButton button) const {
    return pressed_buttons_.find(button) != pressed_buttons_.end();
}

Vec2 Mouse::getPosition() const {
    return position_;
}

Vec2 Mouse::getDelta() const {
    return delta_;
}

void Mouse::update() {
    delta_ = position_ - old_position_;
    old_position_ = position_;
}

void Mouse::setMouseMode(MouseMode mode) {
    switch (mode) {
        case MouseMode::Normal: glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL); break;
        case MouseMode::Hidden: glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); break;
        case MouseMode::Locked: glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED); break;
        default: break;
    }

    mode_ = mode;
}

MouseMode Mouse::getMouseMode() const {
    return mode_;
}

void Mouse::on_button_event(MouseButton button, bool pressed) {
    if (pressed) {
        pressed_buttons_.insert(button);
    } else {
        pressed_buttons_.erase(button);
    }
}

void Mouse::on_move_event(Vec2 position) {
    position_ = position;
}

}
