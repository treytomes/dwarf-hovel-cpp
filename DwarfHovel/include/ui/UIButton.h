#pragma once

#include <SDL.h>
#include "IRenderContext.h"
#include "math/math.h"
#include "ui/ui.h"

class UIButton : public UIElement {
public:
	UIButton(unsigned int _id, Rectangle bounds) : UIElement(bounds), id(_id) {}
	void inner_render(Rectangle bounds, IRenderContext* context, unsigned int delta_time_ms);
	bool inner_handle_event(SDL_MouseButtonEvent* evt);

	static unsigned int command_event_id;

private:
	unsigned int id;
};
