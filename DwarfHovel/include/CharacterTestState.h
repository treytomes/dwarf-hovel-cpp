#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include "GameState.h"
#include "IRenderContext.h"
#include "Sprite.h"
#include "UIButton.h"
#include "Vector2UI.h"

enum class Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
};

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
	float grid_offset_x;
	float grid_offset_y;
	
	Bitmap2bpp* player_south_bitmap;
	Bitmap2bpp* player_north_bitmap;
	Bitmap2bpp* player_east_bitmap;
	Bitmap2bpp* player_west_bitmap;
	Sprite* player_base;

	Vector2UI player_speed;
	Direction player_facing;
};
