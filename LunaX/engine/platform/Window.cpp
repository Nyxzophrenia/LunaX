#include "Window.h"
#include <iostream>

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Window::Window(int width, int height, const std::string& title)
    : m_Width(width), m_Height(height), m_Title(title), m_IsOpen(false)
{
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Window::~Window()
{
    Close();
}

// ------------------------------------------------------------
// Initialize
// ------------------------------------------------------------
void Window::Initialize()
{
    // In a real engine, this is where you would:
    // - create OS window (Win32, GLFW, SDL, etc.)
    // - initialize graphics context (OpenGL, Vulkan, DirectX)
    // For now, we just simulate:
    m_IsOpen = true;
    std::cout << "[Window] Initialized: " << m_Width << "x" << m_Height
              << " Title: " << m_Title << "\n";
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Window::Update()
{
    // Poll OS events (keyboard, mouse, window close, etc.)
    // For now, we simulate a check: if ESC pressed or OS close
    // you could call Close()
    // Example simulation: nothing happens

    // Real implementation: call m_CloseCallback() if requested
}

// ------------------------------------------------------------
// Close
// ------------------------------------------------------------
void Window::Close()
{
    if (m_IsOpen)
    {
        m_IsOpen = false;
        std::cout << "[Window] Closed\n";

        // Call user-defined callback
        if (m_CloseCallback)
            m_CloseCallback();
    }
}
