#pragma once
#include "Engine.h"

class Application {
public:
    Application(int argc, char** argv); // TODO: Store config & run mode
    ~Application();                     // TODO: Clean shutdown

    void Run();                          // TODO: Main loop

private:
    void Init();                          // TODO: Initialize subsystems
    void MainLoop();                      // TODO: Fixed timestep loop
    void Shutdown();                      // TODO: Shutdown subsystems

    Engine m_Engine;                      // TODO: Expand with window/editor references
};
