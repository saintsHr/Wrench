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

#include <cstdint>
#include <functional>
#include <optional>
#include <vector>
#include <utility>
#include <deque>

namespace Wrench::Scene {

template<typename Tag>
struct Handle {
    uint64_t index = 0xFFFFFFFFFFFFFFFF;
    uint64_t generation = 0;

    bool valid() const { return index != 0xFFFFFFFFFFFFFFFF; }
    friend bool operator==(const Handle&, const Handle&) = default;
};

struct NodeTag {};
struct ComponentTag {};

using NodeID = Handle<NodeTag>;
using ComponentID = Handle<ComponentTag>;

constexpr NodeID InvalidNode;
constexpr ComponentID InvalidComponent;

template<typename T, typename IdType>
class Pool {
public:
    template<typename... Args>
    IdType emplace(Args&&... args) {
        uint64_t idx;

        if (!freeList_.empty()) {
            idx = freeList_.back();
            freeList_.pop_back();
            slots_[idx].value.emplace(std::forward<Args>(args)...);
        } else {
            idx = static_cast<uint64_t>(slots_.size());
            slots_.emplace_back();
            slots_[idx].value.emplace(std::forward<Args>(args)...);
        }

        return IdType{idx, slots_[idx].generation};
    }

    bool remove(IdType id) {
        if (!isValid(id)) return false;
        slots_[id.index].value.reset();
        slots_[id.index].generation++;
        freeList_.push_back(id.index);
        return true;
    }

    T* get(IdType id) {
        if (!isValid(id)) return nullptr;
        return &*slots_[id.index].value;
    }

    const T* get(IdType id) const {
        if (!isValid(id)) return nullptr;
        return &*slots_[id.index].value;
    }

    bool isValid(IdType id) const {
        return id.valid()
            && id.index < slots_.size()
            && slots_[id.index].generation == id.generation
            && slots_[id.index].value.has_value();
    }

private:
    struct Slot {
        std::optional<T> value;
        uint64_t generation = 0;
    };

    std::deque<Slot> slots_;
    std::vector<uint64_t> freeList_;
};

}

namespace std {

template<typename Tag>
struct hash<Wrench::Scene::Handle<Tag>> {
    size_t operator()(const Wrench::Scene::Handle<Tag>& h) const noexcept {
        return (size_t(h.index) << 32) ^ h.generation;
    }
};

}
