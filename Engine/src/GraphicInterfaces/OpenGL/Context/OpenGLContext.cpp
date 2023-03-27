#include "GraphicInterfaces/OpenGL/Context/OpenGLContext.h"
#include "Core/Logger/Logger.h"

namespace ENGINE_NAMESPACE
{
	OpenGLContext::OpenGLContext(void* pWindow)
		:m_pWindow(static_cast<GLFWwindow*>(pWindow)) { }

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_pWindow);

		glewExperimental = true;
		auto success = glewInit();
		if (success != GLEW_OK)
		{
			LOG_CORE_ERROR("Failed to initialize GLEW!");
		}

		// Print OpenGL Info:

		LOG_CORE_INFO("OpenGL Info:");
		LOG_CORE_INFO("\tVendor: ", glGetString(GL_VENDOR));
		LOG_CORE_INFO("\tRenderer: ", glGetString(GL_RENDERER));
		LOG_CORE_INFO("\tVersion: ", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_pWindow);
	}
}