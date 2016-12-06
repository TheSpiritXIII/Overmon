#pragma once

#include <iostream>

namespace overmon
{

void debug() {}

template<typename First>
void debug(First &&first)
{
	std::cout << std::forward<First>(first) << std::endl;
}

template<typename First, typename ...Rest>
void debug(First &&first, Rest &&...rest)
{
	std::cout << std::forward<First>(first) << " ";
	log(std::forward<Rest>(rest)...);
}

}
