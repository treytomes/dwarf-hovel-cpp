#include "MainMenuGameState.h"

#include "DemoGameState.h"
#include "Logger.h"
#include "Settings.h"
#include "UIButton.h"
#include "UILabel.h"

#define DB_PERLIN_IMPL
#include "perlin.h"

#define IDB_DEMO 0
#define IDB_EXIT 4

MainMenuGameState::MainMenuGameState()
	: GameState(), angle(0.0f), mouse_x(0u), mouse_y(0u) {
	std::vector<std::string> options = {
		"Demo",
		"Button 1",
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
	elapsed_time_ms += delta_time_ms;
	float offset = elapsed_time_ms / 1000.0f;

	context->clear(Color::sky().darker());

	Vector2UI size = Settings::get_instance()->virtual_window_size;
	for (unsigned int y = 0, row = 0; y < size.y; y += OEM437::CHAR_HEIGHT, row++) {
		for (unsigned int x = 0, col = 0; x < size.x; x += OEM437::CHAR_WIDTH, col++) {
			//float height = db::perlin<float>((float)x, (float)y);
			auto const noise = (
				db::perlin(float(x + offset * 16.0f) / 64.0f, float(y) / 64.0f, offset * 0.1f) * 1.0f +
				db::perlin(float(x + offset * 16.0f) / 32.0f, float(y) / 32.0f, offset * 0.2f) * 0.5f
                ) / 1.5f;

			float height = (noise * 0.5f + 0.5f);

			if (height < 0.5f) {
				context->draw_char(Point2UI(x, y), Color::white(), Color::transparent(), 32);
			} else if (height < 0.55f) {
				context->draw_char(Point2UI(x, y), Color::white(), Color::transparent(), 176);
			} else if (height < 0.6f) {
				context->draw_char(Point2UI(x, y), Color::white(), Color::transparent(), 177);
			} else if (height < 0.65f) {
				context->draw_char(Point2UI(x, y), Color::white(), Color::transparent(), 178);
			} else {
				context->draw_char(Point2UI(x, y), Color::white(), Color::transparent(), 219);
			}
		}
	}

	GameState::render(context, delta_time_ms);
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
		LOG_INFO("Entering the demo state.");
		enter(new DemoGameState());
		break;
	case IDB_EXIT:
		leave();
		break;
	}
}
