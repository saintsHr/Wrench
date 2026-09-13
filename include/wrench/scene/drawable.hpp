#pragma once

#include "wrench/renderer/mesh.hpp"
#include "wrench/renderer/shader.hpp"
#include "wrench/scene/scene.hpp"

namespace Wrench::Scene {

class DrawableNode : public Node {
public:
	Renderer::Mesh* mesh = nullptr;
	Renderer::Shader* shader = nullptr;

protected:

private:

};

}