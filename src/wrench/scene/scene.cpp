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
#include <algorithm>

namespace Wrench::Scene {

Scene::Scene() {
    root_ = node_pool_.emplace();
    Node* r = node_pool_.get(root_);
    r->id = root_;
    r->parent = InvalidNode;
}

NodeID Scene::createNode(NodeID parentId) {
    NodeID pid = parentId.valid() ? parentId : root_;
    Node* parent = getNode(pid);
    if (!parent) return InvalidNode;

    NodeID newId = node_pool_.emplace();
    Node* n = node_pool_.get(newId);
    n->id = newId;
    n->parent = pid;

    parent->children.push_back(newId);
    return newId;
}

bool Scene::removeNode(NodeID id) {
    if (id == root_) return false;
    Node* n = getNode(id);
    if (!n) return false;

    std::vector<NodeID> childrenCopy = n->children;
    for (NodeID child : childrenCopy) {
        removeNode(child);
    }

    std::vector<ComponentID> compsCopy = n->components;
    for (ComponentID cid : compsCopy) {
        detach_and_remove_component_(*n, cid);
    }

    if (activeCamera == id) {
        activeCamera = InvalidNode;
    }

    if (Node* parent = getNode(n->parent)) {
        auto& siblings = parent->children;
        siblings.erase(std::remove(siblings.begin(), siblings.end(), id), siblings.end());
    }

    return node_pool_.remove(id);
}

Node* Scene::getNode(NodeID id) {
    return node_pool_.get(id);
}

const Node* Scene::getNode(NodeID id) const {
    return node_pool_.get(id);
}

bool Scene::isNodeValid(NodeID id) const {
    return node_pool_.isValid(id);
}

Component* Scene::getComponent(ComponentID id) {
    if (!id.valid() || id.index >= component_slots_.size()) return nullptr;
    auto& slot = component_slots_[id.index];
    if (slot.generation != id.generation || !slot.value) return nullptr;
    return slot.value.get();
}

const Component* Scene::getComponent(ComponentID id) const {
    if (!id.valid() || id.index >= component_slots_.size()) return nullptr;
    const auto& slot = component_slots_[id.index];
    if (slot.generation != id.generation || !slot.value) return nullptr;
    return slot.value.get();
}

bool Scene::isComponentValid(ComponentID id) const {
    return getComponent(id) != nullptr;
}

ComponentID Scene::insert_component_(std::unique_ptr<Component> comp) {
    uint64_t idx;
    if (!free_component_slots_.empty()) {
        idx = free_component_slots_.back();
        free_component_slots_.pop_back();
        component_slots_[idx].value = std::move(comp);
    } else {
        idx = component_slots_.size();
        component_slots_.push_back(ComponentSlot{std::move(comp), 0});
    }
    return ComponentID{idx, component_slots_[idx].generation};
}

void Scene::erase_from_registry_(std::type_index type, ComponentID id) {
    auto it = registry_.find(type);
    if (it == registry_.end()) return;
    auto& vec = it->second;
    vec.erase(std::remove(vec.begin(), vec.end(), id), vec.end());
}

bool Scene::detach_and_remove_component_(Node& owner, ComponentID cid) {
    Component* comp = getComponent(cid);
    if (!comp) return false;

    comp->onDetach();
    erase_from_registry_(std::type_index(typeid(*comp)), cid);

    auto& slot = component_slots_[cid.index];
    slot.value.reset();
    slot.generation++;
    free_component_slots_.push_back(cid.index);

    auto& comps = owner.components;
    comps.erase(std::remove(comps.begin(), comps.end(), cid), comps.end());

    return true;
}

bool Scene::removeComponent(ComponentID id) {
    Component* comp = getComponent(id);
    if (!comp) return false;
    Node* owner = getNode(comp->owner);
    if (!owner) return false;
    return detach_and_remove_component_(*owner, id);
}

Scene& Component::scene() const {
    return *scene_;
}

Node* Component::node() const {
    return scene_->getNode(owner);
}

}
