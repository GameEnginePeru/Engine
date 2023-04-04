#pragma once

#include "Core/HAL/EngineDefinitions.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <functional>
#include <random>

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <array>
#include <format>

namespace ENGINE_NAMESPACE
{
	// STL String typedef

	typedef std::string CString;

	// STL Container definitions

	template<typename Key, typename Value>
	class CMap : public std::map<Key, Value> {};

	template<typename Key, typename Value, typename Hasher = std::hash<Key>>
	class CUnorderedMap : public std::unordered_map<Key, Value, Hasher> {};

	template<typename T>
	class CVector : public std::vector<T> 
	{
	public:
		using std::vector<T>::vector;
		CVector(size_t reserveSize) : std::vector<T>() { this->reserve(reserveSize); }
	};


	// Smart Pointer Definitions

	/// Unique Pointer definition
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... ARG>
	constexpr Scope<T> CreateScope(ARG&& ... args)
	{
		return std::make_unique<T>(std::forward<ARG>(args)...);
	}

	/// Shared Pointer definition
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... ARG>
	constexpr Ref<T> CreateRef(ARG&& ... args)
	{
		return std::make_shared<T>(std::forward<ARG>(args)...);
	}
}