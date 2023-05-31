#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include "GameState.h"
#include "IRenderContext.h"
#include "UIButton.h"

class CharacterTestState : public GameState {
public:
	CharacterTestState();
	~CharacterTestState();

	void update(unsigned int delta_time_ms);
	void render(IRenderContext* context, unsigned int delta_time_ms);
	void handle_event(SDL_KeyboardEvent* evt);
	void handle_event(SDL_MouseMotionEvent* evt);
	void handle_event(SDL_UserEvent* evt);

private:
	unsigned int total_elapsed_time;
	unsigned int last_horizontal_pulse_time;
	unsigned int last_vertical_pulse_time;
	
	Point2UI player_position;
    unsigned short bitmap_player_base[8];
};
