#pragma once

#include "Events/Event.h"

namespace Engine
{
	class EventManager
	{
	public:
		template<typename T>
		static void AddListener(std::function<bool(const T&)> callback)
		{
			CString eventName = T::GetNameStatic();
			auto& instance = Get();
			auto it = instance.m_Listeners.find(eventName);
			
			if (it == instance.m_Listeners.end())
			{
				instance.m_Listeners.emplace(std::make_pair(eventName, CVector<std::function<bool(const Event&)>>()));
				it = instance.m_Listeners.find(eventName);
			}

			it->second.emplace_back([=](const Event& event) {
				if (auto ptr = dynamic_cast<const T*>(&event))
				{
					return callback(*ptr);
				}

				return false;
			});
		}
	private:
		EventManager() = default;
		~EventManager() = default;

		friend class EventDispatcher;
		inline static EventManager& Get()
		{
			static EventManager instance;
			return instance;
		}
	private:
		CMap<CString, CVector<::std::function<bool(const Event&)>>> m_Listeners;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			:m_Event(e) {}

		void Dispatch()
		{
			auto& instance = EventManager::Get();
			auto it = instance.m_Listeners.find(m_Event.GetName());
			if (it != instance.m_Listeners.end())
			{
				for (auto& listener : it->second)
				{
					if (!m_Event.handled)
					{
						m_Event.handled |= listener(m_Event);
					}
				}
			}
		}
	private:
		Event& m_Event;
	};
}