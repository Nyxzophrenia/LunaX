#pragma once

#include <iostream>

#include "../ecs/Registry.h"
#include "../ecs/Systems.h"
#include "../platform/Window.h"
#include "../platform/Input.h"
#include "../renderer/ConsoleRenderer.h"
#include "../simulation/Simulation.h"
#include "../scene/ScenarioLoader.h"

// ============================================================
// Engine
// ============================================================
// Central controller that owns the ECS registry, system
// manager, and window. Provides Initialize/Step/Render/Shutdown
// lifecycle methods called by the Application main loop.
// ============================================================

class Engine
{
public:
    Engine();

    void Initialize();     // Start engine and subsystems
    void Step(double dt);  // Update all systems
    void Render();         // Draw current state
    void Shutdown();       // Clean up all resources

    void SetPaused(bool paused);
    bool IsRunning() const;
    void Stop();

    // Access to ECS
    Registry& GetRegistry() { return m_Registry; }
    const Registry& GetRegistry() const { return m_Registry; }
    SystemManager& GetSystemManager() { return m_SystemManager; }

    // Access to Window
    Window& GetWindow() { return m_Window; }

    // Access to Simulation
    Simulation& GetSimulation() { return m_Simulation; }

    // Access to Scenes
    ScenarioLoader& GetSceneLoader() { return m_SceneLoader; }

private:
    bool m_Running;
    bool m_Paused;

    Registry m_Registry;
    SystemManager m_SystemManager;
    Window m_Window;
    ConsoleRenderer m_Renderer;
    Simulation m_Simulation;
    ScenarioLoader m_SceneLoader;
};
