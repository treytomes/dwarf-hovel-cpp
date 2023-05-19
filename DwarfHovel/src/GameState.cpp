#include "GameState.h"
#include "GameStateManager.h"

GameState::GameState(GameStateManager* _parent)
	: parent(_parent) {
}

GameState::~GameState() {
	parent = nullptr;
}

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
