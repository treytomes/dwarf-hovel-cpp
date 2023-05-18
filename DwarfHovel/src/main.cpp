﻿#include "main.h"

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

float angle = 0.0f;
void render(IRenderContext* ctx, unsigned int delta_ticks) {
	const unsigned int max_x = ctx->get_width() - 1;
	const unsigned int max_y = ctx->get_height() - 1;
	const unsigned int center_x = max_x / 2;
	const unsigned int center_y = max_y / 2;

	ctx->clear(Color(0.1f, 0.1f, 0.1f));

	ctx->draw_h_line(0, max_x, 0u, Color(1.0f, 0.0f, 0.0f));
	ctx->draw_h_line(0, max_x, max_y, Color(1.0f, 1.0f, 0.0f));
	ctx->draw_v_line(0, 0, max_y, Color(0.0f, 1.0f, 0.0f));
	ctx->draw_v_line(max_x, 0, max_y, Color(0.0f, 1.0f, 1.0f));

	ctx->set_pixel(Vector2UI(50u, 50u), Color(0.0f, 0.0f, 1.0f));

	ctx->draw_filled_rect(Vector2UI(55u, 65u), Vector2UI(105u, 90u), Color(1.0f, 0.5f, 0.25f));

	ctx->draw_line(Vector2UI(0, 0), Vector2UI(max_x, max_y), Color(1.0f, 0.0f, 1.0f));
	ctx->draw_line(Vector2UI(0, max_y), Vector2UI(max_x, 0), Color(1.0f, 0.0f, 1.0f));

	ctx->draw_circle(Vector2UI(center_x - 20, center_y - 50), 25, Color(1.0f, 0.0f, 0.0f));
	ctx->flood_fill(Vector2UI(center_x - 20, center_y - 50), Color(0.5f, 0.0f, 0.5f), Color(1.0f, 0.0f, 0.0f));

	ctx->draw_circle(Vector2UI(center_x, center_y), 25, Color(1.0f, 0.0f, 0.0f));

	angle += 0.25f * delta_ticks * 3.141 / 180;
	ctx->draw_line(Vector2UI(center_x, center_y), Vector2UI(center_x - 25 * cos(angle), center_y - 25 * sin(angle)), Color(0.5f, 0.0f, 0.0f));

	ctx->draw_string(Vector2UI(50, 190), Color(1.0f, 1.0f, 0.1f), Color(0.0f, 0.0f, 0.9f), "Hello, world!");
	ctx->draw_char(Vector2UI(50, 200), Color(1.0f, 1.0f, 0.9f), Color(0.0f, 0.0f, 0.1f), '*');
}

int main(int argc, char* argv[]) {
	Window* window = nullptr;
	int error_code = 0;

	try {
		System::initialize();
		LOG_INFO("Starting %s.", WINDOW_TITLE);

        window = new Window(WINDOW_TITLE, ACTUAL_WINDOW_WIDTH, ACTUAL_WINDOW_HEIGHT);

		window->init_gl();

		//SDL_Delay(3000);

		bool is_running = true;
		unsigned int last_frame_ticks = SDL_GetTicks();
		while (is_running) {
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
				case SDL_KEYUP:
					break;
				case SDL_KEYDOWN:
					break;
				}
			}

			unsigned int this_frame_ticks = SDL_GetTicks();
			render(window->texture, this_frame_ticks - last_frame_ticks);
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
