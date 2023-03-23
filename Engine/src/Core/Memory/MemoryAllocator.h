#pragma once
#include "Core/CoreMinimal.h"

namespace Engine
{
	class MemoryAllocator
	{
	public:
	private:
		MemoryAllocator() = default;
		~MemoryAllocator() = default;

		inline static MemoryAllocator& Get()
		{
			static MemoryAllocator instance;
			return instance;
		}
	};
}