#pragma once

#include <SDL.h>
#include "GameState.h"
#include "IRenderContext.h"
#include "UIElement.h"

class DemoGameState : public GameState {
public:
	DemoGameState();
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
