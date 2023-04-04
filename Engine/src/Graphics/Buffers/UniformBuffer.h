#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}
		virtual void SetData(const void* data, uint32 uSize, uint32 uOffset = 0) = 0;

		static Ref<UniformBuffer> Create(uint32 uSize, uint32 uBinding);
	};
}
