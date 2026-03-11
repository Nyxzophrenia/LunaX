#pragma once

#include "Registry.h"
#include <vector>
#include <memory>

// ============================================================
// System (Base Class)
// ============================================================
// All systems inherit from this.
// Each system processes entities with specific components
// every frame.
// ============================================================

class System
{
public:
    virtual ~System() = default;

    // Called once per frame with the registry and delta time
    virtual void Update(Registry& registry, double deltaTime) = 0;
};


// ============================================================
// SystemManager
// ============================================================
// Stores and updates all registered systems.
// Owns systems via unique_ptr (automatic cleanup).
// ============================================================

class SystemManager
{
public:
    // Add a new system (returns reference for chaining)
    template<typename T, typename... Args>
    T& AddSystem(Args&&... args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *system;
        m_Systems.push_back(std::move(system));
        return ref;
    }

    // Update all systems in registration order
    void UpdateAll(Registry& registry, double deltaTime)
    {
        for (auto& system : m_Systems)
        {
            system->Update(registry, deltaTime);
        }
    }

private:
    std::vector<std::unique_ptr<System>> m_Systems;
};
