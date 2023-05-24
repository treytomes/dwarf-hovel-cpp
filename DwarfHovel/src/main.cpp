#include "main.h"

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include <cstdarg>
#include <string>
#include <vector>
#include "moremath.h"
#include "Rectangle.h"
#include "OEM437.h"

void try_register_event(unsigned int& event_id) {
	event_id = SDL_RegisterEvents(1);
	if (event_id == ((unsigned int)-1)) {
		LOG_ERROR("Failed to register the button event.");
	}
}

int main(int argc, char* argv[]) {
	Window* window = nullptr;
	int error_code = 0;

	try {
		System::initialize();
		LOG_INFO("Starting %s.", Settings::get_instance()->window_title.c_str());

		LOG_INFO("Registering custom events.");
		try_register_event(UIButton::command_event_id);

        window = new Window(Settings::get_instance()->window_title, Settings::get_instance()->actual_window_size);
		window->init_gl();
		window->enter(new MainMenuGameState());

		//SDL_Delay(3000);

		bool is_running = true;
		unsigned int last_frame_ticks = SDL_GetTicks();
		while (is_running && !window->has_active_state()) {
			SDL_Event evt;
			while (SDL_PollEvent(&evt)) {
				switch (evt.type) {
				case SDL_QUIT:
					LOG_INFO(&evt);
					is_running = false;
					break;
				case SDL_WINDOWEVENT:
					if (window->can_handle_event(&evt.window)) {
						window->handle_event(&evt.window);
					}
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					if (window->can_handle_event(&evt.key)) {
						window->handle_event(&evt.key);
					}
					break;
				case SDL_MOUSEMOTION:
					if (window->can_handle_event(&evt.motion)) {
						window->handle_event(&evt.motion);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					if (window->can_handle_event(&evt.button)) {
						window->handle_event(&evt.button);
					}
					break;
				case SDL_MOUSEWHEEL:
					if (window->can_handle_event(&evt.wheel)) {
						window->handle_event(&evt.wheel);
					}
					break;
				default:
					if (evt.user.type == UIButton::command_event_id) {
						window->handle_event(&evt.user);
					}
					break;
				}
			}

			unsigned int this_frame_ticks = SDL_GetTicks();
			unsigned int delta_time_ms = this_frame_ticks - last_frame_ticks;
			window->update(delta_time_ms);
			window->render(window->texture, delta_time_ms);
			last_frame_ticks = this_frame_ticks;
			window->present();
		}
	}
	catch (const std::exception& e) {
		LOG_FATAL("Unable to recover: %s", e.what());
		error_code = 1;
	}

	if (window != nullptr) {
		delete window;
		window = nullptr;
	}

	return error_code;
}
