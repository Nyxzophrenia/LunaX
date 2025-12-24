#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>

using Entity = std::uint32_t;

class Registry
{
public:
    Entity CreateEntity();
    void DestroyEntity(Entity entity);

    template<typename T>
    void AddComponent(Entity entity, T component);

    template<typename T>
    T* GetComponent(Entity entity);

private:
    Entity m_NextEntity = 1;

    // Stores components by type
    std::unordered_map<
        std::type_index,
        std::unordered_map<Entity, std::shared_ptr<void>>
    > m_Components;
};
