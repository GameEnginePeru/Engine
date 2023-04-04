#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/API/RendererAPI.h"
#include "GraphicInterfaces/OpenGL/Buffers/OpenGLVertexArray.h"

namespace ENGINE_NAMESPACE
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OPENGL:
			return CreateRef<OpenGLVertexArray>();
		}

		return nullptr;
	}
}