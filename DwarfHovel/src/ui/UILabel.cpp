#include "ui/ui.h"

void UILabel::inner_render(Rectangle bounds, IRenderContext* context, unsigned int delta_time_ms) {
	context->draw_string(bounds.get_position(), fg_color, bg_color, text.c_str());
}

void UILabel::set_text(const char* format, ...) {
	va_list args;
	va_start(args, format);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	text = buffer;
}
