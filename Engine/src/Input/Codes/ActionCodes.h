#pragma once
#include "Core/CoreMinimal.h"

using ActionCode = uint16;

namespace ENGINE_NAMESPACE
{
	namespace InputAction
	{
		enum : ActionCode
		{
			// The key or mouse button was released.
			Release = 0,

			// The key or mouse button was pressed.
			Press = 1,

			// The key was held down until it repeated.
			Repeat = 2
		};
	}

	namespace JoystickAction
	{
		enum : ActionCode
		{
			Centered = 0,
			Up = PREPROCESSOR_BIT(1),
			Right = PREPROCESSOR_BIT(2),
			Down = PREPROCESSOR_BIT(4),
			Left = PREPROCESSOR_BIT(8),
			RightUp = (Right | Up),
			RightDown = (Right | Down),
			LeftUp = (Left | Up),
			LeftDown = (Left | Down)
		};
	}
}
