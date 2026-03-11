#pragma once

#include "../ecs/Registry.h"
#include "../ecs/Component.h"
#include "../platform/Window.h"
#include "Colors.h"
#include "Log.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// ============================================================
// ConsoleRenderer
// ============================================================
// Draws entity information to the console window as text.
// This is a lightweight, terminal-based renderer suitable for
// debugging and prototyping without a GPU graphics API.
//
// Usage:
//   ConsoleRenderer renderer;
//   renderer.Render(window, registry);
// ============================================================

class ConsoleRenderer
{
public:
    // Render all entities with TransformComponent to the console
    void Render(Window& window, Registry& registry)
    {
        // Clear the console
        window.Clear();

        // Header
        window.SetCursorPosition(0, 0);
        std::cout << Color::BrightCyan << Color::Bold
                  << "=== LunaX Engine ===" << Color::Reset << "\n\n";

        // Entity list
        const auto& entities = registry.GetAliveEntities();
        int row = 2;

        for (Entity entity : entities)
        {
            window.SetCursorPosition(0, row);

            // Entity ID
            std::cout << Color::BrightBlack << "Entity "
                      << GetEntityIndex(entity)
                      << Color::Reset;

            // Tag (name)
            if (registry.HasComponent<TagComponent>(entity))
            {
                auto* tag = registry.GetComponent<TagComponent>(entity);
                std::cout << " " << Color::Bold << Color::BrightWhite
                          << tag->tag << Color::Reset;
            }

            // Transform (position)
            if (registry.HasComponent<TransformComponent>(entity))
            {
                auto* t = registry.GetComponent<TransformComponent>(entity);
                std::cout << " " << Color::Green
                          << "pos(" << std::fixed << std::setprecision(1)
                          << t->x << ", " << t->y << ", " << t->z << ")"
                          << Color::Reset;
            }

            // Velocity
            if (registry.HasComponent<VelocityComponent>(entity))
            {
                auto* v = registry.GetComponent<VelocityComponent>(entity);
                std::cout << " " << Color::Yellow
                          << "vel(" << std::fixed << std::setprecision(1)
                          << v->vx << ", " << v->vy << ", " << v->vz << ")"
                          << Color::Reset;
            }

            row++;
        }

        // Footer
        window.SetCursorPosition(0, row + 1);
        std::cout << Color::BrightBlack
                  << "Entities: " << entities.size()
                  << " | Press ESC to exit"
                  << Color::Reset;
    }
};
