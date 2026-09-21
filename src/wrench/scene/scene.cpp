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

#include "wrench/scene/scene.hpp"
#include "wrench/scene/components/transform.hpp"
#include "wrench/scene/components/camera.hpp"
#include <algorithm>

namespace Wrench::Scene {

Node::Node(Scene& scene) : scene_(&scene) {
    transform_ = addComponent<TransformComponent>();
}

Node::~Node() {
    if (scene_ && !scene_->destructing_ &&
        scene_->activeCamera && scene_->activeCamera->node() == this) {
        scene_->activeCamera = nullptr;
    }

    for (auto& c : components_) {
        c->onDetach();
        if (scene_ && !scene_->destructing_) {
            Component& comp = *c;
            scene_->unregister_component_(std::type_index(typeid(comp)), c.get());
        }
    }
}

Scene& Node::scene() {
    return *scene_;
}

TransformComponent& Node::transform() {
    return *transform_;
}

void Node::attach_component_(std::unique_ptr<Component> comp, std::type_index type) {
    comp->node_ = this;
    Component* ptr = comp.get();

    components_.push_back(std::move(comp));

    if (scene_) scene_->register_component_(type, ptr);

    ptr->onAttach();
}

bool Node::removeComponent(Component* component) {
    if (!component || component == transform_) return false;

    auto it = std::ranges::find_if(
        components_,
        [component](const std::unique_ptr<Component>& c) { return c.get() == component; }
    );
    if (it == components_.end()) return false;

    (*it)->onDetach();

    if (scene_) {
        Component& comp = *component;
        scene_->unregister_component_(std::type_index(typeid(comp)), component);
    }

    components_.erase(it);
    return true;
}

bool Node::removeChild(Node* child) {
    auto it = std::ranges::find_if(
        children,
        [child](const std::unique_ptr<Node>& c) { return c.get() == child; }
    );
    if (it == children.end()) return false;

    children.erase(it);
    return true;
}

Node* Component::node() const {
    return node_;
}

TransformComponent& Component::transform() const {
    return node_->transform();
}

Scene::Scene() {
    root_ = std::make_unique<Node>(*this);
}

Scene::~Scene() {
    destructing_ = true;
}

Node& Scene::root() {
    return *root_;
}

const Node& Scene::root() const {
    return *root_;
}

bool Scene::removeNode(Node* node) {
    if (!node || node == root_.get() || !node->parent) return false;
    return node->parent->removeChild(node);
}

Node* Scene::createNode(Node* parent) {
    return addNode<Node>(parent);
}

void Scene::register_component_(std::type_index type, Component* comp) {
    registry_[type].push_back(comp);
}

void Scene::unregister_component_(std::type_index type, Component* comp) {
    auto it = registry_.find(type);
    if (it == registry_.end()) return;

    auto& vec = it->second;
    vec.erase(std::remove(vec.begin(), vec.end(), comp), vec.end());
}

}
