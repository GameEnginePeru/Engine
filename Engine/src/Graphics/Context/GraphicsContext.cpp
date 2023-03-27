#include "Graphics/Context/GraphicsContext.h"
#include "Graphics/API/RendererAPI.h"

#include "GraphicInterfaces/OpenGL/Context/OpenGLContext.h"

namespace ENGINE_NAMESPACE
{
    Scope<GraphicsContext> GraphicsContext::Create(void* pWindow)
    {
		const auto& api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::NONE:
			return nullptr;
		case RendererAPI::API::OPENGL:
			return CreateScope<OpenGLContext>(pWindow);
		default:
			return nullptr;
		}
    }
}
