#include "glew_error.h"
#include <SDL.h>
#include "Logger.h"

GLEWError::GLEWError(GLenum _code) {
	code = _code;
	const char* errorString = (const char*)glewGetErrorString(code);
	message = errorString;
	LOG_ERROR(message.c_str());
}

char const* GLEWError::what() const {
	return message.c_str();
}
