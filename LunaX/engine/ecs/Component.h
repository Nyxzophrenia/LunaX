#pragma once
#include <string>
#include <memory>

// Base class for all engine components
// Components represent modular pieces of behavior
// that can be attached to game entities.
class Component
{
public:
    // Virtual destructor ensures derived components
    // are properly destroyed when deleted via base pointer
    virtual ~Component() = default;

    // Called once when the component is added to an entity
    virtual void Initialize() {}

    // Called every frame
    // dt = delta time since last frame (seconds)
    virtual void Update(double dt) {}

    // Optional rendering call for components that draw
    virtual void Render() {}

    // Name of the component for debugging / identification
    [[nodiscard]] const std::string& GetName() const noexcept { return name; }

    // Set a name for the component
    void SetName(const std::string& newName) { name = newName; }

protected:
    std::string name = "Component";
};
    