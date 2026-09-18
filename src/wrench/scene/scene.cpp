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

#include "wrench/scene/camera.hpp"
#include "wrench/scene/scene.hpp"

namespace Wrench::Scene {

bool Scene::removeNode(Node* node) {
	if (!node || node == &root || !node->parent) return false;

	if (activeCamera && is_same_or_ancestor(node, activeCamera)) {
		activeCamera = nullptr;
	}

	return node->parent->removeChild(node);
}

bool Node::removeChild(Node* child) {
	auto it = std::ranges::find_if(
		children.begin(), children.end(),

		[child](const std::unique_ptr<Node>& c) {
			return c.get() == child;
		}
	); if (it == children.end()) return false;

	children.erase(it);
	return true;
}

std::vector<Node*> Node::findChildrenByName(const std::string& childName, bool includeSelf) {
	std::vector<Node*> result;
	if (includeSelf && this->name == childName) result.push_back(this);
	collect_children_by_name(this, childName, result);
	return result;
}

Node* Node::findChildByName(const std::string& childName, bool includeSelf) {
	auto result = findChildrenByName(childName, includeSelf);
	return result.empty() ? nullptr : result[0];
}

std::vector<Node*> Node::findDirectChildrenByName(const std::string& childName) {
	std::vector<Node*> result;
	for (auto& child : children) {
		if (child->name == childName) result.push_back(child.get());
	}
	return result;
}

Node* Node::findDirectChildByName(const std::string& childName) {
	for (auto& child : children) {
		if (child->name == childName) return child.get();
	}
	return nullptr;
}

void Node::collect_children_by_name(Node* node, const std::string& childName, std::vector<Node*>& out) {
	for (auto& child : node->children) {
		if (child->name == childName) out.push_back(child.get());
		collect_children_by_name(child.get(), childName, out);
	}
}

Math::Mat4 Node::getWorldMatrix() const {
	if (parent) return parent->getWorldMatrix() * transform.toMat4();
	return transform.toMat4();
}

Math::Vec3 Node::getWorldPosition() const {
	Math::Mat4 m = getWorldMatrix();
	return Math::Vec3(m(3, 0), m(3, 1), m(3, 2));
}

Math::Vec3 Node::getWorldScale() const {
	Math::Mat4 m = getWorldMatrix();

	Math::Vec3 col0(m(0, 0), m(0, 1), m(0, 2));
	Math::Vec3 col1(m(1, 0), m(1, 1), m(1, 2));
	Math::Vec3 col2(m(2, 0), m(2, 1), m(2, 2));

	return Math::Vec3(col0.length(), col1.length(), col2.length());
}

Math::Quaternion Node::getWorldRotation() const {
	Math::Mat4 m = getWorldMatrix();
	Math::Vec3 scale = getWorldScale();

	float m00 = m(0,0) / scale.x, m01 = m(1,0) / scale.y, m02 = m(2,0) / scale.z;
	float m10 = m(0,1) / scale.x, m11 = m(1,1) / scale.y, m12 = m(2,1) / scale.z;
	float m20 = m(0,2) / scale.x, m21 = m(1,2) / scale.y, m22 = m(2,2) / scale.z;

	Math::Quaternion q;
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

bool Scene::is_same_or_ancestor(Node* potentialAncestor, Node* node) {
	Node* current = node;

	while (current) {
		if (current == potentialAncestor) return true;
		current = current->parent;
	}

	return false;
}

std::vector<Node*> Scene::findNodesByName(const std::string& name) {
	return root.findChildrenByName(name, true);
}

Node* Scene::findNodeByName(const std::string& name) {
	return root.findChildByName(name, true);
}

}
