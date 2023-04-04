#include "Graphics/Buffers/Framebuffer.h"
#include "GraphicInterfaces/OpenGL/Buffers/OpenGLFramebuffer.h"
#include "Graphics/API/RendererAPI.h"

namespace ENGINE_NAMESPACE
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecs& specs)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OPENGL:
			return CreateRef<OpenGLFramebuffer>(specs);
		}

		return nullptr;
	}
}