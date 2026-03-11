#pragma once

#include <string>
#include <cstdint>
#include <functional>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

// ============================================================
// Window
// ============================================================
// Console-based "window" abstraction.
//
// On Windows, uses the Win32 Console API to:
//   - Set the console title and size
//   - Detect console close events (Ctrl+C, window X)
//   - Provide a virtual "window" for text-based rendering
//
// On other platforms, falls back to basic terminal output.
// ============================================================

class Window
{
public:
    using CloseCallback = std::function<void()>;

    // Default constructor
    Window() = default;

    // Constructor with custom size and title
    Window(int width, int height, const std::string& title)
        : m_Width(width), m_Height(height), m_Title(title), m_IsOpen(false)
    {
    }

    // Destructor — ensures cleanup
    ~Window()
    {
        Close();
    }

    // ── Lifecycle ──────────────────────────────────────────

    // Initialize the console window
    void Initialize()
    {
        m_IsOpen = true;

#ifdef _WIN32
        // Set console title
        SetConsoleTitleA(m_Title.c_str());

        // Get console handle
        m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        // Set console window size (in character cells)
        SMALL_RECT windowSize = {0, 0,
            static_cast<SHORT>(m_Width - 1),
            static_cast<SHORT>(m_Height - 1)};
        SetConsoleWindowInfo(m_ConsoleHandle, TRUE, &windowSize);

        // Set buffer size to match window
        COORD bufferSize = {
            static_cast<SHORT>(m_Width),
            static_cast<SHORT>(m_Height)};
        SetConsoleScreenBufferSize(m_ConsoleHandle, bufferSize);

        // Register console close handler
        SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
        s_Instance = this;

        // Hide cursor for cleaner rendering
        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 1;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(m_ConsoleHandle, &cursorInfo);
#endif

        std::cout << "[Window] Initialized: "
                  << m_Width << "x" << m_Height
                  << " Title: " << m_Title << "\n";
    }

    // Process window/console events each frame
    void Update()
    {
        if (!m_IsOpen)
            return;

#ifdef _WIN32
        // Check if the console window is still valid
        if (s_CloseRequested)
        {
            Close();
        }
#endif
    }

    // Close the window
    void Close()
    {
        if (m_IsOpen)
        {
            m_IsOpen = false;

#ifdef _WIN32
            // Restore cursor visibility
            CONSOLE_CURSOR_INFO cursorInfo;
            cursorInfo.dwSize = 1;
            cursorInfo.bVisible = TRUE;
            SetConsoleCursorInfo(m_ConsoleHandle, &cursorInfo);
#endif

            std::cout << "[Window] Closed\n";

            if (m_CloseCallback)
                m_CloseCallback();
        }
    }

    // ── Clear & Cursor ─────────────────────────────────────

    // Clear the console screen
    void Clear()
    {
#ifdef _WIN32
        COORD origin = {0, 0};
        DWORD written;
        DWORD size = m_Width * m_Height;
        FillConsoleOutputCharacterA(m_ConsoleHandle, ' ', size, origin, &written);
        FillConsoleOutputAttribute(m_ConsoleHandle, 7, size, origin, &written);
        SetConsoleCursorPosition(m_ConsoleHandle, origin);
#else
        // ANSI escape fallback
        std::cout << "\033[2J\033[H";
#endif
    }

    // Set cursor position (for text rendering)
    void SetCursorPosition(int x, int y)
    {
#ifdef _WIN32
        COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
        SetConsoleCursorPosition(m_ConsoleHandle, pos);
#else
        std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
#endif
    }

    // ── Queries ────────────────────────────────────────────

    [[nodiscard]] bool IsOpen() const noexcept { return m_IsOpen; }
    int GetWidth() const noexcept { return m_Width; }
    int GetHeight() const noexcept { return m_Height; }
    const std::string& GetTitle() const noexcept { return m_Title; }

    void SetCloseCallback(CloseCallback callback) { m_CloseCallback = callback; }

private:
    int m_Width = 80;
    int m_Height = 25;
    std::string m_Title = "LunaX Engine";
    bool m_IsOpen = false;
    CloseCallback m_CloseCallback = nullptr;

#ifdef _WIN32
    HANDLE m_ConsoleHandle = nullptr;

    // Static close handler for Win32 console events
    static inline Window* s_Instance = nullptr;
    static inline bool s_CloseRequested = false;

    static BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType)
    {
        switch (ctrlType)
        {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_CLOSE_EVENT:
            s_CloseRequested = true;
            return TRUE;
        default:
            return FALSE;
        }
    }
#endif
};
