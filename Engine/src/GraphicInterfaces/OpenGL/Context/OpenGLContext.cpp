#include "GraphicInterfaces/OpenGL/Context/OpenGLContext.h"
#include "Core/Logger/Logger.h"

namespace ENGINE_NAMESPACE
{
	OpenGLContext::OpenGLContext(void* pWindow)
		:m_pWindow(static_cast<GLFWwindow*>(pWindow)) { }

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_pWindow);

		// @TODO: Initialize GLEW

		// glewExperimental = true
		// auto success = glewInit()
		// GLEW_OK

		// Print OpenGL Info:

		LOG_CORE_INFO("OpenGL Info:");
		LOG_CORE_INFO("\tVendor: %s", glGetString(GL_VENDOR));
		LOG_CORE_INFO("\tRenderer: %s", glGetString(GL_RENDERER));
		LOG_CORE_INFO("\tVersion: %s", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_pWindow);
	}
}