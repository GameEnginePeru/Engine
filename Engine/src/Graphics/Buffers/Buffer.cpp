#include "Graphics/Buffers/Buffer.h"
#include "Graphics/API/RendererAPI.h"
#include "GraphicInterfaces/OpenGL/Buffers/OpenGLBuffer.h"

namespace ENGINE_NAMESPACE
{
	void BufferLayout::CalculateOffsetsAndStride()
	{
		SIZE_T offset = 0;
		m_Stride = 0;

		for (auto& e : m_Elements)
		{
			e.offset = offset;
			offset += e.size;
			m_Stride += e.size;
		}
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32 size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OPENGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32* indices, uint32 count)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OPENGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		return nullptr;
	}
}