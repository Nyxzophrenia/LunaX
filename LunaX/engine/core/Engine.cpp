#include "Engine.h"
#include "../ecs/Component.h"
#include <iostream>

// ============================================================
// Constructor
// ============================================================
Engine::Engine()
    : m_Running(true), m_Paused(false)
{
}

// ============================================================
// Initialize
// ============================================================
// Sets up the window, creates demo entities to prove the ECS
// is working, and registers any built-in systems.
void Engine::Initialize()
{
    // --- Window ---
    m_Window.Initialize();
    m_Window.SetCloseCallback([this]() {
        Stop();
    });

    // --- Simulation (registers PhysicsSystem + RuleSystem) ---
    m_Simulation.Initialize(m_SystemManager);

    // --- Demo: Bounce rule (reverses velocity at x > 20) ---
    m_Simulation.GetRuleSystem().AddRule("Bounce at boundary",
        [](Registry& r, Entity e) {
            auto* t = r.GetComponent<TransformComponent>(e);
            return t && (t->x > 20.0 || t->x < -20.0);
        },
        [](Registry& r, Entity e) {
            auto* v = r.GetComponent<VelocityComponent>(e);
            if (v) v->vx = -v->vx;
        });

    // --- Demo: Create entities to test the ECS ---
    Entity player = m_Registry.CreateEntity();
    m_Registry.AddComponent<TagComponent>(player, {"Player"});
    m_Registry.AddComponent<TransformComponent>(player, {0.0, 0.0, 0.0});
    m_Registry.AddComponent<VelocityComponent>(player, {5.0, 2.0, 0.0});

    Entity obstacle = m_Registry.CreateEntity();
    m_Registry.AddComponent<TagComponent>(obstacle, {"Obstacle"});
    m_Registry.AddComponent<TransformComponent>(obstacle, {10.0, 0.0, 0.0});

    std::cout << "[Engine] Initialized — "
              << m_Registry.GetAliveEntities().size()
              << " entities created\n";
}

// ============================================================
// Step (Update)
// ============================================================
// Called at a fixed timestep. Runs all registered systems.
void Engine::Step(double dt)
{
    if (m_Paused)
        return;

    // Poll keyboard input
    Input::Update();

    // Escape key stops the engine
    if (Input::IsKeyPressed(Key::Escape))
    {
        Stop();
        return;
    }

    // Update all ECS systems
    m_SystemManager.UpdateAll(m_Registry, dt);

    // Update window events (poll close, etc.)
    m_Window.Update();
}

// ============================================================
// Render
// ============================================================
// Called every frame after Step(). Will forward to a renderer
// in future priorities.
void Engine::Render()
{
    m_Renderer.Render(m_Window, m_Registry);
}

// ============================================================
// Shutdown
// ============================================================
void Engine::Shutdown()
{
    m_Window.Close();
    std::cout << "[Engine] Shutdown\n";
}

// ============================================================
// State control
// ============================================================
void Engine::SetPaused(bool paused)
{
    m_Paused = paused;
}

bool Engine::IsRunning() const
{
    return m_Running;
}

void Engine::Stop()
{
    m_Running = false;
}
