#pragma once
#include "Core/CoreMinimal.h"
#include "Graphics/Buffers/VertexArray.h"

namespace ENGINE_NAMESPACE
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const CVector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VBOs; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_pIBO; }
	private:
		uint32 m_uObjID;
		uint32 m_uVertexBufferIndex = 0;
		CVector<Ref<VertexBuffer>> m_VBOs;
		Ref<IndexBuffer> m_pIBO;
	};
}
