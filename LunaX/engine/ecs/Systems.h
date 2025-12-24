#pragma once

#include "Registry.h"
#include <vector>
#include <memory>

// System (base class)
// All systems inherit from this.
// Each system runs logic every frame.
class System
{
public:
    virtual ~System() = default;

    // Called once per frame
    virtual void Update(Registry& registry, float deltaTime) = 0;
};

// SystemManager

// Stores and updates all systems.
// Owns systems using smart pointers (no leaks).
class SystemManager
{
public:
    // Add a new system
    template<typename T, typename... Args>
    T& AddSystem(Args&&... args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *system;
        m_Systems.push_back(std::move(system));
        return ref;
    }

    // Update all systems
    void UpdateAll(Registry& registry, float deltaTime)
    {
        for (auto& system : m_Systems)
        {
            system->Update(registry, deltaTime);
        }
    }

private:
    // Stores all systems
    std::vector<std::unique_ptr<System>> m_Systems;
};
