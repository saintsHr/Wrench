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

#include "wrench/utils/vector/quaternion.hpp"
#include "wrench/utils/vector/vec3.hpp"
#include <wrench/utils/vector/mat4.hpp>

namespace Wrench {

enum class RotationSpace {
    Local, World
};

enum class RotationOrder {
    XYZ, XZY,
    YXZ, YZX,
    ZXY, ZYX
};

struct RotationOptions {
    RotationSpace x = RotationSpace::Local;
    RotationSpace y = RotationSpace::Local;
    RotationSpace z = RotationSpace::Local;
    RotationOrder order = RotationOrder::XYZ;
};

class Transform {
public:
	Transform() :
		position(0.0f, 0.0f, 0.0f),
		rotation(0.0f, 0.0f, 0.0f, 1.0f),
		scale(1.0f, 1.0f, 1.0f)
	{}

	Vec3 position;
	Quaternion rotation;
	Vec3 scale;

	Mat4 toMat4() const {
		Mat4 result = Mat4::identity();

		result = (
			Mat4::translate(position) * rotation.toMat4() * Mat4::scale(scale)
		);

		return result;
	}

	void rotateBy(
        const Vec3& deltaRotation,
        const RotationOptions& options = {}
	) {
        struct AxisRotation {
            Quaternion rotation;
            RotationSpace space;
        };

        AxisRotation axes[3] = {
            {
                Quaternion::fromAxisAngle(
                    Vec3(1,0,0),
                    deltaRotation.x
                ),
                options.x
            },
            {
                Quaternion::fromAxisAngle(
                    Vec3(0,1,0),
                    deltaRotation.y
                ),
                options.y
            },
            {
                Quaternion::fromAxisAngle(
                    Vec3(0,0,1),
                    deltaRotation.z
                ),
                options.z
            }
        };

        auto applyRotation = [&](const AxisRotation& axis) {
            rotateBy(axis.rotation, axis.space);
        };

        switch (options.order) {
            case RotationOrder::XYZ: {
                applyRotation(axes[0]);
                applyRotation(axes[1]);
                applyRotation(axes[2]);
                break;
            }
            case RotationOrder::XZY: {
                applyRotation(axes[0]);
                applyRotation(axes[2]);
                applyRotation(axes[1]);
                break;
            }
            case RotationOrder::YXZ: {
                applyRotation(axes[1]);
                applyRotation(axes[0]);
                applyRotation(axes[2]);
                break;
            }
            case RotationOrder::YZX: {
                applyRotation(axes[1]);
                applyRotation(axes[2]);
                applyRotation(axes[0]);
                break;
            }
            case RotationOrder::ZXY: {
                applyRotation(axes[2]);
                applyRotation(axes[0]);
                applyRotation(axes[1]);
                break;
            }
            case RotationOrder::ZYX: {
                applyRotation(axes[2]);
                applyRotation(axes[1]);
                applyRotation(axes[0]);
                break;
            }
        }

        rotation.normalize();
	}

	void rotateBy(const Quaternion& deltaRotation, RotationSpace space = RotationSpace::Local) {
        switch (space) {
            case RotationSpace::Local: rotation = rotation * deltaRotation; break;
            case RotationSpace::World: rotation = deltaRotation * rotation; break;
        }

		rotation.normalize();
	}

	void moveBy(const Vec3& deltaPosition) {
		position = position + deltaPosition;
	}

	void scaleBy(const Vec3& deltaScale) {
		scale = scale * deltaScale;
	}

	void setRotation(const Vec3& newRotation) {
    	rotation = (
    		Quaternion::fromAxisAngle(Vec3(1,0,0), newRotation.x) *
    		Quaternion::fromAxisAngle(Vec3(0,1,0), newRotation.y) *
			Quaternion::fromAxisAngle(Vec3(0,0,1), newRotation.z)
		);

        rotation.normalize();
	}

	void setRotation(const Quaternion& newRotation) {
    	rotation = newRotation;
	}

	void setPosition(const Vec3& newPosition) {
    	position = newPosition;
	}

	void setScale(const Vec3& newScale) {
    	scale = newScale;
	}

	Vec3 forward() const {
	    return rotation * Vec3(0, 0, -1);
	}

	Vec3 right() const {
	    return rotation * Vec3(1, 0, 0);
	}

	Vec3 up() const {
	    return rotation * Vec3(0, 1, 0);
	}

	void lookAt(const Vec3& target) {
	    Vec3 direction = target - position;

	    rotation = Quaternion::lookRotation(
	        direction,
	        Vec3(0,1,0)
	    );
	}

protected:

private:

};

}
