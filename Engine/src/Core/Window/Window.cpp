#include "Core/Window/Window.h"

#if PLATFORM_WINDOWS
    #include "Platform/WindowsPlatform/Window/WindowsWindow.h"
#endif

namespace ENGINE_NAMESPACE
{
    Scope<Window> Window::Create(const WindowProperties& props)
    {
    #ifdef PLATFORM_WINDOWS
        return CreateScope<WindowsWindow>(props);
    #else
        return nullptr;
    #endif
    }
}