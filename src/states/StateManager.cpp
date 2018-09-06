#include "StateManager.h"

#include "State.h"
#include "../debugging.h"

void StateManager::update(Input &in) {
	state->update(in);
}

void StateManager::draw() {
	state->draw();
}

void StateManager::changeState(std::unique_ptr<State> newState) {
	DEBUG_LOG("Changing state to: " << newState->name);
	state = std::move(newState);
}