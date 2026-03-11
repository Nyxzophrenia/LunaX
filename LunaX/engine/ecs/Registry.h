#pragma once

#include "Entity.h"

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <iostream>
#include <queue>

// ============================================================
// Registry
// ============================================================
// Central storage for all entities and their components.
// Supports entity recycling with generation tracking.
// ============================================================

class Registry
{
public:
    // ----------------------------------------------------------
    // Entity Management
    // ----------------------------------------------------------

    // Creates a new entity (or recycles a destroyed one)
    Entity CreateEntity()
    {
        Entity entity = NullEntity;

        if (!m_FreeList.empty())
        {
            // Recycle: reuse index with incremented generation
            uint32_t index = m_FreeList.front();
            m_FreeList.pop();

            uint32_t gen = m_Generations[index];
            entity = MakeEntity(index, gen);
        }
        else
        {
            // Fresh entity
            uint32_t index = m_NextIndex++;
            if (index >= m_Generations.size())
                m_Generations.push_back(0);

            entity = MakeEntity(index, 0);
        }

        m_AliveEntities.push_back(entity);
        return entity;
    }

    // Destroys an entity and removes all its components
    void DestroyEntity(Entity entity)
    {
        if (!IsAlive(entity))
            return;

        // Remove all components for this entity
        for (auto& [type, componentMap] : m_Components)
        {
            componentMap.erase(entity);
        }

        // Increment generation for this index slot
        uint32_t index = GetEntityIndex(entity);
        if (index < m_Generations.size())
        {
            m_Generations[index]++;
        }

        // Add index to free list for recycling
        m_FreeList.push(index);

        // Remove from alive list
        for (auto it = m_AliveEntities.begin(); it != m_AliveEntities.end(); ++it)
        {
            if (*it == entity)
            {
                m_AliveEntities.erase(it);
                break;
            }
        }
    }

    // Check if an entity handle is still alive (valid generation)
    bool IsAlive(Entity entity) const
    {
        if (!IsValidEntity(entity))
            return false;

        uint32_t index = GetEntityIndex(entity);
        uint32_t gen = GetEntityGeneration(entity);

        if (index >= m_Generations.size())
            return false;

        return m_Generations[index] == gen;
    }

    // Get all currently alive entities
    const std::vector<Entity>& GetAliveEntities() const
    {
        return m_AliveEntities;
    }

    // ----------------------------------------------------------
    // Component Management (templates — must be in header)
    // ----------------------------------------------------------

    // Attach a component of type T to an entity
    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        if (!IsAlive(entity))
        {
            std::cerr << "[Registry] Cannot add component to dead entity\n";
            return;
        }

        auto& componentMap = m_Components[typeid(T)];
        componentMap[entity] = std::make_shared<T>(std::move(component));
    }

    // Get a pointer to an entity's component (nullptr if missing)
    template<typename T>
    T* GetComponent(Entity entity)
    {
        auto typeIt = m_Components.find(typeid(T));
        if (typeIt == m_Components.end())
            return nullptr;

        auto entityIt = typeIt->second.find(entity);
        if (entityIt == typeIt->second.end())
            return nullptr;

        return static_cast<T*>(entityIt->second.get());
    }

    // Check if an entity has a component of type T
    template<typename T>
    bool HasComponent(Entity entity) const
    {
        auto typeIt = m_Components.find(typeid(T));
        if (typeIt == m_Components.end())
            return false;

        return typeIt->second.find(entity) != typeIt->second.end();
    }

    // Remove a component of type T from an entity
    template<typename T>
    void RemoveComponent(Entity entity)
    {
        auto typeIt = m_Components.find(typeid(T));
        if (typeIt == m_Components.end())
            return;

        typeIt->second.erase(entity);
    }

    // Get all entities that have a component of type T
    template<typename T>
    std::vector<Entity> GetEntitiesWithComponent() const
    {
        std::vector<Entity> result;

        auto typeIt = m_Components.find(typeid(T));
        if (typeIt == m_Components.end())
            return result;

        for (const auto& [entity, ptr] : typeIt->second)
        {
            result.push_back(entity);
        }

        return result;
    }

private:
    // Index counter for fresh entities (1-based, 0 = NullEntity)
    uint32_t m_NextIndex = 1;

    // Generation counter per index slot (for stale-handle detection)
    std::vector<uint32_t> m_Generations = {0}; // slot 0 reserved for NullEntity

    // Recycled index slots
    std::queue<uint32_t> m_FreeList;

    // Currently alive entity handles
    std::vector<Entity> m_AliveEntities;

    // Component storage: type -> { entity -> component_ptr }
    std::unordered_map<
        std::type_index,
        std::unordered_map<Entity, std::shared_ptr<void>>
    > m_Components;
};
