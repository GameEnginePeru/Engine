#pragma once
#include "Core/CoreMinimal.h"
#include "Core/Logger/Logger.h"

namespace ENGINE_NAMESPACE
{
	enum class ShaderDataType
	{
		NONE = 0,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		MAT3,
		MAT4,
		INT,
		INT2,
		INT3,
		INT4,
		BOOL
	};

	static uint32 ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT:		return 4;
		case ShaderDataType::FLOAT2:	return 4 * 2;
		case ShaderDataType::FLOAT3:	return 4 * 3;
		case ShaderDataType::FLOAT4:	return 4 * 4;
		case ShaderDataType::MAT3:		return 4 * 3 * 3;
		case ShaderDataType::MAT4:		return 4 * 4 * 4;
		case ShaderDataType::INT:		return 4;
		case ShaderDataType::INT2:		return 4 * 2;
		case ShaderDataType::INT3:		return 4 * 3;
		case ShaderDataType::INT4:		return 4 * 4;
		case ShaderDataType::BOOL:		return 1;
		}

		LOG_CORE_ERROR("Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		CString name;
		ShaderDataType type;
		uint32 size;
		SIZE_T offset;
		bool normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const CString& name, bool normalized = false)
			:name(name), type(type), normalized(normalized), offset(0), size(ShaderDataTypeSize(type)) {}

		uint32 GetComponentCount() const
		{
			switch (type)
			{
			case ShaderDataType::FLOAT:	return 1;
			case ShaderDataType::FLOAT2:	return 2;
			case ShaderDataType::FLOAT3:	return 3;
			case ShaderDataType::FLOAT4:	return 4;
			case ShaderDataType::MAT3:		return 3;
			case ShaderDataType::MAT4:		return 4;
			case ShaderDataType::INT:		return 1;
			case ShaderDataType::INT2:		return 2;
			case ShaderDataType::INT3:		return 3;
			case ShaderDataType::INT4:		return 4;
			case ShaderDataType::BOOL:		return 1;
			default: break;
			}

			LOG_CORE_ERROR("Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> elements)
			:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32 GetStride() const { return m_Stride; }
		const CVector<BufferElement>& GetElements() const { return m_Elements; }

		CVector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		CVector<BufferElement>::iterator end() { return m_Elements.end(); }
		CVector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		CVector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride();
	private:
		CVector<BufferElement> m_Elements;
		uint32 m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32 size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(uint32 size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetCount() = 0;

		static Ref<IndexBuffer> Create(uint32* indices, uint32 count);
	};
}