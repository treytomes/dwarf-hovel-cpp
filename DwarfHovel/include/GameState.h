#pragma once

#include <SDL.h>
#include "IRenderContext.h"

class GameStateManager;

class GameState {
public:
	inline GameState() {}
	inline ~GameState() { parent = nullptr; }

	virtual void update(unsigned int delta_time_ms);
	virtual void render(IRenderContext* context, unsigned int delta_time_ms);

	void enter(GameState* state);
	void leave();
	inline void set_parent(GameStateManager* _parent) { parent = _parent; }

	inline virtual void handle_event(SDL_WindowEvent* evt) {}
	inline virtual void handle_event(SDL_KeyboardEvent* evt) {}
	inline virtual void handle_event(SDL_MouseMotionEvent* evt) {}
	inline virtual void handle_event(SDL_MouseButtonEvent* evt) {}
	inline virtual void handle_event(SDL_MouseWheelEvent* evt) {}
	inline virtual void handle_event(SDL_UserEvent* evt) {}

protected:
	GameStateManager* parent;
};
