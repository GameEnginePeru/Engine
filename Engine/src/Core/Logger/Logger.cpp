#include "Core/Logger/Logger.h"

#if PLATFORM_WINDOWS
    #include "Platform/WindowsPlatform/Logger/WindowsLogger.h"
#elif PLATFORM_APPLE
#elif PLATFORM_LINUX
#endif


namespace Engine
{
    Logger& Logger::Get()
    {
    #if PLATFORM_WINDOWS
        return WindowsLogger::Get();
    #elif PLATFORM_APPLE
    #elif PLATFORM_LINUX
    #endif
    }

    CString Logger::GetMessagePrefix(LogType type)
    {
        switch (type)
        {
        case LogType::INFO_LOG:
            return "[INFO]";
        case LogType::TRACE_LOG:
            return "[TRACE]";
        case LogType::WARNING_LOG:
            return "[WARNING]";
        case LogType::ERROR_LOG:
            return "[ERROR]";
        default:
            return "";
        }
    }
}