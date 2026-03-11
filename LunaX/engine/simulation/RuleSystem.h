#pragma once

#include "../ecs/Systems.h"
#include "../ecs/Component.h"
#include <functional>
#include <vector>
#include <string>

// ============================================================
// RuleSystem
// ============================================================
// A data-driven system that evaluates user-defined rules
// against entities each frame.
//
// Rules are simple condition→action pairs:
//   - Condition: a function that checks entity state
//   - Action: a function that modifies entity state
//
// Usage:
//   auto& rules = engine.GetSystemManager().AddSystem<RuleSystem>();
//   rules.AddRule("Bounce at boundary",
//       [](Registry& r, Entity e) {
//           auto* t = r.GetComponent<TransformComponent>(e);
//           return t && t->x > 50.0;
//       },
//       [](Registry& r, Entity e) {
//           auto* v = r.GetComponent<VelocityComponent>(e);
//           if (v) v->vx = -v->vx;
//       });
// ============================================================

class RuleSystem : public System
{
public:
    using ConditionFn = std::function<bool(Registry&, Entity)>;
    using ActionFn    = std::function<void(Registry&, Entity)>;

    struct Rule
    {
        std::string name;
        ConditionFn condition;
        ActionFn    action;
    };

    // Register a new rule
    void AddRule(const std::string& name, ConditionFn condition, ActionFn action)
    {
        m_Rules.push_back({name, std::move(condition), std::move(action)});
    }

    // Evaluate all rules against all alive entities
    void Update(Registry& registry, double /*deltaTime*/) override
    {
        const auto& entities = registry.GetAliveEntities();

        for (const auto& rule : m_Rules)
        {
            for (Entity entity : entities)
            {
                if (rule.condition(registry, entity))
                {
                    rule.action(registry, entity);
                }
            }
        }
    }

    // Get number of registered rules
    size_t GetRuleCount() const { return m_Rules.size(); }

private:
    std::vector<Rule> m_Rules;
};
