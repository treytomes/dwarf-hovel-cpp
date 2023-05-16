#include "glew_error.h"
#include <SDL.h>
#include "logger.h"

GLEWError::GLEWError(GLenum _code) {
	code = _code;
	const char* errorString = (const char*)glewGetErrorString(code);
	message = errorString;
	Logger::get_instance()->write(LogLevel::LOG_ERROR, message.c_str());
}

char const* GLEWError::what() const {
	return message.c_str();
}
