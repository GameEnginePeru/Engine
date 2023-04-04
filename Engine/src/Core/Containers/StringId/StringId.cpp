#include "Core/Containers/StringId/StringId.h"
#include "Utils/Hash/FNV-1a.h"

namespace ENGINE_NAMESPACE
{
	static CUnorderedMap<StringId, const char*> g_StringIdTable;

	StringId InternString(const char* str)
	{
		StringId sid = fnv1a_32(str);

		auto it = g_StringIdTable.find(sid);

		if (it == g_StringIdTable.end())
		{
			g_StringIdTable[sid] = _strdup(str);
		}

		return sid;
	}

	const char* RetrieveString(const StringId& sid)
	{
		auto it = g_StringIdTable.find(sid);
		if (it == g_StringIdTable.end())
		{
			return "";
		}

		return it->second;
	}
}