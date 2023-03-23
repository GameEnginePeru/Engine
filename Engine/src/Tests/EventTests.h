#pragma once
#include "Events/ApplicationEvents.h"
#include "Events/EventManager.h"
#include "Tests/GenericTest.h"

namespace Engine::Tests::Events
{
	void StringIntegrityTest();
	void EventHandlerTest();

	void RunTests()
	{
		StringIntegrityTest();
		EventHandlerTest();
	}

	void StringIntegrityTest()
	{
		const uint32 width = 123, height = 456;
		Test test{ .name = "Event StringIntegrityTest" };
		WindowResizeEvent wre = WindowResizeEvent(width, height);

		auto callback1 = [&](const WindowResizeEvent& e) -> bool
		{
			CString compare = CString(e.GetName()) + ": " + std::to_string(width) + ", " + std::to_string(height);
			if (e.ToString() == compare)
			{
				test.bPassed = true;
			}
			return false;
		};

		EventManager::AddListener<WindowResizeEvent>(callback1);
		EventDispatcher dispatcher(wre);
		dispatcher.Dispatch();

		std::cout << test.name << (test.bPassed ? " passed" : " not passed") << std::endl;
	}

	void EventHandlerTest()
	{
		Test test{ .name = "Event HandledTest" };
		WindowCloseEvent wce = WindowCloseEvent();

		auto callback1 = [&](const WindowCloseEvent& e) -> bool { test.bPassed = true; return true; };
		auto callback2 = [&](const WindowCloseEvent& e) -> bool { test.bPassed = false; return false; };

		EventManager::AddListener<WindowCloseEvent>(callback1);
		EventManager::AddListener<WindowCloseEvent>(callback2);
		EventDispatcher dispatcher(wce);
		dispatcher.Dispatch();

		std::cout << test.name << (test.bPassed ? " passed" : " not passed") << std::endl;
	}
}