#pragma once
#include "Core/CoreMinimal.h"
#include "Graphics/Resources/Shader.h"
#include "Core/Containers/StringId/StringId.h"

namespace ENGINE_NAMESPACE
{
	class Resources
	{
	public:
		// Get Function

		static Ref<Shader> GetShader(const StringId id);

		// Create Functions

		static void CreateShader(const CString& path);

		// Other Utils

		static void ReloadShaders();
	};
}