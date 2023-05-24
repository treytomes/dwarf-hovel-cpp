#include "MainMenuGameState.h"

#include "DemoGameState.h"
#include "Logger.h"
#include "Settings.h"
#include "UIButton.h"
#include "UILabel.h"

MainMenuGameState::MainMenuGameState()
	: angle(0.0f), mouse_x(0u), mouse_y(0u) {
	ui_root = new UIElement(Rectangle(Point2UI::zero(), Settings::get_instance()->virtual_window_size));

	std::vector<std::string> options = {
		"Demo",
		"Button 1",
		"Button 2",
		"Button 3",
		"Exit",
	};

	const Vector2UI screen_size = Settings::get_instance()->virtual_window_size;
	const unsigned int padding = 2;
	const unsigned int height = OEM437::CHAR_HEIGHT + padding * 2;
	const unsigned int total_height = (unsigned int)options.size() * height;
	for (unsigned int n = 0; n < options.size(); n++) {
		std::string text = options[n];
		unsigned int button_id = n;
		unsigned int width = (unsigned int)text.size() * OEM437::CHAR_WIDTH + padding * 2;
		unsigned int x = screen_size.x / 2 - width / 2;
		unsigned int y = screen_size.y / 2 - ((unsigned int)options.size() - n) * height + total_height / 2;

		UILabel* lbl = new UILabel(Point2UI(padding, padding), text);
		UIButton* btn = new UIButton(n, Rectangle(Point2UI(x, y), Vector2UI(width, height)));
		btn->add_child(lbl);
		ui_root->add_child(btn);
	}
}

MainMenuGameState::~MainMenuGameState() {
	if (ui_root != nullptr) {
		delete ui_root;
		ui_root = nullptr;
	}
}

void MainMenuGameState::update(unsigned int delta_time_ms) {
	ui_root->update(delta_time_ms);
}

void MainMenuGameState::render(IRenderContext* context, unsigned int delta_time_ms) {
	context->clear(Color::black());
	ui_root->render(context, delta_time_ms);
}

void MainMenuGameState::handle_event(SDL_KeyboardEvent* evt) {
	if (evt->state == SDL_PRESSED) {
		if (evt->keysym.sym == SDLK_ESCAPE) {
			leave();
		}
	}
	
	ui_root->handle_event(evt);
}

void MainMenuGameState::handle_event(SDL_MouseMotionEvent* evt) {
	ui_root->handle_event(evt);
}

void MainMenuGameState::handle_event(SDL_MouseButtonEvent* evt) {
	ui_root->handle_event(evt);
}

void MainMenuGameState::handle_event(SDL_MouseWheelEvent* evt) {
	ui_root->handle_event(evt);
}

void MainMenuGameState::handle_event(SDL_UserEvent* evt) {
	switch (evt->code) {
	case 0:
		LOG_INFO("Entering the demo state.");
		enter(new DemoGameState());
		break;
	case 4:
		leave();
		break;
	}
}
