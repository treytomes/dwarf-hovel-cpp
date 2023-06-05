#include "states/GameStateManager.h"

GameStateManager::~GameStateManager() {
	while (!states.empty()) {
		GameState* state = states.top();
		states.pop();
		delete state;
	}
}

void GameStateManager::leave() {
	if (!states.empty()) {
		GameState* state = states.top();
		states.pop();
		delete state;
	}
}

void GameStateManager::update(unsigned int delta_time_ms) {
	GameState* state = get_current();
	if (state == nullptr) {
		return;
	}
	state->update(delta_time_ms);
}

void GameStateManager::render(IRenderContext* context, unsigned int delta_time_ms) {
	GameState* state = get_current();
	if (state == nullptr) {
		return;
	}
	state->render(context, delta_time_ms);
}

void GameStateManager::handle_event(SDL_WindowEvent* evt) {
	GameState* state = get_current();
	if (state == nullptr) {
		return;
	}
	state->handle_event(evt);
}

void GameStateManager::handle_event(SDL_KeyboardEvent* evt) {
	GameState* state = get_current();
	if (state == nullptr) {
		return;
	}
	state->handle_event(evt);
}

void GameStateManager::handle_event(SDL_MouseMotionEvent* evt) {
	GameState* state = get_current();
	if (state == nullptr) {
		return;
	}
	state->handle_event(evt);
}

void GameStateManager::handle_event(SDL_MouseButtonEvent* evt) {
	GameState* state = get_current();
	if (state == nullptr) {
		return;
	}
	state->handle_event(evt);
}

void GameStateManager::handle_event(SDL_MouseWheelEvent* evt) {
	GameState* state = get_current();
	if (state == nullptr) {
		return;
	}
	state->handle_event(evt);
}

void GameStateManager::handle_event(SDL_UserEvent* evt) {
	GameState* state = get_current();
	if (state == nullptr) {
		return;
	}
	state->handle_event(evt);
}
