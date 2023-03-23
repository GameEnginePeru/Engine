#pragma once
#include "Core/CoreMinimal.h"

namespace Engine
{
	enum EventCategory
	{
		EVENT_CATEGORY_NONE = PREPROCESSOR_BIT(0),
		EVENT_CATEGORY_APPLICATION = PREPROCESSOR_BIT(1),
		EVENT_CATEGORY_INPUT = PREPROCESSOR_BIT(2),
		EVENT_CATEGORY_KEYBOARD = PREPROCESSOR_BIT(3),
		EVENT_CATEGORY_MOUSE = PREPROCESSOR_BIT(4),
		EVENT_CATEGORY_GAME = PREPROCESSOR_BIT(5)
	};

#define DEFINE_EVENT_TYPE(type) static const char* GetNameStatic() { return #type; } \
								virtual const char* GetName() const override { return #type; }

#define DEFINE_EVENT_CATEGORY(category) virtual int32 GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual int32 GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual CString ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

		static const char* GetNameStatic() { return "Event"; }
	public:
		bool handled = false;
	};
}