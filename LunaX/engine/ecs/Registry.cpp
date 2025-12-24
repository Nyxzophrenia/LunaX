#include "Registry.h"

// CreateEntity
// Returns a new unique entity ID.
// No memory allocation here.
Entity Registry::CreateEntity()
{
    return m_NextEntity++;
}

// DestroyEntity
// Removes all components that belong to this entity.
// Shared pointers clean up memory automatically.
void Registry::DestroyEntity(Entity entity)
{
    for (auto& [type, componentMap] : m_Components)
    {
        componentMap.erase(entity);
    }
}

// ------------------------------------------------------------
// AddComponent
// ------------------------------------------------------------
// Adds a component to an entity.
// Uses shared_ptr to avoid manual delete.
template<typename T>
void Registry::AddComponent(Entity entity, T component)
{
    auto& componentMap = m_Components[typeid(T)];

    // Store component as shared_ptr<void>
    componentMap[entity] = std::make_shared<T>(std::move(component));
}

// GetComponent
// Returns a pointer to the component if it exists.
// Returns nullptr if not found.
template<typename T>
T* Registry::GetComponent(Entity entity)
{
    auto typeIt = m_Components.find(typeid(T));
    if (typeIt == m_Components.end())
        return nullptr;

    auto entityIt = typeIt->second.find(entity);
    if (entityIt == typeIt->second.end())
        return nullptr;

    return static_cast<T*>(entityIt->second.get());
}

// Explicit template instantiation
// Needed because templates are defined in cpp
template void Registry::AddComponent<int>(Entity, int);
template int* Registry::GetComponent<int>(Entity);
