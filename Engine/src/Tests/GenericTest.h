#pragma once
#include "Tests/EventTests.h"

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
			std::cout << "---" << std::endl;
			std::cout << name << (bPassed ? " " : " not") << " passed! ";
			for (const auto& result : results)
			{
				std::cout << result.name << "(" << result.value << result.unit << "), ";
			}
			std::cout << std::endl;
			std::cout << "---" << std::endl;
		}
	};
}
