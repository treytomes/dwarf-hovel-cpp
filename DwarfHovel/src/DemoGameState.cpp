#include "DemoGameState.h"

#include <string>
#include "Logger.h"
#include "OEM437.h"
#include "math/math.h"
#include "Settings.h"
#include "ui/ui.h"

DemoGameState::DemoGameState()
	: GameState(), angle(0.0f), mouse_x(0u), mouse_y(0u) {
	test_button_id = 1;
	unsigned int padding = 2;
	std::string text = "My Button";
	UILabel* lbl = new UILabel(Point2UI(padding, padding), text);
	UIButton* btn = new UIButton(test_button_id, Rectangle(Point2UI(10, 10), Vector2UI((unsigned int)text.size() * OEM437::CHAR_WIDTH + padding * 2, OEM437::CHAR_HEIGHT + padding * 2)));
	btn->add_child(lbl);
	ui->add_child(btn);
}

void DemoGameState::update(unsigned int delta_time_ms) {
	GameState::update(delta_time_ms);
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

	context->set_pixel(Point2UI(50u, 50u), Color(0.0f, 0.0f, 1.0f));

	context->draw_filled_rect(Point2UI(55u, 65u), Point2UI(105u, 90u), Color(1.0f, 0.5f, 0.25f));

	context->draw_line(Point2UI::zero(), Point2UI(max_x, max_y), Color(1.0f, 0.0f, 1.0f));
	context->draw_line(Point2UI(0, max_y), Point2UI(max_x, 0), Color(1.0f, 0.0f, 1.0f));

	context->draw_circle(Point2UI(center_x - 20, center_y - 50), 25, Color(1.0f, 0.0f, 0.0f));
	context->flood_fill(Point2UI(center_x - 20, center_y - 50), Color(0.5f, 0.0f, 0.5f), Color(1.0f, 0.0f, 0.0f));

	context->draw_circle(Point2UI(center_x, center_y), 25, Color(1.0f, 0.0f, 0.0f));

	context->draw_line(Point2UI(center_x, center_y), Point2UI(center_x - (unsigned int)(25 * cos(angle)), center_y - (unsigned int)(25 * sin(angle))), Color(0.5f, 0.0f, 0.0f));

	context->draw_string(Point2UI(50, 190), Color(1.0f, 1.0f, 0.1f), Color(0.0f, 0.0f, 0.9f), "Hello, world!");
	context->draw_char(Point2UI(50, 200), Color(1.0f, 1.0f, 0.9f), Color(0.0f, 0.0f, 0.1f), '*');

	//if (math::is_in_range(mouse_x, 0u, context->get_width() - 1) && math::is_in_range(mouse_y, 0u, context->get_height() - 1)) {
	//	context->draw_circle(Point2UI(mouse_x, mouse_y), 4, Color(1.0f, 1.0f, 0.0f));
	//	context->flood_fill(Point2UI(mouse_x, mouse_y), Color(1.0f, 1.0f, 0.0f), Color(1.0f, 1.0f, 0.0f));
	//}

	GameState::render(context, delta_time_ms);
}

void DemoGameState::handle_event(SDL_MouseMotionEvent* evt) {
	mouse_x = evt->x;
	mouse_y = evt->y;
	LOG_DEBUG("Mouse position: (%d, %d)", mouse_x, mouse_y);
	
	GameState::handle_event(evt);
	
}

void DemoGameState::handle_event(SDL_KeyboardEvent* evt) {
	if (evt->state == SDL_PRESSED) {
		if (evt->keysym.sym == SDLK_ESCAPE) {
			leave();
		}
	}
	
	GameState::handle_event(evt);
}

void DemoGameState::handle_event(SDL_UserEvent* evt) {
	if (evt->code == test_button_id) {
		LOG_INFO("The test button was clicked!");
	}
}
