#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0,
			OPENGL = 1
		};
	public:
		virtual ~RendererAPI() = default;

		static API GetAPI() { return s_API; }
		static Ref<RendererAPI> Create();
	protected:
		virtual void Init() = 0;
		virtual void Clear() = 0;

		virtual void SetUnpackAlignmanet(uint32 uAlignment) = 0;
		virtual void SetViewport(uint32 uX, uint32 uY, uint32 uWidth, uint32 uHeight) = 0;
		virtual void SetClearColor() = 0;

		virtual void EnableDepthTest() = 0;
		virtual void DisableDepthTest() = 0;

		// @TODO: Add DrawIndexed Command

		// @TODO: Add Stencil: Read, Write Clear & Don't Care commands
	private:
		static API s_API;
	};
}