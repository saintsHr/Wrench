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

#include <unordered_set>
#include <wrench/utils/vector/vec2.hpp>

namespace Wrench::Window {
    class Window;
}

class GLFWwindow;

namespace Wrench::Input {

enum class Key {
    Unknown,

    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    Num0, Num1, Num2, Num3, Num4,
    Num5, Num6, Num7, Num8, Num9,

    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
    F11, F12, F13, F14, F15, F16, F17, F18, F19, F20,
    F21, F22, F23, F24, F25,

    Up, Down, Left, Right,
    Home, End, PageUp, PageDown,

    LeftShift, RightShift,
    LeftControl, RightControl,
    LeftAlt, RightAlt,
    LeftSuper, RightSuper,

    Escape, Enter, Tab, Backspace,
    Space, CapsLock, Delete, Insert,
    PrintScreen, ScrollLock, NumLock, Pause, Menu,

    Comma, Period, Slash, Semicolon,
    Apostrophe, GraveAccent, Equal, Minus,
    LeftBracket, RightBracket, Backslash,

    World1, World2,

    KeypadNum0, KeypadNum1, KeypadNum2, KeypadNum3, KeypadNum4,
    KeypadNum5, KeypadNum6, KeypadNum7, KeypadNum8, KeypadNum9,
    KeypadDecimal, KeypadDivide, KeypadMultiply,
    KeypadSubtract, KeypadAdd, KeypadEnter, KeypadEqual
};

enum class MouseButton {
    Left, Right, Middle,
    Button4, Button5, Button6, Button7, Button8,
    Unknown
};

enum class MouseMode {
    Normal, Hidden, Locked
};

class Mouse {

friend class Wrench::Window::Window;

public:
    void update();

    bool isButtonDown(MouseButton button) const;
    Vec2 getPosition() const;
    Vec2 getDelta() const;

    void setMouseMode(MouseMode mode);
    MouseMode getMouseMode() const;
protected:

private:
    void on_button_event(MouseButton button, bool pressed);
    void on_move_event(Vec2 position);

    GLFWwindow* window_ = nullptr;

    std::unordered_set<MouseButton> pressed_buttons_;
    MouseMode mode_;

    Vec2 position_ = {0, 0};
    Vec2 old_position_ = {0, 0};
    Vec2 delta_ = {0, 0};
};

class Keyboard {

friend class Wrench::Window::Window;

public:
    bool isKeyDown(Key key) const;

protected:

private:
    void on_key_event(Key key, bool pressed);

    GLFWwindow* window_ = nullptr;

    std::unordered_set<Key> pressed_keys_;
};

}
