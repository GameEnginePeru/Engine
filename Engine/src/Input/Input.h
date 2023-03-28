#pragma once
#include "Core/CoreMinimal.h"
#include "Input/Codes/KeyCodes.h"
#include "Input/Codes/MouseCodes.h"
#include "Input/Codes/ActionCodes.h"

namespace ENGINE_NAMESPACE
{
	class Input
	{
	public:
		static void Update();

		static bool IsKeyPressed(KeyCode keycode);
		static bool IsKeyReleased(KeyCode keycode);
		static bool IsKeyDown(KeyCode keycode);
		static bool IsKeyUp(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static bool IsMouseButtonReleased(MouseCode button);

		static vec2 GetMousePosition();
		static vec2 GetMouseDelta();
	private:
	#if PLATFORM_WINDOWS
		friend class WindowsWindow;
	#endif
		static void OnKeyEvent(int32 keycode, int32 action);
		static void OnMouseButtonEvent(int32 button, int32 action);
		static void OnMousePositionEvent(double xpos, double ypos);
	private:
		static CUnorderedMap<KeyCode, bool> s_KeyPressedMap;
		static CUnorderedMap<KeyCode, bool> s_KeyReleasedMap;
		static CUnorderedMap<KeyCode, bool> s_KeyDownMap;
		static CUnorderedMap<KeyCode, bool> s_KeyUpMap;
		static CUnorderedMap<MouseCode, bool> s_MouseButtonPressedMap;
		static CUnorderedMap<MouseCode, bool> s_MouseButtonReleasedMap;
		static vec2 s_MousePosition;
		static vec2 s_LastMousePosition;
	};
}