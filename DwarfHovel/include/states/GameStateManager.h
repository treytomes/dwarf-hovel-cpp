#pragma once

#include <SDL.h>
#include <stack>
#include "states/GameState.h"
#include "IRenderContext.h"

class GameStateManager {
public:
	inline GameStateManager() {}

	~GameStateManager();

	inline bool has_active_state() {
		return states.empty();
	}

	inline void enter(GameState* state) {
		state->set_parent(this);
		states.push(state);
	}

	void leave();

	void update(unsigned int delta_time_ms);
	void render(IRenderContext* context, unsigned int delta_time_ms);

	virtual void handle_event(SDL_WindowEvent* evt);
	virtual void handle_event(SDL_KeyboardEvent* evt);
	virtual void handle_event(SDL_MouseMotionEvent* evt);
	virtual void handle_event(SDL_MouseButtonEvent* evt);
	virtual void handle_event(SDL_MouseWheelEvent* evt);
	virtual void handle_event(SDL_UserEvent* evt);

	inline GameState* get_current() { return states.empty() ? nullptr : states.top(); }

private:
	std::stack<GameState*> states;
};