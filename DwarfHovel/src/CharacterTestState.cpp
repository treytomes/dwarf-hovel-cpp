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
	  grid_offset_x(GRID_OFFSET), grid_offset_y(GRID_OFFSET), player_facing(Direction::SOUTH) {
	Vector2UI size = Settings::get_instance()->virtual_window_size;

	player_north_bitmap = new Bitmap2bpp(
		"01111110"
		"11111111"
		"11111111"
		"11111111"
		"11111111"
		"11111111"
		"11111111"
		"01111110"
	);
	player_south_bitmap = new Bitmap2bpp(
		"01111110"
		"11111111"
		"11311311"
		"11311311"
		"11111111"
		"11222211"
		"11122111"
		"01111110"
	);
	player_east_bitmap = new Bitmap2bpp(
		"01111110"
		"11111111"
		"11111311"
		"11111311"
		"11111111"
		"11111222"
		"11111122"
		"01111110"
	);
	player_west_bitmap = new Bitmap2bpp(
		"01111110"
		"11111111"
		"11311111"
		"11311111"
		"11111111"
		"22211111"
		"22111111"
		"01111110"
	);


	player_base = new Sprite(player_south_bitmap);
	player_base->color1 = SKIN_COLOR;
	player_base->color2 = MOUTH_COLOR;
	player_base->color3 = EYE_COLOR;
	player_base->position = Point2UI(size.x / 2, size.y / 2);
}

CharacterTestState::~CharacterTestState() {
	if (player_south_bitmap != nullptr) delete player_south_bitmap;
	if (player_north_bitmap != nullptr) delete player_north_bitmap;
	if (player_east_bitmap != nullptr) delete player_east_bitmap;
	if (player_west_bitmap != nullptr) delete player_west_bitmap;
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
	if (player_speed != Vector2UI::zero()) {
		float grid_offset_speed = player_speed.magnitude() / 4.0f;;
		switch (player_facing) {
		case Direction::NORTH:
			grid_offset_y += grid_offset_speed;
			break;
		case Direction::SOUTH:
			grid_offset_y -= grid_offset_speed;
			break;
		case Direction::WEST:
			grid_offset_x += grid_offset_speed;
			break;
		case Direction::EAST:
			grid_offset_x -= grid_offset_speed;
			break;
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
	for (y = (int)grid_offset_y % GRID_SPACING; y < size.y; y += GRID_SPACING) {
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

	for (x = (int)grid_offset_x % GRID_SPACING; x < size.x; x += GRID_SPACING) {
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

	GameState::render(context, delta_time_ms);
}

void CharacterTestState::handle_event(SDL_MouseMotionEvent* evt) {
	GameState::handle_event(evt);
}

void CharacterTestState::handle_event(SDL_KeyboardEvent* evt) {
	player_speed = Vector2UI::zero();

	if (evt->state == SDL_PRESSED) {
		switch (evt->keysym.sym) {
		case SDLK_ESCAPE:
			leave();
			break;
		case SDLK_w:
			player_speed = Vector2UI(0, -1);
			player_base->bitmap = player_north_bitmap;
			player_facing = Direction::NORTH;
			break;
		case SDLK_s:
			player_speed = Vector2UI(0, 1);
			player_base->bitmap = player_south_bitmap;
			player_facing = Direction::SOUTH;
			break;
		case SDLK_a:
			player_speed = Vector2UI(-1, 0);
			player_base->bitmap = player_west_bitmap;
			player_facing = Direction::WEST;
			break;
		case SDLK_d:
			player_speed = Vector2UI(1, 0);
			player_base->bitmap = player_east_bitmap;
			player_facing = Direction::EAST;
			break;
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
