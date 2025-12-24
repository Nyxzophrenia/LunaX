#pragma once
#include <string>
#include <cstdint>
#include <functional>

// ------------------------------------------------------------
// Simple Window class for engine
// Handles creation, update, and basic events
// ------------------------------------------------------------
class Window
{
public:
    // Callback type for close events
    using CloseCallback = std::function<void()>;

    Window() = default;
    Window(int width, int height, const std::string& title);

    ~Window();

    // Create the window
    void Initialize();

    // Poll window events (input, close, etc.)
    void Update();

    // Close the window
    void Close();

    // Check if the window is still open
    [[nodiscard]] bool IsOpen() const noexcept { return m_IsOpen; }

    // Set the callback to call when window closes
    void SetCloseCallback(CloseCallback callback) { m_CloseCallback = callback; }

    // Getters
    int GetWidth() const noexcept { return m_Width; }
    int GetHeight() const noexcept { return m_Height; }
    const std::string& GetTitle() const noexcept { return m_Title; }

private:
    int m_Width  = 1280;
    int m_Height = 720;
    std::string m_Title = "Engine Window";

    bool m_IsOpen = false;

    CloseCallback m_CloseCallback = nullptr;
};
