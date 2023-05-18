#include "gl_error.h"
#include <SDL.h>
#include "Logger.h"

GLError::GLError(GLenum _code) {
	code = _code;
	const char* errorString = (const char*)gluErrorString(_code);
	message = errorString;
	LOG_ERROR(message.c_str());
}

char const* GLError::what() const {
	return message.c_str();
}
