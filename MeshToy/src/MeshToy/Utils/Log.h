﻿#pragma once

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define MESHTOY_LOG_INFO(Message) Log::Write("INFO", __FILENAME__, __LINE__, Message)
#define MESHTOY_LOG_WARN(Message) Log::Write("WARN", __FILENAME__, __LINE__, Message)
#define MESHTOY_LOG_ERROR(Message) Log::Error("ERR!", __FILENAME__, __LINE__, Message)
#define MESHTOY_EXCEPTION(Message) Log::ThrowException(__FILENAME__, __LINE__, Message)

#include <format>
#include <iostream>
#include <string>

class Log
{
public:
    static void Write(
        const std::string& Suffix,
        const std::string& File,
        const int Line,
        const std::string& Message
    )
    {
        std::cout << std::format("[{}][{}:{}] {}\n", Suffix, File, Line, Message);
    }

    static void Error(
        const std::string& Suffix,
        const std::string& File,
        const int Line,
        const std::string& Message
    )
    {
        std::cerr << std::format("[{}][{}:{}] {}\n", Suffix, File, Line, Message);
    }

    static void ThrowException(
        const std::string& File,
        const int Line,
        const std::string& Message
    )
    {
        throw std::runtime_error(std::format("[CRIT][{}:{}] {}\n", File, Line, Message));
    }
};
