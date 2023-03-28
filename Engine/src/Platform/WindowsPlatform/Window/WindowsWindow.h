#pragma once
#include "Core/Window/Window.h"
#include "Graphics/Context/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace ENGINE_NAMESPACE
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow() override;

		virtual void OnUpdate() override;
		
		virtual uint32 GetWidth() const override { return m_Data.uWidth; }
		virtual uint32 GetHeight() const override { return m_Data.uHeight; }

		virtual void SetVSync(bool bEnabled) override;
		virtual bool IsVSync() const override { return m_Data.bVSync; }

		virtual void* GetNativeWindow() const override { return m_pWindow; }
	private:
		void Init(const WindowProperties& props);
		void Shutdown();
	private:
		GLFWwindow* m_pWindow = nullptr;
		GLFWmonitor* m_pMonitor = nullptr;
		const GLFWvidmode* m_pVideoMode = nullptr;
		Scope<GraphicsContext> m_pContext;

		struct WindowData
		{
			CString title;
			uint32 uWidth = 0, uHeight = 0;
			bool bVSync = true;
			bool bResizable = false;
			bool bMaximized = false;
			uint32 uSamples = 0;

			std::function<void(int32, int32)> KeyCodeFun;
			std::function<void(int32, int32)> MouseButtonFun;
			std::function<void(double, double)> MousePosFun;
		} m_Data;
	};
}
