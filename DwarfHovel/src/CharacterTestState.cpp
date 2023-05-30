#include "CharacterTestState.h"

#include <random>
#include <string>
#include <cmath>
#include "Logger.h"
#include "OEM437.h"
#include "Point2UI.h"
#include "Settings.h"
#include "UIElement.h"
#include "UILabel.h"
#include "UIButton.h"
#include "Vector2UI.h"

#define IDB_BUTTON0 0
#define IDB_BUTTON1 1
#define IDB_BUTTON2 2
#define IDB_BUTTON3 3
#define IDB_BUTTON4 4

#define TIME_PULSE_X 3000
#define TIME_PULSE_Y 5000

CharacterTestState::CharacterTestState()
	: GameState(), total_elapsed_time(0u), last_horizontal_pulse_time(0u), last_vertical_pulse_time(0u) {
}

CharacterTestState::~CharacterTestState() {
}

void CharacterTestState::update(unsigned int delta_time_ms) {
	total_elapsed_time += delta_time_ms;

	if (total_elapsed_time - last_horizontal_pulse_time > TIME_PULSE_X * 2) {
		last_horizontal_pulse_time = total_elapsed_time;
	}
	if (total_elapsed_time - last_vertical_pulse_time > TIME_PULSE_Y * 2) {
		last_vertical_pulse_time = total_elapsed_time;
	}

	GameState::update(delta_time_ms);
}

#define PULSE_WIDTH 8

void CharacterTestState::render(IRenderContext* context, unsigned int delta_time_ms) {
	context->clear(Color(0.02f, 0.02f, 0.02f));

	Vector2UI size = Settings::get_instance()->virtual_window_size;
	bool is_pulsing_x = total_elapsed_time < last_horizontal_pulse_time + TIME_PULSE_X;
	unsigned int pulse_x = math::lerp(0u, size.x, (float)(total_elapsed_time - last_horizontal_pulse_time) / TIME_PULSE_X);

	Color base_color = Color::green().darkest();
	Color bright_color = Color::green();

	unsigned int x;
	unsigned int y;
	for (y = 4u; y < size.y; y += 8) {
		for (x = 0u; x < size.x; x++) {
			if (is_pulsing_x) {
				auto dist = sqrtf((x - pulse_x) * (x - pulse_x));
				if (dist <= PULSE_WIDTH) {
					Color c = base_color.lerp(bright_color, 1.0f - (float)dist / PULSE_WIDTH);
					context->set_pixel(x, y, c);
				} else {
	                context->set_pixel(x, y, base_color);
				}
			} else {
				context->set_pixel(x, y, base_color);
			}
		}
	}

	bool is_pulsing_y = total_elapsed_time < last_vertical_pulse_time + TIME_PULSE_Y;
	unsigned int pulse_y = math::lerp(0u, size.y, (float)(total_elapsed_time - last_vertical_pulse_time) / TIME_PULSE_Y);

	for (x = 4u; x < size.x; x += 8) {
		for (y = 0u; y < size.y; y++) {
			if (is_pulsing_y) {
				auto dist = sqrtf((y - pulse_y) * (y - pulse_y));
				if (dist <= PULSE_WIDTH) {
					Color c = base_color.lerp(bright_color, 1.0f - (float)dist / PULSE_WIDTH);
					context->set_pixel(x, y, c);
				} else {
	                context->set_pixel(x, y, base_color);
				}
			} else {
				context->set_pixel(x, y, base_color);
			}
		}
	}

	GameState::render(context, delta_time_ms);
}

void CharacterTestState::handle_event(SDL_MouseMotionEvent* evt) {
	GameState::handle_event(evt);
}

void CharacterTestState::handle_event(SDL_KeyboardEvent* evt) {
	if (evt->state == SDL_PRESSED) {
		if (evt->keysym.sym == SDLK_ESCAPE) {
			leave();
		}
	}
	
	GameState::handle_event(evt);
}

void CharacterTestState::handle_event(SDL_UserEvent* evt) {
	float volume = 0.5f;

	switch (evt->code) {
		case IDB_BUTTON0:
			break;
		case IDB_BUTTON1:
			break;
		case IDB_BUTTON2:
			break;
		case IDB_BUTTON3:
			break;
		case IDB_BUTTON4:
			break;
	}
}
