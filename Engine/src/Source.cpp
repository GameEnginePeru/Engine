#include "Core/Core.h"
#include "Graphics/Resources/Resources.h"

namespace ENGINE_NAMESPACE
{
	class Game : public Application
	{
	public:
		inline Game(const CommandLineArgs& args) : Application (args) 
		{
			CreateAppWindow();
			Resources::CreateShader("assets/shaders/default.glsl");
		}
	};

	Application* CreateApplication(CommandLineArgs args)
	{
		return new Game(args);
	}
}