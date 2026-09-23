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

#include "wrench/scene/data.hpp"
#include <string>
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <cassert>

namespace Wrench::Scene {

class Node;
class Component;
class Scene;
class Entity;

class TransformComponent;
class CameraComponent;

class Node {
public:
    std::string name;

    NodeID id;
    NodeID parent = InvalidNode;

    std::vector<NodeID> children;
    std::vector<ComponentID> components;
};

class Component {

friend class Scene;

public:
    virtual ~Component() = default;

    ComponentID id;
    NodeID owner = InvalidNode;

    Scene& scene() const;
    Node* node() const;

    virtual void onAttach() {}
    virtual void onDetach() {}

protected:

private:
    Scene* scene_ = nullptr;
};

class Scene {
public:
    Scene();

    NodeID root() const { return root_; }

    NodeID createNode(NodeID parent = InvalidNode);
    bool removeNode(NodeID id);

    Node* getNode(NodeID id);
    const Node* getNode(NodeID id) const;

    Entity createEntity(NodeID parent = InvalidNode);
    Entity getEntity(NodeID id);

    template<typename T, typename... Args>
    ComponentID createComponent(NodeID parent, Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>);

        Node* n = getNode(parent);
        if (!n) return InvalidComponent;

        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        ComponentID cid = insert_component_(std::move(comp));

        Component* ptr = component_slots_[cid.index].value.get();
        ptr->id = cid;
        ptr->owner = parent;
        ptr->scene_ = this;

        n->components.push_back(cid);
        registry_[std::type_index(typeid(T))].push_back(cid);

        ptr->onAttach();
        return cid;
    }

    bool removeComponent(ComponentID id);

    Component* getComponent(ComponentID id);
    const Component* getComponent(ComponentID id) const;

    template<typename T>
    T* getComponentOfType(NodeID nodeId) {
        Node* n = getNode(nodeId);
        if (!n) return nullptr;
        for (ComponentID cid : n->components) {
            if (auto* c = dynamic_cast<T*>(getComponent(cid))) return c;
        }
        return nullptr;
    }

    template<typename T>
    T* getComponentOfType() {
        auto it = registry_.find(std::type_index(typeid(T)));
        if (it == registry_.end() || it->second.empty()) return nullptr;
        for (ComponentID cid : it->second) {
            if (auto* c = dynamic_cast<T*>(getComponent(cid))) return c;
        }
        return nullptr;
    }

    template<typename T>
    std::vector<T*> getComponentsOfType(NodeID nodeId) {
        std::vector<T*> result;
        Node* n = getNode(nodeId);
        if (!n) return result;
        for (ComponentID cid : n->components) {
            if (auto* c = dynamic_cast<T*>(getComponent(cid))) result.push_back(c);
        }
        return result;
    }

    template<typename T>
    std::vector<T*> getComponentsOfType() {
        std::vector<T*> result;
        auto it = registry_.find(std::type_index(typeid(T)));
        if (it == registry_.end()) return result;
        for (ComponentID cid : it->second) {
            if (auto* c = dynamic_cast<T*>(getComponent(cid))) result.push_back(c);
        }
        return result;
    }

    bool isNodeValid(NodeID id) const;
    bool isComponentValid(ComponentID id) const;

    NodeID activeCamera = InvalidNode;

private:
    struct ComponentSlot {
        std::unique_ptr<Component> value;
        uint64_t generation = 0;
    };

    std::vector<ComponentSlot> component_slots_;
    std::vector<uint64_t> free_component_slots_;
    std::unordered_map<std::type_index, std::vector<ComponentID>> registry_;

    NodeID root_ = InvalidNode;
    Pool<Node, NodeID> node_pool_;

    ComponentID insert_component_(std::unique_ptr<Component> comp);
    void erase_from_registry_(std::type_index type, ComponentID id);
    bool detach_and_remove_component_(Node& owner, ComponentID cid);
};

class Entity {

friend class Scene;

public:
    Entity() = default;

    explicit operator bool() const {
        return valid();
    }

    template<typename T, typename... Args>
    T& addComponent(Args&&... args) {
        ComponentID cid = scene_->createComponent<T>(
            id_, std::forward<Args>(args)...
        );

        T* component = dynamic_cast<T*>(
            scene_->getComponent(cid)
        );

        assert(component);
        return *component;
    }

    template<typename T>
    bool removeComponent(T* component) {
        if (!component) return false;
        return scene_->removeComponent(component->id);
    }

    template<typename T>
    T* getComponent() {
        return scene_->getComponentOfType<T>(id_);
    }

    template<typename T>
    std::vector<T*> getComponents() {
        return scene_->getComponentsOfType<T>(id_);
    }

    Scene& scene() const;
    NodeID id() const;

    Node* node();
    const Node* node() const;

    bool valid() const;

protected:

private:
    Entity(Scene* scene, NodeID id) : id_(id), scene_(scene) {}

    NodeID id_ = InvalidNode;
    Scene* scene_ = nullptr;
};

}
