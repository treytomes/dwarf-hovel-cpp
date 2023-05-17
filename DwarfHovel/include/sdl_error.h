#pragma once

#include <stdexcept>
#include <string>

class SDLError : public std::exception {
public:
	SDLError();
	char const* what() const;

private:
	std::string message;
};
