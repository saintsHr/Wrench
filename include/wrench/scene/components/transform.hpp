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

#include "wrench/scene/scene.hpp"
#include "wrench/utils/vector/transform.hpp"

namespace Wrench::Scene {

class TransformComponent : public Component {
public:
    Mat4 toMat4() const;

    void rotateBy(const Vec3& deltaRotation, const RotationOptions& options = {});
    void rotateBy(const Quaternion& deltaRotation, RotationSpace space = RotationSpace::Local);
    void moveBy(const Vec3& deltaPosition);
    void scaleBy(const Vec3& deltaScale);

    void setRotation(const Vec3& r);
    void setRotation(const Quaternion& r);
    void setPosition(const Vec3& p);
    void setScale(const Vec3& s);

    void lookAt(const Vec3& target);

    Vec3 forward() const;
    Vec3 right() const;
    Vec3 up() const;

    Mat4 getWorldMatrix() const;
    Vec3 getWorldPosition() const;
    Vec3 getWorldScale() const;
    Quaternion getWorldRotation() const;

protected:

private:
    Transform local_;
};

}
