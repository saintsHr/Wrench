#pragma once

#include "wrench/renderer/mesh.hpp"
#include "wrench/renderer/material.hpp"
#include "wrench/scene/scene.hpp"

namespace Wrench::Scene {

class DrawableNode : public Node {
public:
	Renderer::Mesh* mesh;
	Renderer::Material material;

protected:

private:

};

}