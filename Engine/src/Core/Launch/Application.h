#pragma once
#include "Core/CoreMinimal.h"

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

		inline static Application* GetApp() { return s_pThisApp; }
	private:
		friend int ::main(int argc, char** argv);
		void Run();
	private:
		static Application* s_pThisApp;
	};

	Application* CreateApplication(CommandLineArgs args);
}