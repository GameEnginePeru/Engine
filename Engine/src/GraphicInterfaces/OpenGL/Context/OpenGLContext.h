#pragma once
#include "Graphics/Context/GraphicsContext.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ENGINE_NAMESPACE
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(void* pWindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_pWindow = nullptr;
	};
}