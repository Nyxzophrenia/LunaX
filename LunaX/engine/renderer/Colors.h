#pragma once

#include <string>

// ============================================================
// Colors
// ============================================================
// ANSI escape codes for colored console output.
// Works in Windows 10+ (with virtual terminal enabled),
// Linux, and macOS terminals.
//
// Usage:
//   std::cout << Color::Red << "Error!" << Color::Reset << "\n";
// ============================================================

namespace Color
{
    // Reset all formatting
    inline constexpr const char* Reset     = "\033[0m";

    // Text styles
    inline constexpr const char* Bold      = "\033[1m";
    inline constexpr const char* Dim       = "\033[2m";
    inline constexpr const char* Underline = "\033[4m";

    // Foreground colors
    inline constexpr const char* Black     = "\033[30m";
    inline constexpr const char* Red       = "\033[31m";
    inline constexpr const char* Green     = "\033[32m";
    inline constexpr const char* Yellow    = "\033[33m";
    inline constexpr const char* Blue      = "\033[34m";
    inline constexpr const char* Magenta   = "\033[35m";
    inline constexpr const char* Cyan      = "\033[36m";
    inline constexpr const char* White     = "\033[37m";

    // Bright foreground colors
    inline constexpr const char* BrightBlack   = "\033[90m";
    inline constexpr const char* BrightRed     = "\033[91m";
    inline constexpr const char* BrightGreen   = "\033[92m";
    inline constexpr const char* BrightYellow  = "\033[93m";
    inline constexpr const char* BrightBlue    = "\033[94m";
    inline constexpr const char* BrightMagenta = "\033[95m";
    inline constexpr const char* BrightCyan    = "\033[96m";
    inline constexpr const char* BrightWhite   = "\033[97m";

    // Background colors
    inline constexpr const char* BgBlack   = "\033[40m";
    inline constexpr const char* BgRed     = "\033[41m";
    inline constexpr const char* BgGreen   = "\033[42m";
    inline constexpr const char* BgYellow  = "\033[43m";
    inline constexpr const char* BgBlue    = "\033[44m";
    inline constexpr const char* BgMagenta = "\033[45m";
    inline constexpr const char* BgCyan    = "\033[46m";
    inline constexpr const char* BgWhite   = "\033[47m";

    // Enable ANSI support on Windows 10+
    inline void EnableVirtualTerminal()
    {
#ifdef _WIN32
        // Requires <windows.h> to be included before calling
        // This is typically done by the Window class
#endif
    }
}
