#pragma once
#include "Graphics/API/RendererAPI.h"

namespace ENGINE_NAMESPACE
{
	class OpenGLRendererAPI : public RendererAPI
	{
	private:
		virtual void Init() override;
		virtual void Clear() override;

		virtual void SetUnpackAlignment(uint32 uAlignment) override;
		virtual void SetViewport(uint32 uX, uint32 uY, uint32 uWidth, uint32 uHeight) override;
		virtual void SetClearColor(const vec4& color) override;

		virtual void EnableDepthTest() override;
		virtual void DisableDepthTest() override;
	};
}