#pragma once
// Prevents this file from being included more than once

#include <string>      // For window title
#include <cstdint>     // Fixed-size integers (not used yet, but common in engines)
#include <functional>  // For callbacks

// Simple window class for the engine
class Window
{
public:
    // Function called when the window closes
    using CloseCallback = std::function<void()>;

    // Default constructor (uses default size and title)
    Window() = default;

    // Constructor with custom size and title
    Window(int width, int height, const std::string& title);

    // Destructor, makes sure the window is closed
    ~Window();

    // Creates the window
    void Initialize();

    // Called every frame to handle window events
    void Update();

    // Closes the window
    void Close();

    // Returns true if the window is open
    [[nodiscard]] bool IsOpen() const noexcept { return m_IsOpen; }

    // Set a function to call when the window closes
    void SetCloseCallback(CloseCallback callback) { m_CloseCallback = callback; }

    // Get window width
    int GetWidth() const noexcept { return m_Width; }

    // Get window height
    int GetHeight() const noexcept { return m_Height; }

    // Get window title
    const std::string& GetTitle() const noexcept { return m_Title; }

private:
    // Window size
    int m_Width  = 1280;
    int m_Height = 720;

    // Window title
    std::string m_Title = "Engine Window";

    // True while the window is open
    bool m_IsOpen = false;

    // Called when the window is closed
    CloseCallback m_CloseCallback = nullptr;
};
