#include "Core/Launch/Application.h"
#include "Tests/RunTests.h"
#include "Core/Logger/Logger.h"

namespace ENGINE_NAMESPACE
{
	Application* Application::s_pThisApp = nullptr;

	Application::Application(CommandLineArgs args)
	{
		s_pThisApp = this;
		Logger::Get().Init();
		Logger::SetFlags(LogFlags::CONSOLE_LOG);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			Tests::RunAllTests();
			std::cin.get();
		}
	}
}