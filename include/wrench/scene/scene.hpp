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

#include <string>
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace Wrench::Scene {

class Node;
class Component;
class Scene;

class TransformComponent;
class CameraComponent;

class Node {
    friend class Scene;

public:
    std::string name;

    Node* parent = nullptr;
    std::vector<std::unique_ptr<Node>> children;

    explicit Node(Scene& scene);
    virtual ~Node();

    Scene& scene();
    TransformComponent& transform();

    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>);
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = comp.get();
        attach_component_(std::move(comp), std::type_index(typeid(T)));
        return ptr;
    }

    template<typename T>
    T* getComponent() {
        for (auto& c : components_) {
            if (auto* casted = dynamic_cast<T*>(c.get())) return casted;
        }
        return nullptr;
    }

    template<typename T>
    std::vector<T*> getComponents() {
        std::vector<T*> result;
        for (auto& c : components_) {
            if (auto* casted = dynamic_cast<T*>(c.get())) result.push_back(casted);
        }
        return result;
    }

    template<typename T>
    T* addChild() {
        auto child = std::make_unique<T>(*scene_);
        T* ptr = child.get();
        child->parent = this;
        children.push_back(std::move(child));
        return ptr;
    }

    bool removeComponent(Component* component);
    bool removeChild(Node* child);

protected:

private:
    Scene* scene_ = nullptr;
    TransformComponent* transform_ = nullptr;
    std::vector<std::unique_ptr<Component>> components_;

    void attach_component_(std::unique_ptr<Component> comp, std::type_index type);
};

class Component {
    friend class Node;

public:
    virtual ~Component() = default;

    Node* node() const;
    TransformComponent& transform() const;

protected:
    Component() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}

private:
    Node* node_ = nullptr;
};

class Scene {
    friend class Node;

public:
    Scene();
    ~Scene();

    CameraComponent* activeCamera = nullptr;

    Node& root();
    const Node& root() const;

    template<typename T>
    T* addNode(Node* parent = nullptr) {
        Node* target = parent ? parent : root_.get();
        return target->addChild<T>();
    }

    Node* createNode(Node* parent = nullptr);

    template<typename T>
    std::vector<T*> getComponents() {
        std::vector<T*> result;
        auto it = registry_.find(std::type_index(typeid(T)));
        if (it == registry_.end()) return result;
        for (auto* c : it->second) result.push_back(static_cast<T*>(c));
        return result;
    }

    bool removeNode(Node* node);

private:
    bool destructing_ = false;

    std::unordered_map<std::type_index, std::vector<Component*>> registry_;
    std::unique_ptr<Node> root_;

    void register_component_(std::type_index type, Component* comp);
    void unregister_component_(std::type_index type, Component* comp);
};

}
