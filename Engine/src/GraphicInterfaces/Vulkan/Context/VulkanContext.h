#pragma once
#include "Graphics/Context/GraphicsContext.h"

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace ENGINE_NAMESPACE
{
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(void* pWindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_pWindow = nullptr;
	};
}
