#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	class Time
	{
	public:
		inline static CString GetTime(const char* format = nullptr) { return Get().IGetTime(format); }
		inline static void SetTimeFormat(const char* format) { Get().m_TimeFormat = format; }
		inline static void SetDateFormat(const char* format) { Get().m_DateFormat = format; }
	private:
		CString IGetTime(const char* format);

		PREPROCESSOR_MAKE_SINGLETON(Time)
	private:
		CString m_TimeFormat = "%H:%M:%S";
		CString m_DateFormat = "%d-%m-%Y";
	};
}
