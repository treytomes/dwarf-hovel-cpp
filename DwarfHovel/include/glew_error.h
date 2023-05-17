#pragma once

#include <stdexcept>
#include <string>
#include <gl\glew.h>

class GLEWError : public std::exception {
public:
	GLEWError(GLenum code);
	char const* what() const;

private:
	std::string message;
	GLenum code;
};
