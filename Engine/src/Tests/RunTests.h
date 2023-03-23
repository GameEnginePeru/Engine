#pragma once
#include "Tests/EventTests.h"
#include "Tests/MemoryTests.h"

namespace Engine::Tests
{
	void RunAllTests()
	{
		Events::RunTests();
		Memory::RunTests();
	}
}