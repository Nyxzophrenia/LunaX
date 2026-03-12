#pragma once

#include "../ecs/Systems.h"
#include "../ecs/Registry.h"
#include "../ecs/Component.h"
#include <iostream>

// ============================================================
// PhysicsSystem
// ============================================================
// Applies velocity to transform each frame.
// This is a basic Euler integration step:
//   position += velocity * deltaTime
//
// Entities must have both TransformComponent and
// VelocityComponent to be processed.
// ============================================================

class PhysicsSystem : public System
{
public:
    void Update(Registry& registry, double deltaTime) override
    {
        auto entities = registry.GetEntitiesWithComponent<VelocityComponent>();

        for (Entity entity : entities)
        {
            auto* transform = registry.GetComponent<TransformComponent>(entity);
            auto* velocity  = registry.GetComponent<VelocityComponent>(entity);

            if (!transform || !velocity)
                continue;

            // Euler integration: pos += vel * dt
            transform->x += velocity->vx * deltaTime;
            transform->y += velocity->vy * deltaTime;
            transform->z += velocity->vz * deltaTime;
        }
    }
};
