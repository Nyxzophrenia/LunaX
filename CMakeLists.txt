cmake_minimum_required(VERSION 3.16)

project(LunaX
    VERSION 0.1.0
    DESCRIPTION "LunaX C++ Engine Prototype"
    LANGUAGES CXX
)

# ── C++17 Standard ────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Collect all source files ──────────────────────────────────
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/engine/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

file(GLOB_RECURSE HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/engine/**/*.h"
)

# ── Executable ────────────────────────────────────────────────
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# ── Include directories ──────────────────────────────────────
# Allow includes relative to the engine root, e.g. "../ecs/Registry.h"
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/core
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/simulation
)

# ── Compiler warnings ────────────────────────────────────────
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ── Output directory ──────────────────────────────────────────
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
