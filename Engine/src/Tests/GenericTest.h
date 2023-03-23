#pragma once
#include "Tests/EventTests.h"

namespace Engine::Tests
{
	struct Test
	{
		CString name;
		int32 value = 0;
		bool bPassed = false;
	};
}
