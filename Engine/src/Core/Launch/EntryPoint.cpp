#include "Core/Launch/Application.h"

extern Engine::Application* Engine::CreateApplication(CommandLineArgs args);

#ifdef PLATFORM_WINDOWS
int main(int argc, char** argv)
{
	auto app = Engine::CreateApplication({ argc, argv });
	app->Run();
	delete app;
	return 0;
}
#elif PLATFORM_APPLE
#elif PLATFORM_LINUX
#endif