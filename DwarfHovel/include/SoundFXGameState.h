#pragma once

#include <string>
#include <SDL.h>
#include "GameState.h"
#include "IRenderContext.h"
#include "UIButton.h"

class SoundFXGameState : public GameState {
public:
	SoundFXGameState();
	void update(unsigned int delta_time_ms);
	void render(IRenderContext* context, unsigned int delta_time_ms);
	void handle_event(SDL_KeyboardEvent* evt);
	void handle_event(SDL_MouseMotionEvent* evt);
	void handle_event(SDL_UserEvent* evt);

private:
	UIButton* make_button(unsigned int id, unsigned int row, unsigned int column, std::string text);
};
