#include "sdl_error.h"
#include <SDL.h>
#include "io/io.h"

SDLError::SDLError() {
	message = SDL_GetError();
	LOG_ERROR(message.c_str());
}

char const* SDLError::what() const {
	return message.c_str();
}
