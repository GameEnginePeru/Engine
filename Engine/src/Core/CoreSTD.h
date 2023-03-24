#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include <functional>

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <array>

typedef std::string CString;

template<typename Key, typename Value>
class CMap : public std::map<Key, Value> {};

template<typename Key, typename Value, typename Hasher = std::hash<Key>>
class CUnorderedMap : public std::unordered_map<Key, Value, Hasher> {};

template<typename T>
class CVector : public std::vector<T> {};