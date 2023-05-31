#include "CharacterTestState.h"

#include <random>
#include <string>
#include <cmath>
#include "bitmaps.h"
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
#define PULSE_WIDTH 8
#define PULSE_X_DELAY 3000
#define PULSE_Y_DELAY 5000
#define GRID_SPACING 8
#define GRID_OFFSET 4

#define SKIN_COLOR Color::sepia()
#define EYE_COLOR Color::blue().dark()
#define MOUTH_COLOR Color::red().darkest()

CharacterTestState::CharacterTestState()
	: GameState(), total_elapsed_time(0u), last_horizontal_pulse_time(0u), last_vertical_pulse_time(0u),
	  grid_offset_x(GRID_OFFSET), grid_offset_y(GRID_OFFSET), player_facing(Vector2I::south()), is_using_item(false) {
	Vector2UI size = Settings::get_instance()->virtual_window_size;

	player_base = new Sprite(&bitmaps::person_south);
	player_base->color1 = SKIN_COLOR;
	player_base->color2 = MOUTH_COLOR;
	player_base->color3 = EYE_COLOR;
	player_base->position = Point2UI(size.x / 2, size.y / 2);
}

CharacterTestState::~CharacterTestState() {
	if (player_base != nullptr) delete player_base;
}

void CharacterTestState::update(unsigned int delta_time_ms) {
	total_elapsed_time += delta_time_ms;

	if (total_elapsed_time - last_horizontal_pulse_time > TIME_PULSE_X + PULSE_X_DELAY) {
		last_horizontal_pulse_time = total_elapsed_time;
	}
	if (total_elapsed_time - last_vertical_pulse_time > TIME_PULSE_Y + PULSE_Y_DELAY) {
		last_vertical_pulse_time = total_elapsed_time;
	}

	player_base->position += player_speed;
	if (player_speed != Vector2I::zero()) {
		float grid_offset_speed = player_speed.magnitude() / 4.0f;
		if (player_facing == Vector2I::north()) {
			grid_offset_y += grid_offset_speed;
		} else if (player_facing == Vector2I::south()) {
			grid_offset_y -= grid_offset_speed;
		} else if (player_facing == Vector2I::west()) {
			grid_offset_x += grid_offset_speed;
		} else if (player_facing == Vector2I::east()) {
			grid_offset_x -= grid_offset_speed;
		}

		if (grid_offset_x < 0) {
			grid_offset_x += GRID_SPACING;
		}
		if (grid_offset_y < 0) {
			grid_offset_y += GRID_SPACING;
		}
	}

	GameState::update(delta_time_ms);
}

void CharacterTestState::render(IRenderContext* context, unsigned int delta_time_ms) {
	context->clear(Color(0.02f, 0.02f, 0.02f));

	Vector2UI size = Settings::get_instance()->virtual_window_size;
	bool is_pulsing_x = total_elapsed_time < last_horizontal_pulse_time + TIME_PULSE_X;
	unsigned int pulse_x = math::lerp(0u, size.x, (float)(total_elapsed_time - last_horizontal_pulse_time) / TIME_PULSE_X);

	Color base_color = Color::green().darkest();
	Color bright_color = Color::green();

	unsigned int x;
	unsigned int y;
	
	for (y = (unsigned int)grid_offset_y % GRID_SPACING; y < size.y; y += GRID_SPACING) {
		for (x = 0u; x < size.x; x++) {
			if (is_pulsing_x) {
				auto dist = sqrtf((float)(x - pulse_x) * (x - pulse_x));
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

	for (x = (unsigned int)grid_offset_x % GRID_SPACING; x < size.x; x += GRID_SPACING) {
		for (y = 0u; y < size.y; y++) {
			if (is_pulsing_y) {
				auto dist = sqrtf((float)(y - pulse_y) * (y - pulse_y));
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

	player_base->draw(context);
	if (is_using_item) {
		if (player_facing == Vector2I::north()) {
			LOG_INFO("use north");
			bitmaps::sword.draw(context, player_base->position + player_facing * 8, Color::transparent(), Color::white(), Color::gray(), Color::gray().darkest(), false, false);
		} else if (player_facing == Vector2I::south()) {
			LOG_INFO("use south");
			bitmaps::sword.draw(context, player_base->position + player_facing * 8, Color::transparent(), Color::white(), Color::gray(), Color::gray().darkest(), false, true);
		} else if (player_facing == Vector2I::west()) {
			LOG_INFO("use west");
			bitmaps::sword.draw(context, player_base->position + player_facing * 8, Color::transparent(), Color::white(), Color::gray(), Color::gray().darkest(), true, false);
		} else if (player_facing == Vector2I::east()) {
			LOG_INFO("use east");
			bitmaps::sword.draw(context, player_base->position + player_facing * 8, Color::transparent(), Color::white(), Color::gray(), Color::gray().darkest(), false, false);
		}
	}

	GameState::render(context, delta_time_ms);
}

void CharacterTestState::handle_event(SDL_MouseMotionEvent* evt) {
	GameState::handle_event(evt);
}

void CharacterTestState::handle_event(SDL_KeyboardEvent* evt) {
	if (evt->state == SDL_PRESSED) {
		switch (evt->keysym.sym) {
		case SDLK_ESCAPE:
			leave();
			break;
		case SDLK_w:
			player_speed = player_facing = Vector2I::north();
			player_base->bitmap = &bitmaps::person_north;
			break;
		case SDLK_s:
			player_speed = player_facing = Vector2I::south();
			player_base->bitmap = &bitmaps::person_south;
			break;
		case SDLK_a:
			player_speed = player_facing = Vector2I::west();
			player_base->bitmap = &bitmaps::person_west;
			break;
		case SDLK_d:
			player_speed = player_facing = Vector2I::east();
			player_base->bitmap = &bitmaps::person_east;
			break;
		case SDLK_SPACE:
			is_using_item = true;
			break;
		}
	} else {
		switch (evt->keysym.sym) {
		case SDLK_w:
			if (player_speed == Vector2I::north()) { player_speed = Vector2I::zero(); }
			break;
		case SDLK_s:
			if (player_speed == Vector2I::south()) { player_speed = Vector2I::zero(); }
			break;
		case SDLK_a:
			if (player_speed == Vector2I::west()) { player_speed = Vector2I::zero(); }
			break;
		case SDLK_d:
			if (player_speed == Vector2I::east()) { player_speed = Vector2I::zero(); }
			break;
		case SDLK_SPACE:
			is_using_item = false;
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
