#pragma once

#include <memory>
#include "../Input.h"
class State;

class StateManager {
public:
	bool update(Input &in);
	void draw();
	void changeState(std::unique_ptr<State> newState);
	void exit();

private:
	std::unique_ptr<State> state;
	std::unique_ptr<State> nextState;
};