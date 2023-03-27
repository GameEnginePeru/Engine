#include "Platform/WindowsPlatform/Window/WindowsWindow.h"
#include "Core/Logger/Logger.h"

namespace ENGINE_NAMESPACE
{
    static uint32 s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* desc)
    {
        LOG_CORE_ERROR("GLFW Error (", error, "): ", desc);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::OnUpdate()
    {
    }

    void WindowsWindow::SetVSync(bool bEnabled)
    {
        glfwSwapInterval(bool(bEnabled));
        m_Data.bVSync = bEnabled;
    }

    void WindowsWindow::Init(const WindowProperties& props)
    {
        m_Data.title = props.title;
        m_Data.uWidth = props.uWidth;
        m_Data.uHeight = props.uHeight;
        m_Data.bMaximized = props.bMaximized;
        m_Data.bResizable = props.bResizable;

        if (s_GLFWWindowCount == 0)
        {
            auto success = glfwInit();
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        glfwWindowHint(GLFW_RESIZABLE, m_Data.bResizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_MAXIMIZED, m_Data.bMaximized ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_SAMPLES, m_Data.uSamples);

        m_pWindow = glfwCreateWindow(m_Data.uWidth, m_Data.uHeight, m_Data.title.c_str(), nullptr, nullptr);
        m_pMonitor = glfwGetPrimaryMonitor();
        m_pVideoMode = glfwGetVideoMode(m_pMonitor);
        s_GLFWWindowCount++;

        // @TODO: Initialize Graphics Context
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_pWindow);
        s_GLFWWindowCount--;

        if (s_GLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }
}