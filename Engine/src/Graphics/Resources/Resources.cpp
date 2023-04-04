#include "Graphics/Resources/Resources.h"

namespace ENGINE_NAMESPACE
{
	CUnorderedMap<StringId, Ref<Shader>> g_ShaderMap;

	Ref<Shader> Resources::GetShader(const StringId id)
	{
		return g_ShaderMap[id];
	}

	void Resources::CreateShader(const CString& path)
	{
		auto slashIndex = path.find_last_of('/');
		auto dotIndex = path.find_last_of('.');
		CString name = path.substr(slashIndex + 1, dotIndex - slashIndex - 1);
		StringId intern = InternString(name.c_str());

		g_ShaderMap[intern] = Shader::Create(path);
	}

	void Resources::ReloadShaders()
	{
		for (const auto& shader : g_ShaderMap) shader.second->Reload();
	}
}