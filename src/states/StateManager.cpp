#include "states/StateManager.h"

#include "states/State.h"
#include "debugging.h"

bool StateManager::update(Input &in) {
	if (nextState != nullptr) state = std::move(nextState); // Change the current state to the next state should one be set.

	if (state == nullptr) return true; // Indicate that there is no state and that the program should therefore exit.

	state->update(in);

	return false;
}

void StateManager::draw() {
	if (state != nullptr) state->draw();
}

void StateManager::changeState(std::unique_ptr<State> newState) {
	DEBUG_LOG("Changing state to: " << newState->name);
	nextState = std::move(newState);
}

void StateManager::exit() {
	state.reset();
}
