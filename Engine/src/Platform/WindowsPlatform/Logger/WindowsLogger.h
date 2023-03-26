#pragma once
#include "Core/Logger/Logger.h"

namespace Engine
{
	class WindowsLogger : public Logger
	{
	private:
		inline virtual void Init() override
		{
			auto& instance = Get();
			instance.m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			std::ofstream file;
			file.open(instance.m_LogFile, std::ofstream::out | std::ofstream::trunc);
			file.close();
		}

		inline virtual void SetConsoleColor(LogType type) const override
		{
			SetConsoleTextAttribute(m_hConsole, (int)type);
		}

		friend class Logger;
		static WindowsLogger& Get()
		{
			static WindowsLogger instance;
			return instance;
		}
	private:
		HANDLE m_hConsole = NULL;
	};
}