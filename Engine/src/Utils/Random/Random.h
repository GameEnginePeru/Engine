#pragma once
#include "Math/GLM/GLMDefinitions.h"
#include "Core/HAL/EngineDefinitions.h"
#include "Core/CoreSTD.h"

namespace ENGINE_NAMESPACE
{
	class Random
	{
	public:
		static void Init()
		{
			s_RandomEngine.seed(std::random_device()());
		}

		static uint32 UInt()
		{
			return s_Distribution(s_RandomEngine);
		}

		static uint32 UInt(uint32 min, uint32 max)
		{
			return min + (s_Distribution(s_RandomEngine) % (max - min + 1));
		}

		static float Float()
		{
			return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32>::max();
		}

		static vec3 Vec3()
		{
			return vec3(Float(), Float(), Float());
		}

		static vec3 Vec3(float min, float max)
		{
			return vec3(Float() * (max - min) + min, Float() * (max - min) + min, Float() * (max - min) + min);
		}

		static vec3 InUnitSphere()
		{
			return normalize(Vec3(-1.0f, 1.0f));
		}
	private:
		inline static thread_local std::mt19937 s_RandomEngine;
		inline static std::uniform_int_distribution<uint32> s_Distribution;
	};
}
