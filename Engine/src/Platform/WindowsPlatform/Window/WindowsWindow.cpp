#include "Platform/WindowsPlatform/Window/WindowsWindow.h"
#include "Core/Logger/Logger.h"
#include "Input/Input.h"
#include "Events/EventManager.h"
#include "Events/ApplicationEvents.h"

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
        glfwPollEvents();
        m_pContext->SwapBuffers();
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
        m_Data.KeyCodeFun = Input::OnKeyEvent;
        m_Data.MouseButtonFun = Input::OnMouseButtonEvent;
        m_Data.MousePosFun = Input::OnMousePositionEvent;

        LOG_CORE_INFO("Creating window ", props.title, "(", m_Data.uWidth, ", ", m_Data.uHeight, ")");

        if (s_GLFWWindowCount == 0)
        {
            auto success = glfwInit();
            if (!success)
            {
                LOG_CORE_ERROR("Could not initialize GLFW");
            }
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        glfwWindowHint(GLFW_RESIZABLE, m_Data.bResizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_MAXIMIZED, m_Data.bMaximized ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_SAMPLES, m_Data.uSamples);

        m_pWindow = glfwCreateWindow(m_Data.uWidth, m_Data.uHeight, m_Data.title.c_str(), nullptr, nullptr);
        m_pMonitor = glfwGetPrimaryMonitor();
        m_pVideoMode = glfwGetVideoMode(m_pMonitor);
        s_GLFWWindowCount++;

        m_pContext = GraphicsContext::Create(m_pWindow);
        m_pContext->Init();

        glfwSetWindowUserPointer(m_pWindow, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* pWindow, int32 width, int32 height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
        });

        glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* pWindow) {
            WindowCloseEvent wce = WindowCloseEvent();
            EventDispatcher dispatcher(wce);
            dispatcher.Dispatch();
        });

        glfwSetKeyCallback(m_pWindow, [](GLFWwindow* pWindow, int32 keycode, int32 scancode, int32 action, int32 mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
            data.KeyCodeFun(keycode, action);
        });

        glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* pWindow, int32 button, int32 action, int32 mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
            data.MouseButtonFun(button, action);
        });

        glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* pWindow, double xpos, double ypos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
            data.MousePosFun(xpos, ypos);
        });
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