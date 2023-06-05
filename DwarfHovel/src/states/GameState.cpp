#include "states/GameState.h"
#include "states/GameStateManager.h"

void GameState::enter(GameState* state) {
	parent->enter(state);
}

void GameState::leave() {
	parent->leave();
}
