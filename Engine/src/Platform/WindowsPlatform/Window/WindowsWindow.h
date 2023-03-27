#pragma once
#include "Core/Window/Window.h"

namespace ENGINE_NAMESPACE
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props) {}
		virtual ~WindowsWindow() override {}

		virtual void OnUpdate() override {}
		
		virtual uint32 GetWidth() const override { return m_Data.uWidth; }
		virtual uint32 GetHeight() const override { return m_Data.uHeight; }

		virtual void SetVSync(bool bEnabled) override {}
		virtual bool IsVSync() const override { return m_Data.bVSync; }

		// @TODO: change!
		virtual void* GetNativeWindow() const override { return nullptr; }
	private:
		struct WindowData
		{
			CString title;
			uint32 uWidth = 0, uHeight = 0;
			bool bVSync = true;
			bool bResizable = false;
			bool bMaximized = false;
			uint32 uSamples = 0;
		} m_Data;
	};
}
