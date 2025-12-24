#include "Application.h"
#include "Time.h"
#include <thread>
#include <iostream>

Application::Application(int argc, char** argv)
{
    // TODO: Parse CLI arguments
    // TODO: Load engine configuration
    std::cout << "[Application] Created\n";
}

Application::~Application()
{
    // TODO: Cleanup happens in Shutdown
}

void Application::Run()
{
    Init();       // TODO: Initialize subsystems
    MainLoop();   // TODO: Start main simulation loop
    Shutdown();   // TODO: Clean shutdown
}

void Application::Init()
{
    std::cout << "[Application] Init\n";
    m_Engine.Initialize();

    // TODO: Initialize logging
    // TODO: Initialize window (if enabled)
    // TODO: Initialize editor (if enabled)
}

void Application::MainLoop()
{
    std::cout << "[Application] Main loop started\n";

    const double fixedTimeStep = 0.016; // 60Hz
    for (int i = 0; i < 5; ++i) // Minimal demo loop
    {
        Time::Update();
        double dt = Time::Delta();

        m_Engine.Step(fixedTimeStep);
        m_Engine.Render(); // TODO: Conditional render if window enabled

        // TODO: Poll input/events (if window exists)
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // simulate frame
    }
}

void Application::Shutdown()
{
    std::cout << "[Application] Shutdown\n";
    m_Engine.Shutdown();

    // TODO: Save metrics
    // TODO: Cleanup window/editor
}
