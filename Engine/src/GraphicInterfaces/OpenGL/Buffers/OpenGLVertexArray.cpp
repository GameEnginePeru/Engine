#include "GraphicInterfaces/OpenGL/Buffers/OpenGLVertexArray.h"

#define GLEW_STATIC
#include <GL/glew.h>

namespace ENGINE_NAMESPACE
{
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT:		return GL_FLOAT;
		case ShaderDataType::FLOAT2:	return GL_FLOAT;
		case ShaderDataType::FLOAT3:	return GL_FLOAT;
		case ShaderDataType::FLOAT4:	return GL_FLOAT;
		case ShaderDataType::MAT3:		return GL_FLOAT;
		case ShaderDataType::MAT4:		return GL_FLOAT;
		case ShaderDataType::INT:		return GL_INT;
		case ShaderDataType::INT2:		return GL_INT;
		case ShaderDataType::INT3:		return GL_INT;
		case ShaderDataType::INT4:		return GL_INT;
		case ShaderDataType::BOOL:		return GL_BOOL;
		}

		LOG_CORE_ERROR("Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_uObjID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_uObjID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_uObjID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_uObjID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.type)
			{
			case ShaderDataType::FLOAT:
			case ShaderDataType::FLOAT2:
			case ShaderDataType::FLOAT3:
			case ShaderDataType::FLOAT4:
			{
				glEnableVertexAttribArray(m_uVertexBufferIndex);
				glVertexAttribPointer(m_uVertexBufferIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLType(element.type), element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.offset);
				LOG_CORE_TRACE("Attrib: ", layout.GetStride(), " | Component Count: ", element.offset, " | Stride: ", m_uVertexBufferIndex, " | Offset: ", element.GetComponentCount(), " | GLType: ", ShaderDataTypeToOpenGLType(element.type));
				m_uVertexBufferIndex++;
				break;
			}
			case ShaderDataType::INT:
			case ShaderDataType::INT2:
			case ShaderDataType::INT3:
			case ShaderDataType::INT4:
			case ShaderDataType::BOOL:
			{
				glEnableVertexAttribArray(m_uVertexBufferIndex);
				glVertexAttribIPointer(m_uVertexBufferIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLType(element.type), layout.GetStride(), (const void*)element.offset);
				LOG_CORE_TRACE("Attrib: ", layout.GetStride(), " | Component Count: ", element.offset, " | Stride: ", m_uVertexBufferIndex, " | Offset: ", element.GetComponentCount(), " | GLType: ", ShaderDataTypeToOpenGLType(element.type));
				m_uVertexBufferIndex++;
				break;
			}
			case ShaderDataType::MAT3:
			case ShaderDataType::MAT4:
			{
				u8 count = element.GetComponentCount();
				for (u8 i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_uVertexBufferIndex);
					glVertexAttribPointer(m_uVertexBufferIndex, count, ShaderDataTypeToOpenGLType(element.type), (element.normalized ? GL_TRUE : GL_FALSE), layout.GetStride(), (const void*)(element.offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_uVertexBufferIndex, 1);
					LOG_CORE_TRACE("Attrib: ", layout.GetStride(), " | Component Count: ", element.offset, " | Stride: ", m_uVertexBufferIndex, " | Offset: ", element.GetComponentCount(), " | GLType: ", ShaderDataTypeToOpenGLType(element.type));
					m_uVertexBufferIndex++;
				}
				break;
			}
			default:
				LOG_CORE_ERROR("Unknown ShaderDataType!");
			}
		}

		m_VBOs.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_uObjID);
		indexBuffer->Bind();

		m_pIBO = indexBuffer;
	}
}