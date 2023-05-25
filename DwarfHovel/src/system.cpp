#include "system.h"

#include <SDL.h>
#include <stdexcept>
#include <cstdlib>

#include "Logger.h"
#include "Settings.h"
#include "sdl_error.h"

System::System() {
	Settings::initialize();
	Logger::initialize();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		throw SDLError();
	}

	// Use OpenGL 3.1 Core.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}


System::~System() {
	SDL_Quit();

	LOG_INFO("And that is all.");
	Logger::shutdown();
	Settings::shutdown();
}

System* System::instance = nullptr;

void System::initialize() {
	if (instance != nullptr) {
		shutdown();
	}
	atexit(System::at_exit);
	instance = new System();
}

void System::shutdown() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

System* System::get_instance() {
	return instance;
}

void System::at_exit() {
	System::shutdown();
}
