#include "GraphicInterfaces/OpenGL/API/OpenGLRendererAPI.h"

#define GLEW_STATIC
#include <GL/glew.h>

namespace ENGINE_NAMESPACE
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_MULTISAMPLE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	}

	void OpenGLRendererAPI::Clear()
	{
		glStencilMask(0xFF);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetUnpackAlignment(uint32 uAlignment)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, uAlignment);
	}

	void OpenGLRendererAPI::SetViewport(uint32 uX, uint32 uY, uint32 uWidth, uint32 uHeight)
	{
		glViewport(uX, uY, uWidth, uHeight);
	}

	void OpenGLRendererAPI::SetClearColor(const vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::DisableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}
}