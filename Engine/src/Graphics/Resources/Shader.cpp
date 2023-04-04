#include "Graphics/Resources/Shader.h"
#include "Graphics/API/RendererAPI.h"
#include "GraphicInterfaces/OpenGL/Resources/OpenGLShader.h"

namespace ENGINE_NAMESPACE
{
	Ref<Shader> Shader::Create(const CString& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OPENGL: return CreateRef<OpenGLShader>(filepath);
		}

		return nullptr;
	}
}