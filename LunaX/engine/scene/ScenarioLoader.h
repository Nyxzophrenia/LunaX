#pragma once

#include "Scenario.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

// ============================================================
// ScenarioLoader
// ============================================================
// Manages a collection of named scenarios.
// Allows registering, loading, and switching between scenes.
//
// Usage:
//   ScenarioLoader loader;
//   loader.Register("level1", myScenario);
//   loader.Load("level1", registry);     // loads level1
//   loader.Load("level2", registry);     // unloads level1, loads level2
// ============================================================

class ScenarioLoader
{
public:
    // Register a scenario by name
    void Register(const std::string& name, std::shared_ptr<Scenario> scenario)
    {
        m_Scenarios[name] = std::move(scenario);
        std::cout << "[ScenarioLoader] Registered: " << name << "\n";
    }

    // Create and register a scenario in one step
    std::shared_ptr<Scenario> Create(const std::string& name)
    {
        auto scenario = std::make_shared<Scenario>(name);
        Register(name, scenario);
        return scenario;
    }

    // Load a scenario by name (unloads current if any)
    bool Load(const std::string& name, Registry& registry)
    {
        auto it = m_Scenarios.find(name);
        if (it == m_Scenarios.end())
        {
            std::cerr << "[ScenarioLoader] Scenario not found: " << name << "\n";
            return false;
        }

        // Unload current scenario first
        if (m_CurrentScenario)
        {
            m_CurrentScenario->Unload(registry);
        }

        // Load the new scenario
        m_CurrentScenario = it->second;
        m_CurrentScenario->Load(registry);
        m_CurrentName = name;

        return true;
    }

    // Unload the current scenario
    void UnloadCurrent(Registry& registry)
    {
        if (m_CurrentScenario)
        {
            m_CurrentScenario->Unload(registry);
            m_CurrentScenario = nullptr;
            m_CurrentName.clear();
        }
    }

    // Get the current scenario name
    const std::string& GetCurrentName() const { return m_CurrentName; }

    // Check if a scenario exists
    bool Has(const std::string& name) const
    {
        return m_Scenarios.find(name) != m_Scenarios.end();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Scenario>> m_Scenarios;
    std::shared_ptr<Scenario> m_CurrentScenario = nullptr;
    std::string m_CurrentName;
};
