#pragma once

#include "wrench/utils/vector/transform.hpp"
#include <memory>
#include <string>
#include <vector>

namespace Wrench::Scene {

class CameraNode;

class Node {
public:
	Math::Transform transform;
	std::string name;

	std::vector<std::unique_ptr<Node>> children;
	Node* parent = nullptr;

	virtual ~Node() = default;

	Math::Mat4 getWorldMatrix() const;
	Math::Vec3 getWorldPosition() const;
	Math::Vec3 getWorldScale() const;
	Math::Quaternion getWorldRotation() const;

	template<typename T>
	T* addChild(std::unique_ptr<T> child) {
		if (!child) return nullptr;

		T* ptr = child.get();
		child->parent = this;
		children.push_back(std::move(child));

		return ptr;
	}

	bool removeChild(Node* child);

	template<typename T>
	std::vector<T*> findChildrenByType(bool includeSelf = false) {
		std::vector<T*> result;
		if (includeSelf) if (auto* casted = dynamic_cast<T*>(this)) result.push_back(casted);
		collect_children_by_type<T>(this, result);
		return result;
	}

	template<typename T>
	T* findChildByType(bool includeSelf = false) {
		auto result = findChildrenByType<T>(includeSelf);
		return result.empty() ? nullptr : result[0];
	}

	std::vector<Node*> findChildrenByName(const std::string& childName, bool includeSelf = false);
	Node* findChildByName(const std::string& childName, bool includeSelf = false);

	template<typename T>
	std::vector<T*> findDirectChildrenByType() {
		std::vector<T*> result;
		for (auto& child : children) {
			if (auto* casted = dynamic_cast<T*>(child.get())) result.push_back(casted);
		}
		return result;
	}

	template<typename T>
	T* findDirectChildByType() {
		for (auto& child : children) {
			if (auto* casted = dynamic_cast<T*>(child.get())) return casted;
		}
		return nullptr;
	}

	std::vector<Node*> findDirectChildrenByName(const std::string& childName);
	Node* findDirectChildByName(const std::string& childName);

protected:

private:
	template<typename T>
	void collect_children_by_type(Node* node, std::vector<T*>& out) {
		for (auto& child : node->children) {
			if (auto* casted = dynamic_cast<T*>(child.get())) out.push_back(casted);
			collect_children_by_type<T>(child.get(), out);
		}
	}

	void collect_children_by_name(Node* node, const std::string& childName, std::vector<Node*>& out);
};

class Scene {
public:
	Node root;
	CameraNode* activeCamera = nullptr;

	template<typename T>
	T* addNode(std::unique_ptr<T> node, Node* parent = nullptr) {
		Node* target = parent ? parent : &root;
		return target->addChild(std::move(node));
	}

	bool removeNode(Node* node);

	template<typename T>
	std::vector<T*> findNodesByType() {
		return root.findChildrenByType<T>(true);
	}

	template<typename T>
	T* findNodeByType() {
		return root.findChildByType<T>(true);
	}

	std::vector<Node*> findNodesByName(const std::string& name);
	Node* findNodeByName(const std::string& name);

protected:

private:
	bool is_same_or_ancestor(Node* potentialAncestor, Node* node);
};

}