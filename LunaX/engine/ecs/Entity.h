#pragma once

#include <cstdint>
#include <limits>

// ============================================================
// Entity
// ============================================================
// An Entity is a lightweight identifier (uint32_t).
//
// Layout (32 bits):
//   [31..24] Generation (8 bits)  — incremented on reuse
//   [23.. 0] Index     (24 bits)  — unique slot index
//
// The generation field allows the engine to detect stale
// entity handles after an entity has been destroyed and its
// index recycled.
// ============================================================

using Entity = std::uint32_t;

// Sentinel value representing "no entity"
constexpr Entity NullEntity = 0;

// Bit layout constants
constexpr uint32_t EntityIndexBits      = 24;
constexpr uint32_t EntityGenerationBits = 8;
constexpr uint32_t EntityIndexMask      = (1u << EntityIndexBits) - 1;       // 0x00FFFFFF
constexpr uint32_t EntityGenerationMask = (1u << EntityGenerationBits) - 1;  // 0x000000FF

// Extract the index portion of an entity handle
inline constexpr uint32_t GetEntityIndex(Entity entity) noexcept
{
    return entity & EntityIndexMask;
}

// Extract the generation portion of an entity handle
inline constexpr uint32_t GetEntityGeneration(Entity entity) noexcept
{
    return (entity >> EntityIndexBits) & EntityGenerationMask;
}

// Build an entity handle from an index and generation
inline constexpr Entity MakeEntity(uint32_t index, uint32_t generation) noexcept
{
    return ((generation & EntityGenerationMask) << EntityIndexBits) | (index & EntityIndexMask);
}

// Check whether an entity handle is valid (non-null)
inline constexpr bool IsValidEntity(Entity entity) noexcept
{
    return entity != NullEntity;
}
