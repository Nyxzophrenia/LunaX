#include "Window.h"
#include <iostream>

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
// Stores window settings (size and title).
// Does NOT create the actual OS window yet.
// That is deferred to Initialize().
Window::Window(int width, int height, const std::string& title)
    : m_Width(width),
      m_Height(height),
      m_Title(title),
      m_IsOpen(false) // Window starts closed
{
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
// Ensures the window is properly closed when the object is destroyed.
Window::~Window()
{
    Close();
}

// ------------------------------------------------------------
// Initialize
// ------------------------------------------------------------
// Creates and initializes the window.
// In a real engine, this is where platform-specific code would live.
void Window::Initialize()
{
    // Normally here you would:
    // - Create the OS window (Win32 / GLFW / SDL)
    // - Create a graphics context (OpenGL / Vulkan / DirectX)
    // - Register event callbacks

    // For now, we simulate successful window creation
    m_IsOpen = true;

    std::cout << "[Window] Initialized: "
              << m_Width << "x" << m_Height
              << " Title: " << m_Title << "\n";
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
// Called once per frame by the engine.
// Used to process window events.
void Window::Update()
{
    // In a real implementation, this would:
    // - Poll OS events
    // - Check keyboard/mouse input
    // - Detect window close requests

    // Example:
    // if (OS requested close)
    //     Close();

    // Currently this is a placeholder
}

// ------------------------------------------------------------
// Close
// ------------------------------------------------------------
// Closes the window and notifies the engine.
void Window::Close()
{
    // Prevent closing the window multiple times
    if (m_IsOpen)
    {
        m_IsOpen = false;

        std::cout << "[Window] Closed\n";

        // If a close callback is registered, call it
        // This lets the engine know the window was closed
        if (m_CloseCallback)
            m_CloseCallback();
    }
}
