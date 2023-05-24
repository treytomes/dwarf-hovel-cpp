#include "main.h"

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include <cstdarg>
#include <string>
#include <vector>
#include "moremath.h"
#include "Rectangle.h"
#include "OEM437.h"

class DemoGameState : public GameState {
public:
	DemoGameState(GameStateManager* parent);
	~DemoGameState();
	void update(unsigned int delta_time_ms);
	void render(IRenderContext* context, unsigned int delta_time_ms);
	void handle_event(SDL_KeyboardEvent* evt);
	void handle_event(SDL_MouseMotionEvent* evt);
	void handle_event(SDL_MouseButtonEvent* evt);
	void handle_event(SDL_MouseWheelEvent* evt);
	void handle_event(SDL_UserEvent* evt);

private:
	unsigned int test_button_id;

	UIElement* ui_root;
	float angle;
	unsigned int mouse_x;
	unsigned int mouse_y;
};

DemoGameState::DemoGameState(GameStateManager* parent)
	: GameState(parent), angle(0.0f), mouse_x(0u), mouse_y(0u) {
	ui_root = new UIElement(Rectangle(Point2UI::zero(), Settings::get_instance()->virtual_window_size));

	test_button_id = 1;
	unsigned int padding = 2;
	std::string text = "My Button";
	UILabel* lbl = new UILabel(Point2UI(padding, padding), text);
	UIButton* btn = new UIButton(test_button_id, Rectangle(Point2UI(10, 10), Vector2UI((unsigned int)text.size() * OEM437::CHAR_WIDTH + padding * 2, OEM437::CHAR_HEIGHT + padding * 2)));
	btn->add_child(lbl);
	ui_root->add_child(btn);
}

DemoGameState::~DemoGameState() {
	if (ui_root != nullptr) {
		delete ui_root;
		ui_root = nullptr;
	}
}

void DemoGameState::update(unsigned int delta_time_ms) {
	ui_root->update(delta_time_ms);
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

	ui_root->render(context, delta_time_ms);
}

void DemoGameState::handle_event(SDL_MouseMotionEvent* evt) {
	mouse_x = evt->x;
	mouse_y = evt->y;
	LOG_DEBUG("Mouse position: (%d, %d)", mouse_x, mouse_y);
	
	ui_root->handle_event(evt);
}

void DemoGameState::handle_event(SDL_KeyboardEvent* evt) {
	if (evt->state == SDL_PRESSED) {
		if (evt->keysym.sym == SDLK_ESCAPE) {
			leave();
		}
	}
	
	ui_root->handle_event(evt);
}

void DemoGameState::handle_event(SDL_MouseButtonEvent* evt) {
	ui_root->handle_event(evt);
}

void DemoGameState::handle_event(SDL_MouseWheelEvent* evt) {
	ui_root->handle_event(evt);
}

void DemoGameState::handle_event(SDL_UserEvent* evt) {
	if (evt->code == test_button_id) {
		LOG_INFO("The test button was clicked!");
	}
}

int main(int argc, char* argv[]) {
	Window* window = nullptr;
	int error_code = 0;

	try {
		System::initialize();
		LOG_INFO("Starting %s.", Settings::get_instance()->window_title.c_str());

		LOG_INFO("Registering custom events.");
		UIButton::command_event_id = SDL_RegisterEvents(1);
		if (UIButton::command_event_id == ((unsigned int)-1)) {
			LOG_ERROR("Failed to register the button event.");
		}

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
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					if (window->can_handle_event(&evt.button)) {
						window->handle_event(&evt.button);
					}
					break;
				case SDL_MOUSEWHEEL:
					if (window->can_handle_event(&evt.wheel)) {
						window->handle_event(&evt.wheel);
					}
					break;
				default:
					if (evt.user.type == UIButton::command_event_id) {
						window->handle_event(&evt.user);
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
