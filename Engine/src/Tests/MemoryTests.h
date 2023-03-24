#pragma once
#include "Core/Memory/MemoryAllocator.h"
#include <chrono>

namespace Engine::Tests::Memory
{
	void IterateTest();
	void EfficencyTest();

	void RunTests()
	{
		IterateTest();
		EfficencyTest();
	}

	void IterateTest()
	{
		Test test{ .name = "Iteration test" };

		class TestStruct
		{
		public:
			TestStruct() = default;
			~TestStruct() = default;

			uint64 n = 0;

			void OnUpdate() { n++;  }
			float x, y, z, w;
		private:
			static MemoryPool* GetPool()
			{
				static MemoryPool* instance;
				if (instance == nullptr)
				{
					instance = new MemoryPool(1000000, sizeof(TestStruct));
				}
				return instance;
			}
		};

		SIZE_T reserve = 1000000;
		std::vector<TestStruct*> items;

		// Instance Pool
		for (uint32 i = 0; i < reserve; i++)
		{
			TestStruct* ptr = MemoryAllocator::Allocate<TestStruct>();
			items.push_back(ptr);
		}

		// Loop Pool
		auto start = std::chrono::steady_clock::now();
		for (const auto& it : items)
		{
			it->OnUpdate();
		}
		auto end = std::chrono::steady_clock::now();

		for (const auto& it : items)
		{
			MemoryAllocator::Free(it);
		}
		items.clear();

		auto result1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		// Instance No Pool
		for (uint32 i = 0; i < reserve; i++)
		{
			TestStruct* ptr = new TestStruct();
			items.push_back(ptr);
		}

		// Loop No Pool
		start = std::chrono::steady_clock::now();
		for (const auto& it : items)
		{
			it->OnUpdate();
		}
		end = std::chrono::steady_clock::now();

		// Clear No Pool
		for (const auto& it : items)
		{
			delete it;
		}
		items.clear();

		auto result2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		if (result1 < result2)
		{
			auto diff = (float(result2 - result1) / float(result1 < 1 ? 1 : result1)) * 100.0f;
			std::cout << test.name << " passed, memory pool(" + std::to_string(result1) + "ms) was " + std::to_string(diff) + "% faster than standard allocations(" << (result2) << "ms)" << std::endl;
		}
		else
		{
			auto diff = (float(result1 - result2) / float(result2 < 1 ? 1 : result2)) * 100.0f;
			std::cout << test.name << " not passed, memory pool(" + std::to_string(result1) + "ms) was " + std::to_string(diff) + "% slower than standard allocations(" << (result2) << "ms)" << std::endl;
		}
	}

	void EfficencyTest()
	{
		Test test{ .name = "Memory Pool efficency test" };

		class TestStruct
		{
		public:
			TestStruct() {  }
			~TestStruct() {  }
			float x, y, z, w;
		};

		SIZE_T reserve = 10000000;

		auto start = std::chrono::steady_clock::now();

		for (uint32 i = 0; i < reserve; i++)
		{
			TestStruct* ptr = MemoryAllocator::Allocate<TestStruct>();
			MemoryAllocator::Free(ptr);
		}
		auto end = std::chrono::steady_clock::now();

		auto result1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		start = std::chrono::steady_clock::now();
		for (uint32 i = 0; i < reserve; i++)
		{
			TestStruct* ptr = new TestStruct();
			delete ptr;
		}
		end = std::chrono::steady_clock::now();

		auto result2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		if (result1 < result2)
		{
			auto diff = (float(result2 - result1) / float(result1 < 1 ? 1 : result1)) * 100.0f;
			std::cout << test.name << " passed, memory pool(" + std::to_string(result1)+ "ms) was " + std::to_string(diff) + "% faster than standard allocations(" << (result2) << "ms)" << std::endl;
		}
		else
		{
			auto diff = (float(result1 - result2) / float(result2 < 1 ? 1 : result2)) * 100.0f;
			std::cout << test.name << " not passed, memory pool(" + std::to_string(result1) + "ms) was " + std::to_string(diff) + "% slower than standard allocations(" << (result2) << "ms)" << std::endl;
		}
	}
}