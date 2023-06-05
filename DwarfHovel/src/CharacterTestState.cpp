#include "CharacterTestState.h"

#include <string>
#include "bitmaps.h"
#include "Logger.h"
#include "OEM437.h"
#include "math/math.h"
#include "Settings.h"
#include "ui/ui.h"

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
	  grid_offset_x(GRID_OFFSET), grid_offset_y(GRID_OFFSET), player_facing(Vector2I::south()), is_using_item(false), item_angle(0.0f),
	  fountain(nullptr) {
	Vector2UI size = Settings::get_instance()->virtual_window_size;

	player_base = new Sprite(&bitmaps::player_south);
	player_base->position = Point2UI(size.x / 2, size.y / 2);

	ui->add_child(new UILabel(Point2UI(8, 8), "*Character Test*", Color::white(), Color::gray().darkest()));
}

CharacterTestState::~CharacterTestState() {
	if (player_base != nullptr) delete player_base;
	if (fountain != nullptr) delete fountain;
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

	item_angle += 6.0f * DEGREE;

	if (fountain != nullptr) {
		fountain->update(delta_time_ms);
		if (fountain->is_dead()) {
			delete fountain;
			fountain = nullptr;
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
				auto dist = fabsf((float)x - (float)pulse_x);
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
				auto dist = fabsf((float)y - (float)pulse_y);
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
		auto item_position = player_base->position + player_facing * 8;
		
		float actual_angle = 0.0f;
		bool is_moving = player_speed != Vector2I::zero();
		if (is_moving) {
			// Only waggle the item if the player is moving.
			actual_angle = (sinf(item_angle) + 1.0f) * (DEGREE * 90) / 2.0f;
		}

		if (player_facing == Vector2I::north()) {
			//LOG_INFO("use north");
			if (is_moving) {
				actual_angle += DEGREE * 180.0f;
				bitmaps::iron_sword.draw(context, item_position + Point2I(4, 8), false, true, actual_angle);
			} else {
				bitmaps::iron_sword.draw(context, item_position + Point2I(4, 0), false, false);
			}
		} else if (player_facing == Vector2I::south()) {
			//LOG_INFO("use south");
			if (is_moving) {
				bitmaps::iron_sword.draw(context, item_position + Point2I(4, 0), false, true, actual_angle);
			} else {
				bitmaps::iron_sword.draw(context, item_position + Point2I(4, 0), false, true);
			}
		} else if (player_facing == Vector2I::west()) {
			//LOG_INFO("use west");
			if (is_moving) {
				actual_angle += DEGREE * 90.0f;
				bitmaps::iron_sword.draw(context, item_position + Point2I(8, 4), false, true, actual_angle);
			} else {
				bitmaps::iron_sword.draw(context, item_position + Point2I(0, -4), true, false);
			}
		} else if (player_facing == Vector2I::east()) {
			//LOG_INFO("use east");
			if (is_moving) {
				actual_angle += DEGREE * 270.0f;
				bitmaps::iron_sword.draw(context, item_position + Point2I(0, 4), false, true, actual_angle);
			} else {
				bitmaps::iron_sword.draw(context, item_position + Point2I(0, -4), false, false);
			}
		}
	}

	if (fountain != nullptr) {
		fountain->draw(context, delta_time_ms);
	} else {
		bitmaps::bush.draw(context, Point2UI(100, 100));
	}

	GameState::render(context, delta_time_ms);
}

void CharacterTestState::handle_event(SDL_MouseButtonEvent* evt) {
	GameState::handle_event(evt);
	
	if (evt->button == SDL_BUTTON_LEFT) {
		if (evt->state == SDL_PRESSED) {
			float angle_radians = atan2f((float)(evt->y - (player_base->position.y + 4)), (float)(evt->x - (player_base->position.x + 4)));
			int angle_degrees = (int)(angle_radians / DEGREE + 360.0f) % 360;
			use_item(angle_degrees);
		} else if (evt->state == SDL_RELEASED) {
			is_using_item = false;
		}
	}
}

void CharacterTestState::handle_event(SDL_MouseMotionEvent* evt) {
	GameState::handle_event(evt);

	unsigned int buttons = SDL_GetMouseState(nullptr, nullptr);
	if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		float angle_radians = atan2f((float)(evt->y - (player_base->position.y + 4)), (float)(evt->x - (player_base->position.x + 4)));
		int angle_degrees = (int)(angle_radians / DEGREE + 360.0f) % 360;
		use_item(angle_degrees);
	}
}

void CharacterTestState::handle_event(SDL_KeyboardEvent* evt) {
	GameState::handle_event(evt);

	if (evt->repeat) {
		return;
	}

	if (evt->state == SDL_PRESSED) {
		switch (evt->keysym.sym) {
		case SDLK_ESCAPE:
			leave();
			break;
		case SDLK_w:
			set_player_facing(Vector2I::north());
			if ((evt->keysym.mod & KMOD_LSHIFT) == 0) {
				player_speed = player_facing;
			}
			break;
		case SDLK_s:
			set_player_facing(Vector2I::south());
			if ((evt->keysym.mod & KMOD_LSHIFT) == 0) {
				player_speed = player_facing;
			}
			break;
		case SDLK_a:
			set_player_facing(Vector2I::west());
			if ((evt->keysym.mod & KMOD_LSHIFT) == 0) {
				player_speed = player_facing;
			}
			break;
		case SDLK_d:
			set_player_facing(Vector2I::east());
			if ((evt->keysym.mod & KMOD_LSHIFT) == 0) {
				player_speed = player_facing;
			}
			break;
		case SDLK_SPACE:
			use_item(Vector2I::zero());
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

void CharacterTestState::use_item(int angle_degrees) {
	if (math::is_in_range(angle_degrees, 45, 135)) {
		use_item(Vector2I::south());
	} else if (math::is_in_range(angle_degrees, 135, 225)) {
		use_item(Vector2I::west());
	} else if (math::is_in_range(angle_degrees, 225, 315)) {
		use_item(Vector2I::north());
	} else {
		use_item(Vector2I::east());
	}

	if (fountain == nullptr) {
		fountain = ParticleFountain::from_bitmap(Point2F(100, 100), &bitmaps::bush);
	}
}

void CharacterTestState::use_item(Vector2I direction) {
	is_using_item = true;
	if (direction != Vector2I::zero()) {
		set_player_facing(direction);
	}
}

void CharacterTestState::set_player_facing(Vector2I direction) {
	if (player_facing == direction) {
		return;
	}

	player_facing = direction;
	if (player_facing == Vector2I::north()) {
		player_base->bitmap = &bitmaps::player_north;
	} else if (player_facing == Vector2I::south()) {
		player_base->bitmap = &bitmaps::player_south;
	} else if (player_facing == Vector2I::east()) {
		player_base->bitmap = &bitmaps::player_east;
	} else if (player_facing == Vector2I::west()) {
		player_base->bitmap = &bitmaps::player_west;
	}
}