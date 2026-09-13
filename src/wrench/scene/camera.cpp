#include "wrench/scene/camera.hpp"

namespace Wrench::Scene {

Math::Mat4 CameraNode::getViewMatrix() const {
	return Math::Mat4::lookAt(
		transform.position,
		transform.position + transform.forward(),
		transform.up()
	);
}

Math::Mat4 CameraNode::getProjectionMatrix() const {
	return Math::Mat4::perspective(fov, aspectRatio, kNearPlane, kFarPlane);
}

}