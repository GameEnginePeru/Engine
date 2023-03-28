#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	typedef uint32 StringId;

	extern StringId InternString(const char* string);
	extern const char* RetrieveString(const StringId& sid);
}
