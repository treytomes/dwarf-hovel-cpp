#pragma once

#include <stdexcept>
#include <string>
#include <gl\glew.h>

class GLError : public std::exception {
public:
	GLError(GLenum _code);
	char const* what() const;

private:
	std::string message;
	GLenum code;
};
