#pragma once

#include <SDL.h>
#include "states/GameState.h"
#include "IRenderContext.h"

class MainMenuGameState : public GameState {
public:
	MainMenuGameState();

	void render(IRenderContext* context, unsigned int delta_time_ms);
	void handle_event(SDL_KeyboardEvent* evt);
	void handle_event(SDL_UserEvent* evt);

private:
	float angle;
	unsigned int mouse_x;
	unsigned int mouse_y;

	unsigned int horizontal_move_timer;
	unsigned int x_offset;
	float noise_offset;

	unsigned char choose_cloud_tile(float height);
};
