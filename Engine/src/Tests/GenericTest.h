#pragma once
#include "Tests/EventTests.h"
#include "Core/Logger/Logger.h"

namespace Engine::Tests
{
	enum class TestSeverity
	{
		NONE,
		WARNING,
		SEVERE
	};

	struct TestResultData
	{
	public:
		float value = 0.0f;
		CString name = "";
		CString unit = "";
	};

	class Test
	{
	public:
		CString name = "";
		bool bPassed = false;
		CVector<TestResultData> results;
		TestSeverity severity = TestSeverity::NONE;
	public:
		inline void Print() const
		{
			std::ostringstream stream;
			stream << "TEST: " << name << (bPassed ? " " : " not ") << "passed! ";
			for (const auto& result : results)
			{
				stream << result.name << "(" << result.value << result.unit << "), ";
			}
			
			(bPassed ? LOG_CORE_TRACE(stream.str()) : LOG_CORE_WARNING(stream.str()));
		}
	};
}
