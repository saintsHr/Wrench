#pragma once

#include "wrench/scene/scene.hpp"
#include "wrench/window/window.hpp"

namespace Wrench::Scene {

class CameraNode : public Node {
public:
	float fov = 70.0f;
	float aspectRatio = 
		Wrench::Window::DEFAULT_WINDOW_SIZE.x /
		Wrench::Window::DEFAULT_WINDOW_SIZE.y;

	Math::Mat4 getViewMatrix() const;
	Math::Mat4 getProjectionMatrix() const;

protected:
	
private:
	static constexpr float kNearPlane = 0.1f;
	static constexpr float kFarPlane = 1000.0f;
};

}