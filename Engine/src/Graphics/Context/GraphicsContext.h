#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* pWindow);
	};
}