#pragma once

#include <SDL.h>
#include "GameState.h"
#include "IRenderContext.h"

class MainMenuGameState : public GameState {
public:
	MainMenuGameState();

	inline void render(IRenderContext* context, unsigned int delta_time_ms) {		
		context->clear(Color::black());
		GameState::render(context, delta_time_ms);
	}
	
	void handle_event(SDL_KeyboardEvent* evt);
	void handle_event(SDL_UserEvent* evt);

private:
	float angle;
	unsigned int mouse_x;
	unsigned int mouse_y;
};
