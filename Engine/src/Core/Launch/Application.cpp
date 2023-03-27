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
		Tests::RunAllTests();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			m_pWindow->OnUpdate();
		}
	}

	void Application::CreateAppWindow(const WindowProperties& props)
	{
		m_pWindow = Window::Create(props);
	}
}