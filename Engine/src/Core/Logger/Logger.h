#pragma once
#include "Core/CoreMinimal.h"
#include "Utils/Time/Time.h"

namespace Engine
{
	enum class LogType
	{
		INFO_LOG = 15,
		TRACE_LOG = 10,
		WARNING_LOG = 14,
		ERROR_LOG = 12,
	};

	enum class LogFlags : uint8
	{
		NONE = 0,
		CONSOLE_LOG = PREPROCESSOR_BIT(0),
		CUSTOM_CONSOLE_LOG = PREPROCESSOR_BIT(1),
		WRITE_TO_FILE_LOG = PREPROCESSOR_BIT(2),
	};

	PREPROCESSOR_DEFINE_ENUM_FLAG_OPERATORS(LogFlags);

	class GenericConsoleLogger
	{
	public: 
		virtual void Log(const LogType type, const std::string& message) const = 0;
	};

	class Logger
	{
	public:
		template<typename ... Args>
		inline static void Log(LogType type, CString prefix, const CString& message, Args&&... args)
		{
			auto& instance = Get();
			instance.SetConsoleColor(type);
			std::ostringstream stream;
			stream << "[" << Time::GetTime() << "] " << prefix;
			StreamArgs(stream, message, std::forward<Args>(args)...);

			if (bool(instance.m_Flags & LogFlags::CONSOLE_LOG))
			{
				std::cout << stream.str() << std::endl;
			}

			if (bool(instance.m_Flags & LogFlags::WRITE_TO_FILE_LOG))
			{
				std::ofstream file;
				file.open(instance.m_LogFile, std::ofstream::app);
				if (file.is_open())
				{
					file << GetMessagePrefix(type);
					file << stream.str() << std::endl;
					file.close();
				}
			}

			if (bool(Get().m_Flags & LogFlags::CUSTOM_CONSOLE_LOG) && Get().m_pConsole)
			{
				Get().m_pConsole->Log(type, stream.str());
			}
			instance.SetConsoleColor(LogType::INFO_LOG);
		}

		inline static void SetFlags(LogFlags flags) { Get().m_Flags |= flags; }
		inline static void SetCustomConsoleLogger(GenericConsoleLogger* console) { Get().m_pConsole = console; }
	private:
		friend class Application;

		inline virtual void Init() = 0;

		static Logger& Get();

		static CString GetMessagePrefix(LogType type);

		template<typename T>
		static void StreamArgs(std::ostringstream& stream, const T& arg)
		{
			stream << arg;
		}

		template<typename T, typename... Args>
		static void StreamArgs(std::ostringstream& stream, const T& arg, Args&&... args)
		{
			StreamArgs(stream, arg);
			StreamArgs(stream, std::forward<Args>(args)...);
		}
	protected:
		inline virtual void SetConsoleColor(LogType type) const = 0;
	protected:
		LogFlags m_Flags = LogFlags::NONE;
		const CString m_LogFile = ".log";
		GenericConsoleLogger* m_pConsole = nullptr;
	};
}

#define LOG_CORE_INFO(...) ::Engine::Logger::Log(::Engine::LogType::INFO_LOG, "ENGINE: ", __VA_ARGS__)
#define LOG_CORE_TRACE(...) ::Engine::Logger::Log(::Engine::LogType::TRACE_LOG, "ENGINE: ", __VA_ARGS__)
#define LOG_CORE_WARNING(...) ::Engine::Logger::Log(::Engine::LogType::WARNING_LOG, "ENGINE: ", __VA_ARGS__)
#define LOG_CORE_ERROR(...) ::Engine::Logger::Log(::Engine::LogType::ERROR_LOG, "ENGINE: ", __VA_ARGS__)

#define LOG_INFO(...) ::Engine::Logger::Log(::Engine::LogType::INFO_LOG, "APP: ", __VA_ARGS__)
#define LOG_TRACE(...) ::Engine::Logger::Log(::Engine::LogType::TRACE_LOG, "APP: ", __VA_ARGS__)
#define LOG_WARNING(...) ::Engine::Logger::Log(::Engine::LogType::WARNING_LOG, "APP: ", __VA_ARGS__)
#define LOG_ERROR(...) ::Engine::Logger::Log(::Engine::LogType::ERROR_LOG, "APP: ", __VA_ARGS__)