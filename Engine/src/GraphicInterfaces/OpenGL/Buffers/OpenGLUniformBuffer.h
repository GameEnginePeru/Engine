#pragma once
#include "Graphics/Buffers/UniformBuffer.h"

namespace ENGINE_NAMESPACE
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32 uSize, uint32 uBinding);
		virtual ~OpenGLUniformBuffer() override;

		virtual void SetData(const void* data, uint32 uSize, uint32 uOffset = 0) override;
	private:
		uint32 m_uBufferID = 0;
	};
}
