#include "Core/Launch/Application.h"
#include "Core/Logger/Logger.h"
#include "Tests/RunTests.h"
#include "Graphics/API/RendererAPI.h"
#include "Input/Input.h"

namespace ENGINE_NAMESPACE
{
	Application* Application::s_pThisApp = nullptr;

	Application::Application(CommandLineArgs args)
	{
		s_pThisApp = this;
		Logger::Get().Init();
		Logger::SetFlags(LogFlags::CONSOLE_LOG);
		Random::Init();
		//Tests::RunAllTests();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			m_pWindow->OnUpdate();
			RenderCommand::Clear();

			// This should go after the Update function!
			Input::Update();
		}
	}

	void Application::CreateAppWindow(const WindowProperties& props)
	{
		RendererAPI::SetApi(RendererAPI::API::OPENGL);
		m_pWindow = Window::Create(props);
		RenderCommand::SetClearColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}
}