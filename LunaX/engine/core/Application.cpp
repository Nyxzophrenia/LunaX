#include "Application.h"
#include "Time.h"
#include <thread>
#include <iostream>
#include <chrono>

// ============================================================
// Constructor
// ============================================================
Application::Application(int argc, char** argv)
{
    // TODO: Parse CLI arguments
    // TODO: Load engine configuration
    std::cout << "[Application] Created\n";
}

// ============================================================
// Destructor
// ============================================================
Application::~Application()
{
    // Cleanup happens in Shutdown()
}

// ============================================================
// Run
// ============================================================
void Application::Run()
{
    Init();
    MainLoop();
    Shutdown();
}

// ============================================================
// Init
// ============================================================
void Application::Init()
{
    std::cout << "[Application] Init\n";
    m_Engine.Initialize();
}

// ============================================================
// MainLoop
// ============================================================
// Proper fixed-timestep loop with accumulator.
// Physics/logic updates at a fixed rate; rendering is uncapped.
void Application::MainLoop()
{
    std::cout << "[Application] Main loop started\n";

    using clock = std::chrono::steady_clock;
    auto lastTime = clock::now();
    double accumulator = 0.0;

    constexpr double fixedDT = 1.0 / 120.0; // 120 Hz fixed timestep

    while (m_Engine.IsRunning())
    {
        // Calculate frame delta
        auto currentTime = clock::now();
        std::chrono::duration<double> frameDelta = currentTime - lastTime;
        lastTime = currentTime;

        double dt = frameDelta.count();

        // Clamp large frame spikes
        if (dt > 0.1)
            dt = 0.1;

        accumulator += dt;

        // Fixed timestep updates
        while (accumulator >= fixedDT)
        {
            m_Engine.Step(fixedDT);
            accumulator -= fixedDT;
        }

        // Render as fast as possible
        m_Engine.Render();

        // Tiny sleep to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

// ============================================================
// Shutdown
// ============================================================
void Application::Shutdown()
{
    std::cout << "[Application] Shutdown\n";
    m_Engine.Shutdown();
}
