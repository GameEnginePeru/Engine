#pragma once
#include "Core/CoreMinimal.h"

namespace Engine
{
	class MemoryPool
	{
	public:
		MemoryPool(SIZE_T reserve, SIZE_T unitSize);
		~MemoryPool();

		void* Allocate();
		void Free(void* ptr);
	private:
		struct MemoryUnit
		{
			MemoryUnit* pPrev;
			MemoryUnit* pNext;
		};

		void* m_pMemoryBlock = nullptr;

		MemoryUnit* m_pAllocatedUnit = nullptr;
		MemoryUnit* m_pFreeUnit = nullptr;

		SIZE_T m_uUnitSize;
		SIZE_T m_uBlockSize;
	};
}