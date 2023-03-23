#pragma once
#include "Core/Memory/MemoryPool.h"
#include <chrono>

namespace Engine::Tests::Memory
{
	void EfficencyTest();

	void RunTests()
	{
		EfficencyTest();
	}

	void EfficencyTest()
	{
		Test test{ .name = "Memory Pool efficency test" };

		struct TestStruct
		{
			float x, y, z, w;
		};

		SIZE_T reserve = 1000000;
		SIZE_T unitSize = sizeof(TestStruct);

		MemoryPool pool = MemoryPool(reserve, unitSize);

		auto start = std::chrono::steady_clock::now();

		for (uint32 i = 0; i < reserve; i++)
		{
			TestStruct* ptr = reinterpret_cast<TestStruct*>(pool.Allocate());
			pool.Free(ptr);
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
			auto diff = ((result2 - result1) / result1) * 100;
			std::cout << test.name << " passed, memory pool(" + std::to_string(result1)+ "ms) was " + std::to_string(diff) + "\% faster than standard allocations(" << (result2) << "ms)" << std::endl;
		}
		else
		{
			auto diff = ((result1 - result2) / result2) * 100;
			std::cout << test.name << " not passed, memory pool(" + std::to_string(result1) + "ms) was " + std::to_string(diff) + "\% slower than standard allocations(" << (result2) << "ms)" << std::endl;
		}

		while (true);
	}
}