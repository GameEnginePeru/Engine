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

		template<typename T>
		void OnUpdate()
		{
			MemoryUnit* pCurrent = m_pAllocatedUnit;
			while (pCurrent != nullptr)
			{
				T* obj = reinterpret_cast<T*>((void*)((char*)pCurrent + sizeof(MemoryUnit)));
				obj->OnUpdate();
				pCurrent = pCurrent->pNext;
			}
		}
	private:
		void OnCreate();
		void OnDestroy();
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
		SIZE_T m_uReserved;
	};
}