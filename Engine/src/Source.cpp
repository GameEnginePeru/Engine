#include "Core/Core.h"
#include <iostream>

namespace ENGINE_NAMESPACE
{
	class Game : public Application
	{
	public:
		inline Game(const CommandLineArgs& args) : Application (args) { }
	};

	Application* CreateApplication(CommandLineArgs args)
	{
		return new Game(args);
	}
}