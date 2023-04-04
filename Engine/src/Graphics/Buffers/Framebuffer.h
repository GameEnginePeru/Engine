#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	enum class FramebufferTextureFormat
	{
		NONE = 0,
		RGBA8,
		RED_INTEGER,
		DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecs
	{
		FramebufferTextureSpecs() = default;
		FramebufferTextureSpecs(FramebufferTextureFormat format)
			:format(format) {}

		FramebufferTextureFormat format = FramebufferTextureFormat::NONE;
	};

	struct FramebufferAttachmentSpecs
	{
		FramebufferAttachmentSpecs() = default;
		FramebufferAttachmentSpecs(std::initializer_list<FramebufferTextureSpecs> attachments)
			:attachments(attachments) {}

		CVector<FramebufferTextureSpecs> attachments;
	};

	struct FramebufferSpecs
	{
		uint32 width = 0, height = 0;
		uint32 samples = 1;
		FramebufferAttachmentSpecs attachments;

		bool bSwapChainTarget = false; // @note: vulkan
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Resize(uint32 width, uint32 height) = 0;
		virtual int ReadPixel(uint32 attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32 attachmentIndex, int value) = 0;

		virtual uint32 GetColorAttachmentID(uint32 index = 0) const = 0;
		virtual FramebufferSpecs GetSpecifications() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecs& specs);
	};
}
