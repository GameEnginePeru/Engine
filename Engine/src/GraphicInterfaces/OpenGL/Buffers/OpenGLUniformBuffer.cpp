#include "GraphicInterfaces/OpenGL/Buffers/OpenGLUniformBuffer.h"

#define GLEW_STATIC
#include <GL/glew.h>

namespace ENGINE_NAMESPACE
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32 size, uint32 binding)
	{
		glCreateBuffers(1, &m_uBufferID);
		glNamedBufferData(m_uBufferID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_uBufferID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_uBufferID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32 size, uint32 offset)
	{
		glNamedBufferSubData(m_uBufferID, offset, size, data);
	}
}