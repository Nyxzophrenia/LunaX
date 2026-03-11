#pragma once

#include "../ecs/Systems.h"
#include "PhysicsSystem.h"
#include "RuleSystem.h"
#include <memory>
#include <iostream>

// ============================================================
// Simulation
// ============================================================
// High-level manager that owns and coordinates simulation
// sub-systems (physics, rules, etc.).
//
// The Simulation registers its systems with the engine's
// SystemManager so they run automatically each frame.
//
// Usage:
//   Simulation sim;
//   sim.Initialize(systemManager);
//   sim.GetRuleSystem().AddRule(...);
// ============================================================

class Simulation
{
public:
    // Register simulation systems with the engine
    void Initialize(SystemManager& systemManager)
    {
        m_Physics = &systemManager.AddSystem<PhysicsSystem>();
        m_Rules   = &systemManager.AddSystem<RuleSystem>();

        std::cout << "[Simulation] Initialized (Physics + Rules)\n";
    }

    // Access sub-systems for configuration
    PhysicsSystem& GetPhysicsSystem() { return *m_Physics; }
    RuleSystem&    GetRuleSystem()    { return *m_Rules; }

private:
    PhysicsSystem* m_Physics = nullptr;
    RuleSystem*    m_Rules   = nullptr;
};
