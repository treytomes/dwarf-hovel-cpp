#pragma once

#include <SDL.h>
#include "IRenderContext.h"

class GameStateManager;

class GameState {
public:
	GameState(GameStateManager* _parent);
	~GameState();

	virtual void update(unsigned int delta_time_ms);
	virtual void render(IRenderContext* context, unsigned int delta_time_ms);

	void enter(GameState* state);
	void leave();

	inline virtual void handle_event(SDL_WindowEvent* evt) {}
	inline virtual void handle_event(SDL_KeyboardEvent* evt) {}
	inline virtual void handle_event(SDL_MouseMotionEvent* evt) {}

private:
	GameStateManager* parent;
};
