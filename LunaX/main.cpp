#include <chrono>
#include <thread>
#include <exception>
#include <iostream>

#include "Engine.h"

int main()
{
    try
    {
        Engine engine;

        // Initialize engine (allocate resources)
        engine.Initialize();

        using clock = std::chrono::steady_clock;
        auto lastTime = clock::now();
        double accumulator = 0.0;

        constexpr double fixedDT = 1.0 / 120.0; // 120 Hz fixed timestep

        // Main loop
        while (engine.IsRunning())
        {
            auto currentTime = clock::now();
            std::chrono::duration<double> frameDelta = currentTime - lastTime;
            lastTime = currentTime;

            double dt = frameDelta.count();
            accumulator += dt;

            // Fixed timestep updates
            while (accumulator >= fixedDT)
            {
                engine.Step(fixedDT); // game logic, physics, AI
                accumulator -= fixedDT;
            }

            // Render as fast as possible (uncapped FPS)
            engine.Render();

            // Optional: tiny sleep to reduce CPU usage (lightweight)
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }

        // Shutdown engine (release resources)
        engine.Shutdown();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown fatal error occurred." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
