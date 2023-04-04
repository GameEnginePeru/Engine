#pragma once
#include "Core/CoreMinimal.h"
#include "Graphics/Resources/Shader.h"

namespace ENGINE_NAMESPACE
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const CString& filePath);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const CString& name, int value) override;
		virtual void SetIntArray(const CString& name, int* values, uint32 count) override;
		virtual void SetFloat(const CString& name, float value) override;
		virtual void SetFloat2(const CString& name, const vec2& value) override;
		virtual void SetFloat3(const CString& name, const vec3& value) override;
		virtual void SetFloat4(const CString& name, const vec4& value) override;
		virtual void SetMat3(const CString& name, const mat3& value) override;
		virtual void SetMat4(const CString& name, const mat4& value) override;

		virtual void Reload() override;

		virtual const CString& GetName() const override { return m_Name; }
		virtual const CString& GetPath() const override { return m_FilePath; }
	private:
		void CreateShader();

		CUnorderedMap<ShaderType, CString> ReadFile(const CString& filepath);
		void CheckErrors(const unsigned int& shader, const char* name);
	private:
		uint32 m_ShaderID;
		CString m_FilePath;
		CString m_Name;
	};
}