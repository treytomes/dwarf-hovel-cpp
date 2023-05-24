#include "GameState.h"
#include "GameStateManager.h"

void GameState::update(unsigned int delta_time_ms) {
}

void GameState::render(IRenderContext* context, unsigned int delta_time_ms) {
}

void GameState::enter(GameState* state) {
	parent->enter(state);
}

void GameState::leave() {
	parent->leave();
}
