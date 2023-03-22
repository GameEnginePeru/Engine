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

	class Event
	{
	public:
		virtual const char* GetName() const = 0;
		virtual int32 GetCategoryFlags() const = 0;

		virtual CString ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
	public:
		bool handled = false;
	};

	class EventManager
	{
	public:
		template<typename T>
		static void AddListener(const T& event, void(*callback)(const T&))
		{
			auto& instance = Get();
			auto it = instance.m_Listeners.find(event.GetName());
			
			if (it == instance.m_Listeners.end())
			{
				instance.m_Listeners.emplace(std::make_pair(event.GetName(), CVector<std::function<void(const Event&)>>()));
				it = instance.m_Listeners.find(event.GetName());
			}
			auto func = [=](const Event& evt) {
				callback(static_cast<const T&>(evt));
			};
			it->second.emplace_back(func);
		}

		static void Dispatch(const Event& event)
		{
			auto& instance = Get();
			auto it = instance.m_Listeners.find(event.GetName());
			if (it != instance.m_Listeners.end())
			{
				for (auto& listener : it->second)
				{
					listener(event);
				}
			}
		}
	private:
		inline static EventManager& Get()
		{
			static EventManager instance;
			return instance;
		}
	private:
		CMap<CString, CVector<::std::function<void(const Event&)>>> m_Listeners;
	};
}