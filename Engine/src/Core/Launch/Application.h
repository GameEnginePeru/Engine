#pragma once
#include "Core/CoreMinimal.h"
#include "Core/Window/Window.h"
#include "Events/ApplicationEvents.h"

int main(int argc, char** argv);

namespace ENGINE_NAMESPACE
{
	struct CommandLineArgs
	{
		int32 count = 0;
		char** args = nullptr;

		const char* operator[](uint32 index) const
		{
			return args[index];
		}
	};

	class Application
	{
	public:
		Application(CommandLineArgs args);
		~Application();

		inline Window& GetWindow() const { return *m_pWindow; }
		inline static Application* GetApp() { return s_pThisApp; }
	private:
		friend int ::main(int argc, char** argv);
		void Run();

		bool OnWindowClose(const WindowCloseEvent& e);
	protected:
		void CreateAppWindow(const WindowProperties& props = WindowProperties());
	private:
		bool m_bIsRunning = true;

		Scope<Window> m_pWindow;
		static Application* s_pThisApp;
	};

	Application* CreateApplication(CommandLineArgs args);
}