#pragma once

#include <string>

// ============================================================
// Component (Base Class)
// ============================================================
// Components represent modular pieces of data that can be
// attached to entities. They are plain data containers —
// behavior lives in Systems.
// ============================================================

class Component
{
public:
    virtual ~Component() = default;

    // Called once when the component is added to an entity
    virtual void Initialize() {}

    // Called every frame (dt = delta time in seconds)
    virtual void Update(double dt) {}

    // Optional rendering call
    virtual void Render() {}

    // Name for debugging / identification
    [[nodiscard]] const std::string& GetName() const noexcept { return name; }
    void SetName(const std::string& newName) { name = newName; }

protected:
    std::string name = "Component";
};


// ============================================================
// Built-in Components
// ============================================================
// Simple structs that store data. No inheritance needed —
// the Registry stores them by type, not by base pointer.
// ============================================================

// Position, rotation, and scale in 3D space
struct TransformComponent
{
    double x = 0.0, y = 0.0, z = 0.0;       // Position
    double rotX = 0.0, rotY = 0.0, rotZ = 0.0; // Rotation (degrees)
    double scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0; // Scale
};

// Velocity in 3D space
struct VelocityComponent
{
    double vx = 0.0, vy = 0.0, vz = 0.0;
};

// Human-readable name tag for an entity
struct TagComponent
{
    std::string tag = "Unnamed";
};