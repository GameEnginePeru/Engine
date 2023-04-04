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
	private:
		friend class Application;
		static void SetApi(RendererAPI::API api) { s_API = api; }
	protected:
		friend class RenderCommand;
		virtual void Init() = 0;
		virtual void Clear() = 0;

		virtual void SetUnpackAlignment(uint32 uAlignment) = 0;
		virtual void SetViewport(uint32 uX, uint32 uY, uint32 uWidth, uint32 uHeight) = 0;
		virtual void SetClearColor(const vec4& color) = 0;

		virtual void EnableDepthTest() = 0;
		virtual void DisableDepthTest() = 0;

		// @TODO: Add DrawIndexed Command
		// @TODO: Add Stencil: Read, Write Clear & Don't Care commands
	private:
		static API s_API;
	};

	class RenderCommand
	{
	public:
		static void Init() { Get()->Init(); }
		static void Clear() { Get()->Clear(); }

		static void SetUnpackAlignment(uint32 alignment) { Get()->SetUnpackAlignment(alignment); }
		static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) { Get()->SetViewport(x, y, width, height); }
		static void SetClearColor(const vec4& color) { Get()->SetClearColor(color); }

		// @TODO: Implement
		static void SetFullscreen() {}
		static void SetWindowed() {}

		static void EnableDepthTest() { Get()->EnableDepthTest(); }
		static void DisableDepthTest() { Get()->DisableDepthTest(); }

		// @TODO: Add DrawIndexed Command
		// @TODO: Add Stencil: Read, Write Clear & Don't Care commands
	private:
		inline static Ref<RendererAPI> Get()
		{
			static bool created = false;
			static Ref<RendererAPI> instance;
			if (!created)
			{
				instance = RendererAPI::Create();
				created = true;
			}
			return instance;
		}
	};
}