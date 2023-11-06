#pragma once

#include <iostream>

#define ASSERT(X)		if(!(X)) __debugbreak()
#define LOG(X)			std::cout << "[LOG] " << X << std::endl
#define LOG_ERROR(X)	std::cout << "\033[1;31m[ERROR]\033[0m " << X << std::endl
