#pragma once
#include "Tests/EventTests.h"
#include "Tests/MemoryTests.h"

namespace ENGINE_NAMESPACE::Tests
{
	void RunAllTests()
	{
		Events::RunTests();
		Memory::RunTests();
	}
}