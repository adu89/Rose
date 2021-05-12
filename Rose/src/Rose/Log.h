#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>

#include <memory>

namespace Rose
{
    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
    };
} 

#define ROSE_CORE_TRACE(...) ::Rose::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ROSE_CORE_INFO(...)  ::Rose::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ROSE_CORE_WARN(...)  ::Rose::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ROSE_CORE_ERROR(...) ::Rose::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ROSE_CORE_FATAL(...) ::Rose::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define ROSE_TRACE(...) ::Rose::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ROSE_INFO(...)  ::Rose::Log::GetClientLogger()->info(__VA_ARGS__)
#define ROSE_WARN(...)  ::Rose::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ROSE_ERROR(...) ::Rose::Log::GetClientLogger()->error(__VA_ARGS__)
#define ROSE_FATAL(...) ::Rose::Log::GetClientLogger()->fatal(__VA_ARGS__)