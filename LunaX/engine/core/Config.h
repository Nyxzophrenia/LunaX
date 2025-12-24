#pragma once
#include <string>
#include <cstdint>

class Config final
{
public:
    Config() = default;

    // Load configuration from file (JSON / YAML later)
    [[nodiscard]]
    bool LoadFromFile(const std::string& path);

    // Getters (read-only access)
    double GetFixedTimestep() const noexcept { return fixedTimestep; }
    int GetWindowWidth() const noexcept { return windowWidth; }
    int GetWindowHeight() const noexcept { return windowHeight; }
    bool IsRenderingEnabled() const noexcept { return renderEnabled; }

private:
    //  Timing 
    static constexpr double DefaultFixedTimestep = 1.0 / 120.0; // seconds
    double fixedTimestep = DefaultFixedTimestep;

    //  Window 
    static constexpr int DefaultWindowWidth  = 1920;
    static constexpr int DefaultWindowHeight = 1080;
    int windowWidth  = DefaultWindowWidth;
    int windowHeight = DefaultWindowHeight;

    //  Rendering 
    bool renderEnabled = true;
};
