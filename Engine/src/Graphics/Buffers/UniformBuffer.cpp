#include "Graphics/Buffers/UniformBuffer.h"
#include "Graphics/API/RendererAPI.h"
#include "GraphicInterfaces/OpenGL/Buffers/OpenGLUniformBuffer.h"

namespace ENGINE_NAMESPACE
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32 uSize, uint32 uBinding)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OPENGL:
			return CreateRef<OpenGLUniformBuffer>(uSize, uBinding);
		}

		return nullptr;
	}
}