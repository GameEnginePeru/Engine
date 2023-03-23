#include "Application.h"
#include "Tests/RunTests.h"

namespace Engine
{
	Application* Application::s_pThisApp = nullptr;

	Application::Application(CommandLineArgs args)
	{
		s_pThisApp = this;
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