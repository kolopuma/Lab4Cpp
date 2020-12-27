#pragma once
#include <stdexcept>
class LoseException : public std::exception
{
public:
	LoseException();
};

