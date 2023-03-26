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
		Test test{ .name = "Memory Iteration" };
		TestResultData resultData1{ .name = "Memory Pool", .unit = "ms" };
		TestResultData resultData2{ .name = "Standard Allocation", .unit = "ms" };

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
					instance = new MemoryPool(10000000, sizeof(TestStruct));
				}
				return instance;
			}
		};

		SIZE_T reserve = 10000000;
		std::vector<TestStruct*> items;

		// Instance Pool
		for (uint32 i = 0; i < reserve; i++)
		{
			TestStruct* ptr = MemoryAllocator::Allocate<TestStruct>();
			items.push_back(ptr);
		}

		// Loop Pool
		auto start = std::chrono::steady_clock::now();
		for (const auto& it : items) it->OnUpdate();
		auto end = std::chrono::steady_clock::now();

		// Clear Pool
		for (const auto& it : items) MemoryAllocator::Free(it);
		items.clear();

		resultData1.value = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		// Instance No Pool
		for (uint32 i = 0; i < reserve; i++)
		{
			TestStruct* ptr = new TestStruct();
			items.push_back(ptr);
		}

		// Loop No Pool
		start = std::chrono::steady_clock::now();
		for (const auto& it : items) it->OnUpdate();
		end = std::chrono::steady_clock::now();

		// Clear No Pool
		for (const auto& it : items) delete it;
		items.clear();

		resultData2.value = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		test.bPassed = resultData1.value < resultData2.value;
		test.results.push_back(resultData1);
		test.results.push_back(resultData2);

		test.Print();
	}

	void EfficencyTest()
	{
		Test test{ .name = "Memory Efficency" };
		TestResultData resultData1 = { .name = "Memory Pool", .unit = "ms" };
		TestResultData resultData2 = { .name = "Standard Allocation", .unit = "ms" };

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

		resultData1.value = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		start = std::chrono::steady_clock::now();
		for (uint32 i = 0; i < reserve; i++)
		{
			TestStruct* ptr = new TestStruct();
			delete ptr;
		}
		end = std::chrono::steady_clock::now();

		resultData2.value = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		test.bPassed = resultData1.value < resultData2.value;
		test.results.push_back(resultData1);
		test.results.push_back(resultData2);

		test.Print();
	}
}