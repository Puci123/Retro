#pragma once

#include <iostream>

#define ASSERT(X)	if(!(X)) __debugbreak()
#define LOG(X)		std::cout << "[LOG] " << X << std::endl
