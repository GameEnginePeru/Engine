#pragma once
#include "Core/CoreMinimal.h"
#include "Graphics/Buffers/Framebuffer.h"
#include "Core/Logger/Logger.h"

namespace ENGINE_NAMESPACE
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecs& specs);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void Resize(uint32 uWidth, uint32 uHeight) override;
		virtual int ReadPixel(uint32 uAttachmentIndex, int32 x, int32 y) override;

		virtual void ClearAttachment(uint32 uAttachmentIndex, int32 value) override;

		virtual uint32 GetColorAttachmentID(uint32 uIndex = 0) const override;
		virtual FramebufferSpecs GetSpecifications() const override { return m_Specs; }
	private:
		void Generate();
		void AttachColorTexture(uint32 uID, uint32 uInternalFormat, uint32 uFormat, int32 index);
		void AttachDepthTexture(uint32 uID, uint32 uFormat, uint32 uAttachmentType);
	private:
		uint32 m_uBufferID = 0;
		FramebufferSpecs m_Specs;

		CVector<FramebufferTextureSpecs> m_ColorAttachmentSpecs;
		FramebufferTextureSpecs m_DepthAttachmentSpecs;

		CVector<uint32> m_ColorAttachments; // @note: color textures
		uint32 m_uDepthAttachment = 0;	// @note: depth texture
	};
}
