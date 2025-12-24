#pragma once

#include <iostream>

// Controls the engine
class Engine
{
public:
    Engine();              // Sets default values
    void Initialize();     // Start engine
    void Step(double dt);  // Update logic
    void Render();         // Draw stuff
    void Shutdown();       // Clean up

    void SetPaused(bool paused);
    bool IsRunning() const;
    void Stop();

private:
    bool m_Running; // Main loop flag
    bool m_Paused;  // Pause flag
};
