#include "main.h"

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

void render(Window* window);

int main(int argc, char* argv[]) {
	Window* window = nullptr;
	int error_code = 0;

	try {
		System::initialize();
		Logger::get_instance()->write(LogLevel::LOG_INFO, "Starting %s.", WINDOW_TITLE);

        window = new Window(WINDOW_TITLE, ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT);

		window->init_gl();

		//SDL_Delay(3000);

		bool is_running = true;
		while (is_running) {
			SDL_Event evt;
			while (SDL_PollEvent(&evt)) {
				switch (evt.type) {
				case SDL_QUIT:
					Logger::get_instance()->write(LogLevel::LOG_INFO, &evt);
					is_running = false;
					break;
				case SDL_WINDOWEVENT:
					if (window->can_handle_event(&evt.window)) {
						window->handle_event(&evt.window);
					}
					break;
				case SDL_KEYUP:
					break;
				case SDL_KEYDOWN:
					break;
				}
			}

			render(window);
		}
	}
	catch (const std::exception& e) {
		Logger::get_instance()->write(LogLevel::LOG_FATAL, "Unable to recover: %s", e.what());
		error_code = 1;
	}

	if (window != nullptr) {
		delete window;
		window = nullptr;
	}

	return error_code;
}


void render(Window* window) {
	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 224; y++) {
			window->texture->set_pixel(x, y, 0.1f, 0.1f, 0.1f);
		}
	}
	for (int x = 0; x < 256; x++) {
		window->texture->set_pixel(x, 0, 1.0f, 0, 0);
		window->texture->set_pixel(x, 223, 1.0f, 0, 0);
	}
	for (int y = 0; y < 224; y++) {
		window->texture->set_pixel(0, y, 0, 1.0f, 0);
		window->texture->set_pixel(255, y, 0, 1.0f, 0);
	}
	window->texture->set_pixel(50, 50, 0, 1.0f, 1.0f);
	window->texture->refresh(true);

	window->present();
}
