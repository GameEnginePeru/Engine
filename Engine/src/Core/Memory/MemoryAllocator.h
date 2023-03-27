#pragma once
#include "Core/CoreMinimal.h"
#include "Core/Memory/MemoryPool.h"

namespace ENGINE_NAMESPACE
{
	struct MemoryAllocatorIdentityHash
	{
		SIZE_T operator()(SIZE_T k) const 
		{
			return k;
		}
	};

	class MemoryAllocator
	{
	public:
		template<typename T>
		static T* Allocate()
		{
			SIZE_T unitSize = sizeof(T);
			auto pool = s_Pools[unitSize];
			if (pool !=  nullptr)
			{
				void* memory = pool->Allocate();
				return new(memory) T();
			}

			pool = new MemoryPool(1000000, unitSize);
			s_Pools[unitSize] = pool;

			void* memory = pool->Allocate();
			return new(memory) T();
		}

		template<typename T>
		static void Free(T* ptr)
		{
			ptr->~T();
			auto pool = s_Pools[sizeof(T)];
			pool->Free(ptr);
		}
	private:
		MemoryAllocator() = default;
		~MemoryAllocator() = default;
	private:
		inline static CUnorderedMap<SIZE_T, MemoryPool*, MemoryAllocatorIdentityHash> s_Pools;
	};
}