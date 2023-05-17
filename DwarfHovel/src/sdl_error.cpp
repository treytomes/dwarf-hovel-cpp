#include "sdl_error.h"
#include <SDL.h>
#include "logger.h"

SDLError::SDLError() {
	message = SDL_GetError();
	Logger::get_instance()->write(LogLevel::LOG_ERROR, message.c_str());
}

char const* SDLError::what() const {
	return message.c_str();
}
