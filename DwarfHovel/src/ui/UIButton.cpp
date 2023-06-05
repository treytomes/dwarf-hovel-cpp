#include "ui/ui.h"

unsigned int UIButton::command_event_id = 0;

void UIButton::inner_render(Rectangle b, IRenderContext* context, unsigned int delta_time_ms) {
	Rectangle deflated = Rectangle(b.get_x(), b.get_y(), b.get_width() - 1, b.get_height() - 1);
	context->draw_filled_rect(deflated, Color(0.2f, 0.2f, 0.2f));
	if (!has_mouse_focus()) {
		context->draw_v_line(b.get_right(), b.get_top() + 1, b.get_bottom() - 1, Color::black());
		context->draw_h_line(b.get_left() + 1, b.get_right(), b.get_bottom(), Color::black());
	}
	if (has_mouse_hover) {
		context->draw_rect(deflated, Color::orange());
	}
}

bool UIButton::inner_handle_event(SDL_MouseButtonEvent* evt) {
	if (evt->button == SDL_BUTTON_LEFT) {
		Rectangle b = get_bounds();
		if (evt->state == SDL_PRESSED) {
			acquire_mouse_focus();
			set_bounds(b.get_x() + 1, b.get_y() + 1, b.get_width(), b.get_height());
		} else {
			lose_mouse_focus();
			set_bounds(b.get_x() - 1, b.get_y() - 1, b.get_width(), b.get_height());

			if (has_mouse_hover) {
				// The button was clicked, so push the event.
				SDL_Event event;
				SDL_zero(event);
				event.type = command_event_id;
				event.user.code = id;
				event.user.data1 = 0;
				event.user.data2 = 0;
				SDL_PushEvent(&event);
			}
		}
		return true;
	}
	return false;
}
