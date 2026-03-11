#pragma once

#include "Colors.h"
#include <iostream>
#include <string>
#include <sstream>

// ============================================================
// Log
// ============================================================
// Lightweight logging system with severity levels and colors.
//
// Usage:
//   Log::Info("Engine", "Started successfully");
//   Log::Warn("Physics", "Delta time clamped");
//   Log::Error("Window", "Failed to create console");
//   Log::Debug("ECS", "Entity 5 created");
// ============================================================

enum class LogLevel
{
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

class Log
{
public:
    // Set minimum log level (messages below this are ignored)
    static void SetLevel(LogLevel level)
    {
        s_MinLevel = level;
    }

    static void Debug(const std::string& tag, const std::string& message)
    {
        Print(LogLevel::Debug, tag, message);
    }

    static void Info(const std::string& tag, const std::string& message)
    {
        Print(LogLevel::Info, tag, message);
    }

    static void Warn(const std::string& tag, const std::string& message)
    {
        Print(LogLevel::Warn, tag, message);
    }

    static void Error(const std::string& tag, const std::string& message)
    {
        Print(LogLevel::Error, tag, message);
    }

    static void Fatal(const std::string& tag, const std::string& message)
    {
        Print(LogLevel::Fatal, tag, message);
    }

private:
    static inline LogLevel s_MinLevel = LogLevel::Debug;

    static void Print(LogLevel level, const std::string& tag, const std::string& message)
    {
        if (level < s_MinLevel)
            return;

        const char* color = Color::Reset;
        const char* label = "???";

        switch (level)
        {
        case LogLevel::Debug:
            color = Color::BrightBlack;
            label = "DEBUG";
            break;
        case LogLevel::Info:
            color = Color::BrightCyan;
            label = "INFO ";
            break;
        case LogLevel::Warn:
            color = Color::BrightYellow;
            label = "WARN ";
            break;
        case LogLevel::Error:
            color = Color::BrightRed;
            label = "ERROR";
            break;
        case LogLevel::Fatal:
            color = Color::Red;
            label = "FATAL";
            break;
        }

        std::cout << color << "[" << label << "]"
                  << Color::Reset << " "
                  << Color::Bold << "[" << tag << "]"
                  << Color::Reset << " "
                  << message << "\n";
    }
};
