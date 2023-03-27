#pragma once
#include "Core/CoreMinimal.h"

namespace ENGINE_NAMESPACE
{
	struct WindowProperties
	{
		CString title = ENGINE_NAME_STRING;
		uint32 uWidth = 1280, uHeight = 720;
		bool bResizable = false;
		bool bMaximized = false;
	};

	class Window
	{
	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProperties& props = WindowProperties());
	};
}
