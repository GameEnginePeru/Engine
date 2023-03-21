#include "Core/Core.h"
#include <iostream>

namespace Engine
{
	class Game : public Application
	{
	public:
		inline Game(const CommandLineArgs& args) : Application (args)
		{
			std::cout << "Hello World" << std::endl;
		}
	};

	Application* CreateApplication(CommandLineArgs args)
	{
		return new Game(args);
	}
}