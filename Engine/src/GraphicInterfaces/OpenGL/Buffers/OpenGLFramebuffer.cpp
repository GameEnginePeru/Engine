#include "GraphicInterfaces/OpenGL/Buffers/OpenGLFramebuffer.h"

#define GLEW_STATIC
#include <GL/glew.h>

namespace ENGINE_NAMESPACE
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecs& specs)
		:m_Specs(specs)
	{
		for (auto spec : m_Specs.attachments.attachments)
		{
			if (spec.format != FramebufferTextureFormat::DEPTH24STENCIL8) m_ColorAttachmentSpecs.emplace_back(spec);
			else m_DepthAttachmentSpecs = spec;
		}

		Generate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_uBufferID);
		glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_uDepthAttachment);
	}

	void OpenGLFramebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_uBufferID);
		glViewport(0, 0, m_Specs.width, m_Specs.height);
	}

	void OpenGLFramebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32 OpenGLFramebuffer::GetColorAttachmentID(uint32 uIndex) const
	{
		if (uIndex > m_ColorAttachments.size())
		{
			LOG_CORE_ERROR("Invalid Framebuffer index attachment");
			return 0;
		}

		return m_ColorAttachments[uIndex];
	}

	void OpenGLFramebuffer::Resize(uint32 uWidth, uint32 uHeight)
	{
		if (uWidth == 0 || uHeight == 0)
		{
			LOG_CORE_WARNING("Attempted to resize framebuffer to ", uWidth, ", ", uHeight);
		}

		LOG_CORE_INFO("Resized framebuffer to ", uWidth, ", ", uHeight);

		m_Specs.width = uWidth;
		m_Specs.height = uHeight;
		Generate();
	}

	/// Only Available for single channel texture
	int OpenGLFramebuffer::ReadPixel(uint32 uAttachmentIndex, int32 x, int32 y)
	{
		if (uAttachmentIndex > m_ColorAttachments.size())
		{
			LOG_CORE_ERROR("Invalid Framebuffer index attachment");
			return 0;
		}

		glReadBuffer(GL_COLOR_ATTACHMENT0 + uAttachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void OpenGLFramebuffer::ClearAttachment(uint32 uAttachmentIndex, int32 value)
	{
		if (uAttachmentIndex > m_ColorAttachments.size())
		{
			LOG_CORE_ERROR("Invalid Framebuffer index attachment");
			return;
		}

		auto& spec = m_ColorAttachmentSpecs[uAttachmentIndex];
		GLenum format = GL_RGBA8;
		switch (spec.format)
		{
		case FramebufferTextureFormat::RGBA8: format = GL_RGBA8; break;
		case FramebufferTextureFormat::RED_INTEGER: format = GL_RED_INTEGER; break;
		}
		glClearTexImage(m_ColorAttachments[uAttachmentIndex], 0, format, GL_INT, &value);
	}

	void OpenGLFramebuffer::Generate()
	{
		if (m_uBufferID)
		{
			glDeleteFramebuffers(1, &m_uBufferID);
			glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_uDepthAttachment);

			m_ColorAttachments.clear();
			m_uDepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_uBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_uBufferID);

		bool multisample = m_Specs.samples > 1;

		if (m_ColorAttachmentSpecs.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());

			glCreateTextures(multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, (GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());

			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				glBindTexture(multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, m_ColorAttachments[i]);

				switch (m_ColorAttachmentSpecs[i].format)
				{
				case FramebufferTextureFormat::RGBA8:
					AttachColorTexture(m_ColorAttachments[i], GL_RGBA8, GL_RGBA, (int)i);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					AttachColorTexture(m_ColorAttachments[i], GL_R32I, GL_RED_INTEGER, (int)i);
					break;
				}
			}
		}

		if (m_DepthAttachmentSpecs.format != FramebufferTextureFormat::NONE)
		{
			glCreateTextures(multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, 1, &m_uDepthAttachment);
			glBindTexture(multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, m_uDepthAttachment);

			switch (m_DepthAttachmentSpecs.format)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				AttachDepthTexture(m_uDepthAttachment, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
				break;
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			if (m_ColorAttachments.size() > 4)
			{
				LOG_CORE_ERROR("Only a max of 4 color textures is allowed");
				return;
			}

			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((GLsizei)m_ColorAttachments.size(), buffers);
		}
		else
		{
			// if color attachments empty we only do the depth pass
			glDrawBuffer(GL_NONE);
		}

		// check if framebuffer is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_CORE_ERROR("Framebuffer is incomplete!");
			return;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::AttachColorTexture(uint32 uID, uint32 uInternalFormat, uint32 uFormat, int32 index)
	{
		bool multisampled = m_Specs.samples > 1;
		if (multisampled)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Specs.samples, uInternalFormat, m_Specs.width, m_Specs.height, GL_FALSE);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, uInternalFormat, m_Specs.width, m_Specs.height, 0, uFormat, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, uID, 0);
	}

	void OpenGLFramebuffer::AttachDepthTexture(uint32 uID, uint32 uFormat, uint32 uAttachmentType)
	{
		bool multisampled = m_Specs.samples > 1;
		if (multisampled)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Specs.samples, uFormat, m_Specs.width, m_Specs.height, GL_FALSE);
		}
		else
		{
			glTexStorage2D(GL_TEXTURE_2D, 1, uFormat, m_Specs.width, m_Specs.height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, uAttachmentType, multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, uID, 0);
	}
}