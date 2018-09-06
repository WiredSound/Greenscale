#pragma once

#include <memory>
#include "../Input.h"
class State;

class StateManager {
public:
	void update(Input &in);
	void draw();
	void changeState(std::unique_ptr<State> newState);

private:
	std::unique_ptr<State> state;
};