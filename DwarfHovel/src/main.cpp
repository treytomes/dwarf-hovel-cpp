﻿#include "main.h"

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include "moremath.h"

class DemoGameState : public GameState {
public:
	DemoGameState(GameStateManager* parent);
	void update(unsigned int delta_time_ms);
	void render(IRenderContext* context, unsigned int delta_time_ms);
	void handle_event(SDL_MouseMotionEvent* evt);
	void handle_event(SDL_KeyboardEvent* evt);

private:
	float angle;
	unsigned int mouse_x;
	unsigned int mouse_y;
};

DemoGameState::DemoGameState(GameStateManager* parent)
	: GameState(parent), angle(0.0f), mouse_x(0u), mouse_y(0u) {
}

void DemoGameState::update(unsigned int delta_time_ms) {
	angle += 0.25f * delta_time_ms * 3.141f / 180.0f;
}

void DemoGameState::render(IRenderContext* context, unsigned int delta_time_ms) {
	const unsigned int max_x = context->get_width() - 1;
	const unsigned int max_y = context->get_height() - 1;
	const unsigned int center_x = max_x / 2;
	const unsigned int center_y = max_y / 2;

	context->clear(Color(0.1f, 0.1f, 0.1f));

	context->draw_h_line(0, max_x, 0u, Color(1.0f, 0.0f, 0.0f));
	context->draw_h_line(0, max_x, max_y, Color(1.0f, 1.0f, 0.0f));
	context->draw_v_line(0, 0, max_y, Color(0.0f, 1.0f, 0.0f));
	context->draw_v_line(max_x, 0, max_y, Color(0.0f, 1.0f, 1.0f));

	context->set_pixel(Vector2UI(50u, 50u), Color(0.0f, 0.0f, 1.0f));

	context->draw_filled_rect(Vector2UI(55u, 65u), Vector2UI(105u, 90u), Color(1.0f, 0.5f, 0.25f));

	context->draw_line(Vector2UI(0, 0), Vector2UI(max_x, max_y), Color(1.0f, 0.0f, 1.0f));
	context->draw_line(Vector2UI(0, max_y), Vector2UI(max_x, 0), Color(1.0f, 0.0f, 1.0f));

	context->draw_circle(Vector2UI(center_x - 20, center_y - 50), 25, Color(1.0f, 0.0f, 0.0f));
	context->flood_fill(Vector2UI(center_x - 20, center_y - 50), Color(0.5f, 0.0f, 0.5f), Color(1.0f, 0.0f, 0.0f));

	context->draw_circle(Vector2UI(center_x, center_y), 25, Color(1.0f, 0.0f, 0.0f));

	context->draw_line(Vector2UI(center_x, center_y), Vector2UI(center_x - (unsigned int)(25 * cos(angle)), center_y - (unsigned int)(25 * sin(angle))), Color(0.5f, 0.0f, 0.0f));

	context->draw_string(Vector2UI(50, 190), Color(1.0f, 1.0f, 0.1f), Color(0.0f, 0.0f, 0.9f), "Hello, world!");
	context->draw_char(Vector2UI(50, 200), Color(1.0f, 1.0f, 0.9f), Color(0.0f, 0.0f, 0.1f), '*');

	if (math::is_in_range(mouse_x, 0u, context->get_width() - 1) && math::is_in_range(mouse_y, 0u, context->get_height() - 1)) {
		context->draw_circle(Vector2UI(mouse_x, mouse_y), 4, Color(1.0f, 1.0f, 0.0f));
		context->flood_fill(Vector2UI(mouse_x, mouse_y), Color(1.0f, 1.0f, 0.0f), Color(1.0f, 1.0f, 0.0f));
	}
}

void DemoGameState::handle_event(SDL_MouseMotionEvent* evt) {
	Settings* settings = Settings::get_instance();
	unsigned int actual_width = settings->actual_window_size.x;
	unsigned int actual_height = settings->actual_window_size.y;
	float aspect_ratio = (float)settings->virtual_window_size.x / (float)settings->virtual_window_size.y;
	float height_from_width = (float)actual_width / aspect_ratio;
	float width_from_height = (float)actual_height * aspect_ratio;

	unsigned int x = evt->x;
	unsigned int y = evt->y;

	// TODO: Convert actual screen position to virtual screen position.

	if (actual_width > width_from_height) {
		if (x > 0) {
			x -= (actual_width - width_from_height) / 2;
		} else {
			x += (actual_width - width_from_height) / 2;
		}
		actual_width = width_from_height;
	}
	if (actual_height > height_from_width) {
		if (y > 0) {
			y -= (actual_height - height_from_width) / 2;
		} else {
			y += (actual_height - height_from_width) / 2;
		}
		actual_height = height_from_width;
	}

	x *= (float)settings->virtual_window_size.x / (float)actual_width;
	y *= (float)settings->virtual_window_size.y / (float)actual_height;

	mouse_x = x;
	mouse_y = y;

	LOG_DEBUG("Mouse position: (%d, %d)", x, y);
}

void DemoGameState::handle_event(SDL_KeyboardEvent* evt) {
	if (evt->state == SDL_PRESSED) {
		if (evt->keysym.sym == SDLK_ESCAPE) {
			leave();
		}
	}
}

int main(int argc, char* argv[]) {
	Window* window = nullptr;
	int error_code = 0;

	try {
		System::initialize();
		LOG_INFO("Starting %s.", Settings::get_instance()->window_title.c_str());

        window = new Window(Settings::get_instance()->window_title, Settings::get_instance()->actual_window_size);
		window->init_gl();
		window->enter(new DemoGameState(window));

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
