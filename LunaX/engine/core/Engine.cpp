#include "Engine.h"
#include <iostream> // Required for std::cout


// Constructor
// Sets the initial state of the engine.
// - m_Running: controls the main loop
// - m_Paused:  allows update logic to be temporarily disabled
Engine::Engine()
    : m_Running(true), m_Paused(false)
{
}


// Initialize

// Called once at application startup.
// This is where engine systems would normally be created:
// - window
// - renderer
// - input
// - audio
void Engine::Initialize()
{
    std::cout << "[Engine] Initialized\n";
}

// Step (Update)
// Called every frame from the main loop.
// dt = delta time in seconds since the last frame.
// Used to update game logic, physics, AI, etc.
void Engine::Step(double dt)
{
    // If the engine is paused, skip update logic
    // Rendering can still continue if desired
    if (m_Paused)
        return;

    std::cout << "[Engine] Step: dt = " << dt << "\n";
}

// Render
// Called every frame after Step().
// Responsible for drawing the current state to the screen.
void Engine::Render()
{
    std::cout << "[Engine] Render\n";
}

// Shutdown
// Called once when the application is closing.
// This is where engine systems should be destroyed and
// resources released (memory, GPU objects, files, etc.).
void Engine::Shutdown()
{
    std::cout << "[Engine] Shutdown\n";
}

// SetPaused
// Enables or disables update processing.
// Useful for pause menus, debugging, or background states.
void Engine::SetPaused(bool paused)
{
    m_Paused = paused;
}

// IsRunning
// Returns whether the engine should continue running.
// Used by the main loop condition.
bool Engine::IsRunning() const
{
    return m_Running;
}

// Stop
// Signals the engine to stop running.
// Typically called when the window is closed or
// the application wants to exit.
void Engine::Stop()
{
    m_Running = false;
}
