#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include <functional>

#include <string>
#include <map>
#include <vector>
#include <unordered_map>

typedef std::string CString;

template<typename Key, typename Value>
class CMap : public std::map<Key, Value> {};

template<typename Key, typename Value>
class CUnorderedMap : public std::map<Key, Value> {};

template<typename T>
class CVector : public std::vector<T> {};
