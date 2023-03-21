#pragma once

#include "Platform/GenericPlatform/GenericPlatform.h"

struct WindowsPlatformTypes : public GenericPlatformTypes
{
	typedef uint64 SIZE_T;
	typedef int64 SSIZE_T;
};

typedef WindowsPlatformTypes PlatformTypes;

#define PLATFORM_LITTLE_ENDIAN 1