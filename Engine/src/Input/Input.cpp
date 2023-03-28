#include "Input/Input.h"
#include "Core/Launch/Application.h"

namespace ENGINE_NAMESPACE
{
	CUnorderedMap<KeyCode, bool> Input::s_KeyPressedMap;
	CUnorderedMap<KeyCode, bool> Input::s_KeyReleasedMap;
	CUnorderedMap<KeyCode, bool> Input::s_KeyDownMap;
	CUnorderedMap<KeyCode, bool> Input::s_KeyUpMap;
	CUnorderedMap<KeyCode, bool> Input::s_MouseButtonPressedMap;
	CUnorderedMap<KeyCode, bool> Input::s_MouseButtonReleasedMap;
	vec2 Input::s_MousePosition = vec2(0.0f);
	vec2 Input::s_LastMousePosition = vec2(0.0f);

	void Input::Update()
	{
		s_LastMousePosition = s_MousePosition;

		for (auto& [keycode, released] : s_KeyReleasedMap)
		{
			released = false;
		}

		for (auto& [button, released] : s_MouseButtonReleasedMap)
		{
			released = false;
		}

		for (auto& [keycode, pressed] : s_KeyPressedMap)
		{
			pressed = false;
		}

		for (auto& [button, pressed] : s_MouseButtonPressedMap)
		{
			pressed = false;
		}
	}

	bool Input::IsKeyPressed(KeyCode keycode)
	{
		return s_KeyPressedMap[keycode];
	}

	bool Input::IsKeyReleased(KeyCode keycode)
	{
		return s_KeyReleasedMap[keycode];
	}

	bool Input::IsKeyDown(KeyCode keycode)
	{
		return s_KeyDownMap[keycode];
	}

	bool Input::IsKeyUp(KeyCode keycode)
	{
		return s_KeyUpMap[keycode];
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		return s_MouseButtonPressedMap[button];
	}

	bool Input::IsMouseButtonReleased(MouseCode button)
	{
		return s_MouseButtonReleasedMap[button];
	}

	vec2 Input::GetMousePosition()
	{
		return s_MousePosition;
	}

	vec2 Input::GetMouseDelta()
	{
		return s_MousePosition - s_LastMousePosition;
	}

	void Input::OnKeyEvent(int32 keycode, int32 action)
	{
		if (action == InputAction::Press)
		{
			s_KeyPressedMap[keycode] = true;
			s_KeyDownMap[keycode] = true;
			s_KeyReleasedMap[keycode] = false;
			s_KeyUpMap[keycode] = false;
		}
		else if (action == InputAction::Release)
		{
			s_KeyPressedMap[keycode] = false;
			s_KeyDownMap[keycode] = false;
			s_KeyReleasedMap[keycode] = true;
			s_KeyUpMap[keycode] = true;
		}
	}

	void Input::OnMouseButtonEvent(int32 button, int32 action)
	{
		if (action == InputAction::Press)
		{
			s_MouseButtonPressedMap[button] = true;
		}
		else if (action == InputAction::Release)
		{
			s_MouseButtonPressedMap[button] = false;
			s_MouseButtonReleasedMap[button] = true;
		}
	}

	void Input::OnMousePositionEvent(double xpos, double ypos)
	{
		s_MousePosition = vec2(xpos, ypos);
	}
}