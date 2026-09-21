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

#include "wrench/scene/components/transform.hpp"
#include <cmath>

namespace Wrench::Scene {

Mat4 TransformComponent::toMat4() const {
    return local_.toMat4();
}

void TransformComponent::rotateBy(const Vec3& deltaRotation, const RotationOptions& options) {
    local_.rotateBy(deltaRotation, options);
}

void TransformComponent::rotateBy(const Quaternion& deltaRotation, RotationSpace space) {
    local_.rotateBy(deltaRotation, space);
}

void TransformComponent::moveBy(const Vec3& deltaPosition) {
    local_.moveBy(deltaPosition);
}

void TransformComponent::scaleBy(const Vec3& deltaScale) {
    local_.scaleBy(deltaScale);
}

void TransformComponent::setRotation(const Vec3& r) {
    local_.setRotation(r);
}

void TransformComponent::setRotation(const Quaternion& r) {
    local_.setRotation(r);
}

void TransformComponent::setPosition(const Vec3& p) {
    local_.setPosition(p);
}

void TransformComponent::setScale(const Vec3& s) {
    local_.setScale(s);
}

void TransformComponent::lookAt(const Vec3& target) {
    local_.lookAt(target);
}

Vec3 TransformComponent::forward() const {
    return local_.forward();
}

Vec3 TransformComponent::right() const {
    return local_.right();
}

Vec3 TransformComponent::up() const {
    return local_.up();
}

Mat4 TransformComponent::getWorldMatrix() const {
    Node* parent = node()->parent;
    if (parent) return parent->transform().getWorldMatrix() * local_.toMat4();
    return local_.toMat4();
}

Vec3 TransformComponent::getWorldPosition() const {
    Mat4 m = getWorldMatrix();
    return Vec3(m(3, 0), m(3, 1), m(3, 2));
}

Vec3 TransformComponent::getWorldScale() const {
    Mat4 m = getWorldMatrix();

    Vec3 col0(m(0, 0), m(0, 1), m(0, 2));
    Vec3 col1(m(1, 0), m(1, 1), m(1, 2));
    Vec3 col2(m(2, 0), m(2, 1), m(2, 2));

    return Vec3(col0.length(), col1.length(), col2.length());
}

Quaternion TransformComponent::getWorldRotation() const {
    Mat4 m = getWorldMatrix();
    Vec3 scale = getWorldScale();

    float m00 = m(0,0) / scale.x, m01 = m(1,0) / scale.y, m02 = m(2,0) / scale.z;
    float m10 = m(0,1) / scale.x, m11 = m(1,1) / scale.y, m12 = m(2,1) / scale.z;
    float m20 = m(0,2) / scale.x, m21 = m(1,2) / scale.y, m22 = m(2,2) / scale.z;

    Quaternion q;
    float trace = m00 + m11 + m22;

    if (trace > 0) {
        float s = std::sqrt(trace + 1.0f) * 2.0f;
        q.w = 0.25f * s;
        q.x = (m21 - m12) / s;
        q.y = (m02 - m20) / s;
        q.z = (m10 - m01) / s;
    } else if (m00 > m11 && m00 > m22) {
        float s = std::sqrt(1.0f + m00 - m11 - m22) * 2.0f;
        q.w = (m21 - m12) / s;
        q.x = 0.25f * s;
        q.y = (m01 + m10) / s;
        q.z = (m02 + m20) / s;
    } else if (m11 > m22) {
        float s = std::sqrt(1.0f + m11 - m00 - m22) * 2.0f;
        q.w = (m02 - m20) / s;
        q.x = (m01 + m10) / s;
        q.y = 0.25f * s;
        q.z = (m12 + m21) / s;
    } else {
        float s = std::sqrt(1.0f + m22 - m00 - m11) * 2.0f;
        q.w = (m10 - m01) / s;
        q.x = (m02 + m20) / s;
        q.y = (m12 + m21) / s;
        q.z = 0.25f * s;
    }

    return q;
}

}
