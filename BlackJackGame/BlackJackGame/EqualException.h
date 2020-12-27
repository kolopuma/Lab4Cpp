#pragma once
#include <stdexcept>
class EqualException :public std::exception
{
public:
	EqualException();
};

