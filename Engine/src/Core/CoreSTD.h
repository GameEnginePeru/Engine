#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <sstream>
#include <fstream>

typedef std::string CString;

template<typename Key, typename Value>
class CMap : public std::map<Key, Value> {};

template<typename T>
class CVector : public std::vector<T> {};
