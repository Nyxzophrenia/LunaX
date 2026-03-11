#pragma once

#include <unordered_map>
#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#endif

// ============================================================
// Input
// ============================================================
// Keyboard input system using polling.
//
// On Windows, uses GetAsyncKeyState to poll key states.
// On other platforms, falls back to a basic stub.
//
// Usage:
//   Input::Update();                    // call once per frame
//   if (Input::IsKeyDown(Key::W)) { }   // check state
//   if (Input::IsKeyPressed(Key::Space)) { } // just pressed
// ============================================================

// Common key codes (maps to Windows VK codes on Win32)
enum class Key : int
{
    // Letters
    A = 'A', B = 'B', C = 'C', D = 'D',
    E = 'E', F = 'F', G = 'G', H = 'H',
    I = 'I', J = 'J', K = 'K', L = 'L',
    M = 'M', N = 'N', O = 'O', P = 'P',
    Q = 'Q', R = 'R', S = 'S', T = 'T',
    U = 'U', V = 'V', W = 'W', X = 'X',
    Y = 'Y', Z = 'Z',

    // Numbers
    Num0 = '0', Num1 = '1', Num2 = '2', Num3 = '3',
    Num4 = '4', Num5 = '5', Num6 = '6', Num7 = '7',
    Num8 = '8', Num9 = '9',

    // Special keys
    Space  = 0x20,
    Enter  = 0x0D,
    Escape = 0x1B,
    Tab    = 0x09,

    // Arrow keys
    Up    = 0x26,
    Down  = 0x28,
    Left  = 0x25,
    Right = 0x27,

    // Modifiers
    Shift   = 0x10,
    Control = 0x11,
    Alt     = 0x12,

    // Function keys
    F1  = 0x70, F2  = 0x71, F3  = 0x72, F4  = 0x73,
    F5  = 0x74, F6  = 0x75, F7  = 0x76, F8  = 0x77,
    F9  = 0x78, F10 = 0x79, F11 = 0x7A, F12 = 0x7B,
};

class Input
{
public:
    // Call once per frame before processing input
    static void Update()
    {
        // Swap current → previous
        s_PreviousKeys = s_CurrentKeys;
        s_CurrentKeys.clear();

#ifdef _WIN32
        // Poll all keys we care about
        PollKey(Key::A); PollKey(Key::B); PollKey(Key::C); PollKey(Key::D);
        PollKey(Key::E); PollKey(Key::F); PollKey(Key::G); PollKey(Key::H);
        PollKey(Key::I); PollKey(Key::J); PollKey(Key::K); PollKey(Key::L);
        PollKey(Key::M); PollKey(Key::N); PollKey(Key::O); PollKey(Key::P);
        PollKey(Key::Q); PollKey(Key::R); PollKey(Key::S); PollKey(Key::T);
        PollKey(Key::U); PollKey(Key::V); PollKey(Key::W); PollKey(Key::X);
        PollKey(Key::Y); PollKey(Key::Z);

        PollKey(Key::Num0); PollKey(Key::Num1); PollKey(Key::Num2);
        PollKey(Key::Num3); PollKey(Key::Num4); PollKey(Key::Num5);
        PollKey(Key::Num6); PollKey(Key::Num7); PollKey(Key::Num8);
        PollKey(Key::Num9);

        PollKey(Key::Space);  PollKey(Key::Enter); PollKey(Key::Escape);
        PollKey(Key::Tab);    PollKey(Key::Up);    PollKey(Key::Down);
        PollKey(Key::Left);   PollKey(Key::Right);
        PollKey(Key::Shift);  PollKey(Key::Control); PollKey(Key::Alt);

        PollKey(Key::F1); PollKey(Key::F2); PollKey(Key::F3); PollKey(Key::F4);
        PollKey(Key::F5); PollKey(Key::F6); PollKey(Key::F7); PollKey(Key::F8);
        PollKey(Key::F9); PollKey(Key::F10); PollKey(Key::F11); PollKey(Key::F12);
#endif
    }

    // Is the key currently held down?
    static bool IsKeyDown(Key key)
    {
        auto it = s_CurrentKeys.find(static_cast<int>(key));
        return it != s_CurrentKeys.end() && it->second;
    }

    // Is the key NOT held down?
    static bool IsKeyUp(Key key)
    {
        return !IsKeyDown(key);
    }

    // Was the key just pressed this frame? (down now, was up last frame)
    static bool IsKeyPressed(Key key)
    {
        int k = static_cast<int>(key);
        bool currentDown = s_CurrentKeys.count(k) && s_CurrentKeys[k];
        bool prevDown = s_PreviousKeys.count(k) && s_PreviousKeys[k];
        return currentDown && !prevDown;
    }

    // Was the key just released this frame? (up now, was down last frame)
    static bool IsKeyReleased(Key key)
    {
        int k = static_cast<int>(key);
        bool currentDown = s_CurrentKeys.count(k) && s_CurrentKeys[k];
        bool prevDown = s_PreviousKeys.count(k) && s_PreviousKeys[k];
        return !currentDown && prevDown;
    }

private:
#ifdef _WIN32
    static void PollKey(Key key)
    {
        int vk = static_cast<int>(key);
        // GetAsyncKeyState returns MSB set if key is down
        bool down = (GetAsyncKeyState(vk) & 0x8000) != 0;
        s_CurrentKeys[vk] = down;
    }
#endif

    static inline std::unordered_map<int, bool> s_CurrentKeys;
    static inline std::unordered_map<int, bool> s_PreviousKeys;
};
