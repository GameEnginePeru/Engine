#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	uint32 fnv1a_32(const char* str)
	{
		const uint32 FNV_prime = 16777619u;
		const uint32 FNV_offset_basis = 2166136261u;

		uint32 hash = FNV_offset_basis;

		for (std::size_t i = 0; i < std::strlen(str); ++i)
		{
			hash ^= static_cast<std::uint32_t>(str[i]);
			hash *= FNV_prime;
		}

		return hash;
	}
}