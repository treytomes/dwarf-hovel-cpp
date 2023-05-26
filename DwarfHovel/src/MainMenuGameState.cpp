#include "MainMenuGameState.h"

#include "DemoGameState.h"
#include "SoundFXGameState.h"
#include "Logger.h"
#include "Settings.h"
#include "UIButton.h"
#include "UILabel.h"

#define DB_PERLIN_IMPL
#include "perlin.h"

#define IDB_DEMO 0
#define IDB_SFX 1
#define IDB_EXIT 4

MainMenuGameState::MainMenuGameState()
	: GameState(), angle(0.0f), mouse_x(0u), mouse_y(0u), horizontal_move_timer(0u), x_offset(0u), noise_offset(0.0f) {
	std::vector<std::string> options = {
		"Demo",
		"SFX",
		"Button 2",
		"Button 3",
		"Exit",
	};

	const Vector2UI screen_size = Settings::get_instance()->virtual_window_size;
	const unsigned int padding_top = 2;
	const unsigned int padding_bottom = 2;
	const unsigned int padding_left = 2;
	const unsigned int padding_right = 2;
	
	const unsigned int margin_top = 2;
	const unsigned int margin_bottom = 2;

	const unsigned int button_height = OEM437::CHAR_HEIGHT + padding_top + padding_bottom;
	const unsigned int total_height = (unsigned int)options.size() * (button_height + margin_top + margin_bottom);
	for (unsigned int n = 0; n < options.size(); n++) {
		std::string text = options[n];
		unsigned int button_id = n;
		unsigned int button_width = (unsigned int)text.size() * OEM437::CHAR_WIDTH + padding_left + padding_right;
		unsigned int x = screen_size.x / 2 - button_width / 2;
		unsigned int y = screen_size.y / 2 - ((unsigned int)options.size() - n) * (button_height + margin_top + margin_bottom) + total_height / 2;

		UILabel* lbl = new UILabel(Point2UI(padding_left, padding_top), text);
		UIButton* btn = new UIButton(n, Rectangle(Point2UI(x, y), Vector2UI(button_width, button_height)));
		btn->add_child(lbl);
		ui->add_child(btn);
	}
}

void MainMenuGameState::render(IRenderContext* context, unsigned int delta_time_ms) {
	horizontal_move_timer += delta_time_ms;
	if (horizontal_move_timer > 20) {
		horizontal_move_timer = 0;
		x_offset--;
		if (x_offset < -7) {
			x_offset = 0;
			noise_offset += 0.5f;
		}
	}
	
	context->clear(Color::sky().darker());

	const auto size = Settings::get_instance()->virtual_window_size;
	const auto cloud_bg = Color::transparent();
	for (unsigned int y = 0, row = 0; y < size.y; y += OEM437::CHAR_HEIGHT, row++) {
		for (unsigned int x = 0, col = 0; x < size.x + OEM437::CHAR_WIDTH; x += OEM437::CHAR_WIDTH, col++) {
			auto const noise = (
				db::perlin(float(x + noise_offset * 16.0f) / 64.0f, float(y) / 64.0f, noise_offset * 0.1f) * 1.0f +
				db::perlin(float(x + noise_offset * 16.0f) / 32.0f, float(y) / 32.0f, noise_offset * 0.2f) * 0.5f
			) / 1.5f;

			auto const height = (noise * 0.5f + 0.5f);
			auto const cloud_fg = Color::white();
			auto const tile = choose_cloud_tile(height);
			context->draw_char(Point2UI(x + x_offset, y), cloud_fg, cloud_bg, tile);
		}
	}

	GameState::render(context, delta_time_ms);
}

unsigned char MainMenuGameState::choose_cloud_tile(float height) {
	if (height < 0.5f) {
		return 32;
	} else if (height < 0.55f) {
		return 176;
	} else if (height < 0.6f) {
		return 177;
	} else if (height < 0.65f) {
		return 178;
	} else {
		return 219;
	}
}

void MainMenuGameState::handle_event(SDL_KeyboardEvent* evt) {
	/*
	if (evt->state == SDL_PRESSED) {
		if (evt->keysym.sym == SDLK_ESCAPE) {
			leave();
		}
	}
	*/

	GameState::handle_event(evt);
}

void MainMenuGameState::handle_event(SDL_UserEvent* evt) {
	switch (evt->code) {
	case IDB_DEMO:
		LOG_INFO("Entering the graphics demo state.");
		enter(new DemoGameState());
		break;
	case IDB_SFX:
		LOG_INFO("Entering the sound effect demo state.");
		enter(new SoundFXGameState());
		break;
	case IDB_EXIT:
		leave();
		break;
	}
}
