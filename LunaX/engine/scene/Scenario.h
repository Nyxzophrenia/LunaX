#pragma once

#include "../ecs/Registry.h"
#include "../ecs/Component.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>

// ============================================================
// Scenario
// ============================================================
// A Scenario represents a "scene" — a named collection of
// entities that can be loaded and unloaded as a group.
//
// Usage:
//   Scenario scene("TestScene");
//   scene.AddEntitySetup([](Registry& r) {
//       Entity e = r.CreateEntity();
//       r.AddComponent<TagComponent>(e, {"Box"});
//       r.AddComponent<TransformComponent>(e, {5.0, 0.0, 0.0});
//   });
//   scene.Load(registry);   // creates the entities
//   scene.Unload(registry); // destroys them
// ============================================================

class Scenario
{
public:
    using EntitySetupFn = std::function<Entity(Registry&)>;

    // Create a named scenario
    explicit Scenario(const std::string& name)
        : m_Name(name)
    {
    }

    // Register an entity setup function
    // Each function creates and configures one entity
    void AddEntitySetup(EntitySetupFn setupFn)
    {
        m_EntitySetups.push_back(std::move(setupFn));
    }

    // Load the scenario — call all setup functions to create entities
    void Load(Registry& registry)
    {
        m_LoadedEntities.clear();

        for (auto& setup : m_EntitySetups)
        {
            Entity entity = setup(registry);
            m_LoadedEntities.push_back(entity);
        }

        std::cout << "[Scenario] Loaded '" << m_Name
                  << "' with " << m_LoadedEntities.size()
                  << " entities\n";
    }

    // Unload the scenario — destroy all entities it created
    void Unload(Registry& registry)
    {
        for (Entity entity : m_LoadedEntities)
        {
            registry.DestroyEntity(entity);
        }

        std::cout << "[Scenario] Unloaded '" << m_Name
                  << "' (" << m_LoadedEntities.size()
                  << " entities destroyed)\n";

        m_LoadedEntities.clear();
    }

    // Getters
    const std::string& GetName() const { return m_Name; }
    size_t GetEntityCount() const { return m_LoadedEntities.size(); }
    const std::vector<Entity>& GetEntities() const { return m_LoadedEntities; }

private:
    std::string m_Name;
    std::vector<EntitySetupFn> m_EntitySetups;
    std::vector<Entity> m_LoadedEntities;
};
