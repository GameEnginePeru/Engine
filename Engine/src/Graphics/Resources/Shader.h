#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	enum class ShaderType
	{
		NONE = 0,

		VERTEX = 1,
		FRAGMENT = 2,
		GEOMETRY = 3
	};

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Reload() = 0;

		virtual void SetInt(const CString& name, int value) = 0;
		virtual void SetIntArray(const CString& name, int* values, uint32 count) = 0;
		virtual void SetFloat(const CString& name, float value) = 0;
		virtual void SetFloat2(const CString& name, const vec2& value) = 0;
		virtual void SetFloat3(const CString& name, const vec3& value) = 0;
		virtual void SetFloat4(const CString& name, const vec4& value) = 0;
		virtual void SetMat3(const CString& name, const mat3& value) = 0;
		virtual void SetMat4(const CString& name, const mat4& value) = 0;

		virtual const CString& GetName() const = 0;
		virtual const CString& GetPath() const = 0;

		static Ref<Shader> Create(const CString& filepath);
	};
}