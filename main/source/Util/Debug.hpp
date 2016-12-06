#pragma once

#include <iostream>

#define BB __PRETTY_FUNCTION__
#define AA __LINE__

#define stringify(x) #x
#define stringify2(x) stringify(x)
#define stringify3(x) stringify2(x)
#define FILE2(a, b) stringify(a ; b)
#define FILE(a, b) FILE2(__func__, b)
#define MACRO(macro) macro

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
//#define LOG(x) overmon::log(stringify2(MACRO(__BASE_FILE__); __LINE__:), x);
#define LOG(...) overmon::log(__FILENAME__, "\033[1;31m" "- " stringify2(__LINE__) ";\033[0m", __VA_ARGS__);

namespace overmon
{

void log() {}

template<typename First>
void log(First &&first)
{
	std::cout << std::forward<First>(first) << std::endl;
}

template<typename First, typename ...Rest>
void log(First &&first, Rest &&...rest)
{
	std::cout << std::forward<First>(first) << " ";
	log(std::forward<Rest>(rest)...);
}

}
