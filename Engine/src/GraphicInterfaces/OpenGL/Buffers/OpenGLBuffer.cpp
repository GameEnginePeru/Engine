#include "GraphicInterfaces/OpenGL/Buffers/OpenGLBuffer.h"

#define GLEW_STATIC
#include <GL/glew.h>

namespace ENGINE_NAMESPACE
{
	// Vertex Buffer Object

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32 size)
	{
		glCreateBuffers(1, &m_uBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_uBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_uBufferID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_uBufferID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32 size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_uBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	// Index Buffer Object

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count)
		:m_uCount(count)
	{
		// @fix: what if it's created before the VAO? Data wouldn't be loaded
		glCreateBuffers(1, &m_uBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_uBufferID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uBufferID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}