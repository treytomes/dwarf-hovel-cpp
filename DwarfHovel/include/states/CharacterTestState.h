#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include "states/GameState.h"
#include "IRenderContext.h"
#include "ParticleFountain.h"
#include "Sprite.h"
#include "ui/ui.h"
#include "math/math.h"

class CharacterTestState : public GameState {
public:
	CharacterTestState();
	~CharacterTestState();

	void update(unsigned int delta_time_ms);
	void render(IRenderContext* context, unsigned int delta_time_ms);
	void handle_event(SDL_KeyboardEvent* evt);
	void handle_event(SDL_MouseButtonEvent* evt);
	void handle_event(SDL_MouseMotionEvent* evt);
	void handle_event(SDL_UserEvent* evt);

private:
	unsigned int total_elapsed_time;
	unsigned int last_horizontal_pulse_time;
	unsigned int last_vertical_pulse_time;
	float grid_offset_x;
	float grid_offset_y;
	
	Sprite* player_base;
	ParticleFountain* fountain;

	Vector2I player_speed;
	Vector2I player_facing;
	bool is_using_item;
	float item_angle;

	void use_item(int angle_degrees);
	void use_item(Vector2I direction);
	void set_player_facing(Vector2I direction);
};
