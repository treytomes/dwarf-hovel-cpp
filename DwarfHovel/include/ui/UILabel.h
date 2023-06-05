#pragma once

#include <string>
#include "Color.h"
#include "IRenderContext.h"
#include "OEM437.h"
#include "math/math.h"
#include "ui/ui.h"

class UILabel : public UIElement {
public:
	UILabel(PointUI point, std::string _text, Color _fg_color = Color(1.0f, 1.0f, 1.0f), Color _bg_color = Color(0.0f, 0.0f, 0.0f, 0.0f))
		: UIElement(Rectangle(point, VectorUI((unsigned int)text.size() * OEM437::CHAR_WIDTH, OEM437::CHAR_HEIGHT))), text(_text), fg_color(_fg_color), bg_color(_bg_color) {
		can_receive_mouse_hover = false;
	}

	void inner_render(Rectangle bounds, IRenderContext* context, unsigned int delta_time_ms);

	inline std::string get_text() { return text; }
	void set_text(const char* format, ...);

private:
	std::string text;
	Color fg_color;
	Color bg_color;
};
